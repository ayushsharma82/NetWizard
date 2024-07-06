/*
 _   _      _ __        ___                  _ 
| \ | | ___| |\ \      / (_)______ _ _ __ __| |
|  \| |/ _ \ __\ \ /\ / /| |_  / _` | '__/ _` |
| |\  |  __/ |_ \ V  V / | |/ / (_| | | | (_| |
|_| \_|\___|\__| \_/\_/  |_/___\__,_|_|  \__,_|
                                               
An easy-to-use yet powerful WiFi manager and captive portal library for wireless microcontrollers.

Author: Ayush Sharma (ayush@softt.io)

Upgrade to NetWizard Pro: https://netwizard.pro
*/

#ifndef NETWIZARD_H
#define NETWIZARD_H

#ifndef NETWIZARD_USE_ASYNC_WEBSERVER
  #define NETWIZARD_USE_ASYNC_WEBSERVER 0
#endif

#ifndef NETWIZARD_DEBUG
  #define NETWIZARD_DEBUG 0
#endif

#if NETWIZARD_DEBUG
  #define NETWIZARD_DEBUG_MSG(x) Serial.printf("%s %s", "[NetWizard]", x)
#else
  #define NETWIZARD_DEBUG_MSG(x) 
#endif

#define NETWIZARD_PORTAL_TIMEOUT      60000 * 5  // 5 minutes
#define NETWIZARD_CONNECT_TIMEOUT     30000      // 30 seconds
#define NETWIZARD_EXIT_TIMEOUT        5000       // 5 seconds

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "vector.h"
#include <functional>
#include "Preferences.h"

#if defined(ESP8266)
  #include "ESP8266WiFi.h"
  #if NETWIZARD_USE_ASYNC_WEBSERVER == 1
    #include "ESPAsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #define NETWIZARD_WEBSERVER AsyncWebServer
    #define NETWIZARD_REQ_HANDLER AsyncWebHandler
  #else
    #include "ESP8266WebServer.h"
    #define NETWIZARD_WEBSERVER ESP8266WebServer
    #define NETWIZARD_REQ_HANDLER RequestHandler
  #endif
  #define HARDWARE "ESP8266"
#elif defined(ESP32)
  #include "WiFi.h"
  #if NETWIZARD_USE_ASYNC_WEBSERVER == 1
    #include "AsyncTCP.h"
    #include "ESPAsyncWebServer.h"
    #define NETWIZARD_WEBSERVER AsyncWebServer
    #define NETWIZARD_REQ_HANDLER AsyncWebHandler
  #else
    #include "WebServer.h"
    #define NETWIZARD_WEBSERVER WebServer
    #define NETWIZARD_REQ_HANDLER RequestHandler
  #endif
  #define HARDWARE "ESP32"
#elif defined(TARGET_RP2040)
  #include "WiFi.h"
  #if NETWIZARD_USE_ASYNC_WEBSERVER == 1
    #include "AsyncTCP_RP2040W.h"
    #include "ESPAsyncWebServer.h"
    #define NETWIZARD_WEBSERVER AsyncWebServer
    #define NETWIZARD_REQ_HANDLER AsyncWebHandler
  #else
    #include "WebServer.h"
    #define NETWIZARD_WEBSERVER WebServer
    #define NETWIZARD_REQ_HANDLER RequestHandler
  #endif
  #define HARDWARE "RP2040"
#endif

#include "DNSServer.h"
#include "ArduinoJson.h"
#include "NetWizardParameter.h"

// enum for strategy
typedef enum {
  NON_BLOCKING = 0,
  BLOCKING,
} NetWizardStrategy;

typedef enum {
  DISCONNECTED = 0,
  CONNECTING,
  CONNECTED,
  CONNECTION_FAILED,
  CONNECTION_LOST,
  NOT_FOUND,
} NetWizardConnectionStatus;

typedef enum {
  IDLE = 0,
  CONNECTING_WIFI,
  WAITING_FOR_CONNECTION,
  SUCCESS,
  FAILED,
  TIMEOUT
} NetWizardPortalState;

typedef enum {
  OPEN = 0,
  WEP,
  WPA_PSK,
  WPA2_PSK,
  WPA_WPA2_PSK,
  ENTERPRISE,
  WPA2_ENTERPRISE,
  WPA3_PSK,
  WPA2_WPA3_PSK,
  WAPI_PSK,
  OWE,
  WPA3_ENT_192,
  WPA3_EXT_PSK,
  WPA3_EXT_PSK_MIXED_MODE,
  MAX,
  UNKNOWN
} NetWizardEncryptionType;

class NetWizardParameter;

typedef std::function<void(NetWizardConnectionStatus)> NetWizardOnConnectionStatusCallback;
typedef std::function<void(NetWizardPortalState)> NetWizardOnPortalStateCallback;
typedef std::function<bool()> NetWizardOnConfigCallback;

class NetWizard {
  public:
    NetWizard(NETWIZARD_WEBSERVER *server);

