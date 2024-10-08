#include "NetWizardParameter.h"

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type) : NetWizardParameter(parent, type, "", "", "") {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name) : NetWizardParameter(parent, type, name, "", "") {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value) : NetWizardParameter(parent, type, name, value, "") {}

NetWizardParameter::NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value, const char* placeholder) {
  _parent = parent;
  _id = _parent->nextId();
  _type = type;
  _name = name;
  _value = value;
  _placeholder = placeholder;
  _parent->addParameter(this);
}

const int NetWizardParameter::getType() {
  return _type;
}

const String& NetWizardParameter::getValue() {
  return _value;
}

const String& NetWizardParameter::getValueStr() {
  return _value;
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

NetWizardParameter::~NetWizardParameter() {
  _value = "";
  _placeholder = "";
  if (_parent != NULL) {
    _parent->removeParameter(this);
  }
}