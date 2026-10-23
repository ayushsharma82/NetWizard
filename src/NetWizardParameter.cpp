#include "NetWizardParameter.h"

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type) : NetWizardParameter(parent, type, "", "", "", true) {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name) : NetWizardParameter(parent, type, name, "", "", true) {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value) : NetWizardParameter(parent, type, name, value, "", true) {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value, const char* placeholder) : NetWizardParameter(parent, type, name, value, placeholder, true) {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value, const char* placeholder, bool required) {
  _parent = parent;
  _id = _parent->nextId();
  _type = type;
  _name = name;
  _value = value;
  _placeholder = placeholder;
  _parent->addParameter(this);
  _required = required;
}

int NetWizardParameter::getType() {
  return _type;
}

const String& NetWizardParameter::getValue() {
  return _value;
}

const String& NetWizardParameter::getValueStr() {
  return getValue();
}

void NetWizardParameter::getValue(String& value) {
  value = _value;
}

void NetWizardParameter::setValue(const String& value) {
  _value = value;
}

void NetWizardParameter::setValue(const char* value) {
  _value = value;
}

String NetWizardParameter::getPlaceholder() {
  return _placeholder;
}

void NetWizardParameter::setPlaceholder(const char* placeholder) {
  _placeholder = placeholder;
}

void NetWizardParameter::setRequired(bool required) {
  _required = required;
}

NetWizardParameter::~NetWizardParameter() {
  _value = "";
  _placeholder = "";
  if (_parent != NULL) {
    _parent->removeParameter(this);
  }
}