    // authentication
    void setAuthentication(String& username, String& password);
    void setAuthentication(const char* username, const char* password);
    
    void setHostname(const char* hostname);
    void setHostname(String& hostname);
    void setConnectTimeout(unsigned long timeout);
    void setPortalTimeout(unsigned long timeout);
    void setStrategy(NetWizardStrategy strategy);

    // replace existing credentials (without invoking portal or WiFi connection)
    void setCredentials(const char* ssid, const char* password);

    // connect to any saved credentials or start captive portal
    void autoConnect(const char* ssid, const char* password);

    // callbacks
    void onConnectionStatus(NetWizardOnConnectionStatusCallback callback);
    void onPortalState(NetWizardOnPortalStateCallback callback);
    void onConfig(NetWizardOnConfigCallback callback);

    // status
    bool isConfigured();
    NetWizardConnectionStatus getConnectionStatus();
    NetWizardPortalState getPortalState();
    const char* getSSID();
    const char* getPassword();
    void getBSSID(uint8_t* bssid);
    uint8_t getChannel();
    IPAddress localIP();
    IPAddress gatewayIP();
    IPAddress subnetMask();

    bool connect();
    bool connect(const char* ssid, const char* password);
    void disconnect();
    void reset();
    void loop();

    // portal
    void startPortal();
    void stopPortal();

    // configuration params
    uint32_t nextId();
    void addParameter(NetWizardParameter* parameter);
    void removeParameter(NetWizardParameter* parameter);

    ~NetWizard();

  private:
    NETWIZARD_WEBSERVER *_server;
    NETWIZARD_REQ_HANDLER *_index_handler    = nullptr;
    NETWIZARD_REQ_HANDLER *_status_handler   = nullptr;
    NETWIZARD_REQ_HANDLER *_schema_handler   = nullptr;
    NETWIZARD_REQ_HANDLER *_scan_handler     = nullptr;
    NETWIZARD_REQ_HANDLER *_save_handler     = nullptr;
    NETWIZARD_REQ_HANDLER *_clear_handler    = nullptr;
    NETWIZARD_REQ_HANDLER *_exit_handler     = nullptr;
    bool _server_running = false;
    DNSServer* _dns = nullptr;
    bool _dns_running = false;

    // nw params
    struct {
      NetWizardStrategy strategy = NetWizardStrategy::BLOCKING;
      NetWizardConnectionStatus status = NetWizardConnectionStatus::DISCONNECTED;
      NetWizardOnConnectionStatusCallback status_cb = nullptr;
      String hostname = "netwizard";

      // sta parameters
      struct {
        bool configured = false;
        unsigned long timeout = NETWIZARD_CONNECT_TIMEOUT;
        String ssid = "";
        String password = "";
        // uint8_t bssid[6];
        // uint8_t channel = 0;
      } sta;
      
      // portal parameters
      struct {
        bool active = false;
        bool blocking = false;
        unsigned long timeout = NETWIZARD_PORTAL_TIMEOUT;
        unsigned long start_millis = 0;
        unsigned long connect_millis = 0;
        NetWizardPortalState state = NetWizardPortalState::IDLE;
        NetWizardOnPortalStateCallback state_cb = nullptr;

        struct {
          bool flag = false;
          unsigned long millis = 0;
        } exit;

        struct {
          String ssid = "";
          String password = "";
        } ap;

        struct {
          String ssid = "";
          String password = "";
          // uint8_t bssid[6];
          // uint8_t channel = 0;
        } sta;

        struct {
          bool enabled = false;
          String username = "";
          String password = "";
        } auth;

        struct {
          bool active = false;
          unsigned long start_millis = 0;
          uint16_t last_status = 0;
        } scan;
        
        struct {
          uint32_t counter = 0;
          Vector<NetWizardParameter*> parameters;
          NetWizardOnConfigCallback callback = nullptr;
        } config;
      } portal;
    } _nw;

    // helper functions
    void _connect(const char* ssid, const char* password);
    void _disconnect();
    void _saveSTACredentials();
    void _loadSTACredentials();
    bool _isIp(String str);

    // HTTP functions
    void _generateStatusJson(String& str);
    void _generateSchemaJson(String& str);
    void _generateScanJson(String& str);
    bool _parseConfigJson(JsonArray& arr);
    bool _parseCredentialsJson(JsonObject& obj);
    void _restartScan();
    // HTTP
    void _startHTTP();
    void _stopHTTP();
    // Portal
    void _startPortal();
    void _stopPortal();

  protected:
  #if NETWIZARD_USE_ASYNC_WEBSERVER == 1
    static bool _onAPFilter(AsyncWebServerRequest *request);
  #else
    #if defined(ESP8266) || defined(ESP32)
      static bool _onAPFilter(NETWIZARD_WEBSERVER &server);
    #elif defined(TARGET_RP2040)
      static bool _onAPFilter(HTTPServer &server);
    #endif
  #endif
};

#endif
