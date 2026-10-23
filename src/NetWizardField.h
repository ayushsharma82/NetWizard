#ifndef NETWIZARD_FIELD_H
#define NETWIZARD_FIELD_H

#include "Arduino.h"
#include "ArduinoJson.h"
#include <type_traits>

#if defined(ESP32) && defined(NETWIZARD_USE_ASYNC_WEBSERVER) && NETWIZARD_USE_ASYNC_WEBSERVER == 1
  #include "freertos/FreeRTOS.h"
  #include "freertos/semphr.h"
#endif

class NetWizard;

/*
  Guards field values in async mode on ESP32, where the portal applies saved
  values from the AsyncTCP task while the sketch reads them from loop().
  Everywhere else the web server runs on the sketch's own context, so the lock
  compiles to nothing.
*/
class NetWizardFieldLock {
  public:
  #if defined(ESP32) && defined(NETWIZARD_USE_ASYNC_WEBSERVER) && NETWIZARD_USE_ASYNC_WEBSERVER == 1
    NetWizardFieldLock() { xSemaphoreTake(_mutex(), portMAX_DELAY); }
    ~NetWizardFieldLock() { xSemaphoreGive(_mutex()); }
  private:
    static SemaphoreHandle_t _mutex() {
      static SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
      return mutex;
    }
  #endif
};

/*
  Base of every element on the portal's settings step. It registers itself with
  NetWizard on construction and removes itself on destruction, so fields are
  usually declared globally, next to the NetWizard instance.
*/
class NetWizardField {
  public:
    NetWizardField(const NetWizardField&) = delete;
    NetWizardField& operator=(const NetWizardField&) = delete;
    virtual ~NetWizardField();

  protected:
    NetWizardField(NetWizard *parent, const char* type, const char* name = "");

    // schema sent to the portal
    virtual void toJson(JsonObject obj);
    // value posted back by the portal: accepts() validates, fromJson() applies
    virtual bool hasValue() const { return false; }
    virtual bool accepts(JsonVariantConst value) const { (void)value; return true; }
    virtual void fromJson(JsonVariantConst value) { (void)value; }

    // parse a whole integer / number out of a string, rejecting trailing junk
    static bool parseInt(const char* str, long& out);
    static bool parseFloat(const char* str, double& out);

    NetWizard *_parent = nullptr;
    uint32_t _id;
    const char* _type;
    String _name;

  friend class NetWizard;
};

/* A section title, with an optional line of text under it. */
class NetWizardHeader : public NetWizardField {
  public:
    NetWizardHeader(NetWizard *parent, const char* title, const char* description = "");
    void setTitle(const char* title);
    void setDescription(const char* description);

  protected:
    void toJson(JsonObject obj) override;

  private:
    String _description;
};

/* A horizontal rule between fields. */
class NetWizardDivider : public NetWizardField {
  public:
    explicit NetWizardDivider(NetWizard *parent) : NetWizardField(parent, "d") {}
};

/* A little extra vertical space between fields. */
class NetWizardSpacer : public NetWizardField {
  public:
    explicit NetWizardSpacer(NetWizard *parent) : NetWizardField(parent, "s") {}
};

/*
  A text input holding a value of type T: String, int, float or double.

    NetWizardInput host(&NW, "Host", "", "mqtt.example.com");   // String
    NetWizardInput port(&NW, "Port", 1883);                     // int
    NetWizardInput<float> ratio(&NW, "Ratio", 0.5f);

  Numeric inputs bring up the numeric keyboard in the portal and are checked
  on the device, a value that doesn't parse is rejected with an error.
*/
template <typename T = String>
class NetWizardInput : public NetWizardField {
  static_assert(
    std::is_same<T, String>::value || std::is_same<T, int>::value || std::is_same<T, float>::value || std::is_same<T, double>::value,
    "NetWizardInput supports String, int, float and double values"
  );

  public:
    NetWizardInput(NetWizard *parent, const char* name, T value = T(), const char* placeholder = "", bool required = true)
      : NetWizardInput(parent, "i", name, value, placeholder, required) {}

    // a copy of the current value, safe to keep
    T getValue() const {
      NetWizardFieldLock lock;
      return _value;
    }

    void setValue(const T& value) {
      NetWizardFieldLock lock;
      _value = value;
    }

    void setPlaceholder(const char* placeholder) { _placeholder = placeholder; }
    void setRequired(bool required) { _required = required; }

  protected:
    NetWizardInput(NetWizard *parent, const char* type, const char* name, T value, const char* placeholder, bool required)
      : NetWizardField(parent, type, name), _value(value), _placeholder(placeholder), _required(required) {}

    void toJson(JsonObject obj) override {
      NetWizardField::toJson(obj);
      {
        NetWizardFieldLock lock;
        obj["v"] = _value;
      }
      obj["p"] = _placeholder;
      obj["r"] = _required;
      obj["k"] = std::is_same<T, String>::value ? "s" : (std::is_same<T, int>::value ? "i" : "f");
    }

    bool hasValue() const override { return true; }

    bool accepts(JsonVariantConst value) const override { return _parse(value, (T*)nullptr); }

    void fromJson(JsonVariantConst value) override { _parse(value, &_value); }

  private:
    // String: any string; empty only if the field is optional
    template <typename U = T>
    typename std::enable_if<std::is_same<U, String>::value, bool>::type _parse(JsonVariantConst value, U* out) const {
      if (!value.is<const char*>()) return false;
      const char* str = value.as<const char*>();
      if (_required && str[0] == '\0') return false;
      if (out) *out = str;
      return true;
    }

    // int: a JSON integer, or a string holding one
    template <typename U = T>
    typename std::enable_if<std::is_same<U, int>::value, bool>::type _parse(JsonVariantConst value, U* out) const {
      long v;
      if (value.is<int>()) {
        v = value.as<int>();
      } else if (value.is<const char*>()) {
        const char* str = value.as<const char*>();
        if (str[0] == '\0' && !_required) {
          v = 0;
        } else if (!parseInt(str, v) || (long)(int)v != v) {
          return false;
        }
      } else {
        return false;
      }
      if (out) *out = (int)v;
      return true;
    }

    // float / double: a JSON number, or a string holding one
    template <typename U = T>
    typename std::enable_if<std::is_floating_point<U>::value, bool>::type _parse(JsonVariantConst value, U* out) const {
      double v;
      if (value.is<double>()) {
        v = value.as<double>();
      } else if (value.is<const char*>()) {
        const char* str = value.as<const char*>();
        if (str[0] == '\0' && !_required) {
          v = 0;
        } else if (!parseFloat(str, v)) {
          return false;
        }
      } else {
        return false;
      }
      if (out) *out = (U)v;
      return true;
    }

    T _value;
    String _placeholder;
    bool _required;
};

// A text value (string literal or no value at all) makes a String input
NetWizardInput(NetWizard*, const char*) -> NetWizardInput<String>;
NetWizardInput(NetWizard*, const char*, const char*) -> NetWizardInput<String>;
NetWizardInput(NetWizard*, const char*, const char*, const char*) -> NetWizardInput<String>;
NetWizardInput(NetWizard*, const char*, const char*, const char*, bool) -> NetWizardInput<String>;

#endif
