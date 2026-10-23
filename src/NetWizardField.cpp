#include "NetWizard.h"
#include <errno.h>

NetWizardField::NetWizardField(NetWizard *parent, const char* type, const char* name) {
  _parent = parent;
  _id = _parent->nextId();
  _type = type;
  _name = name;
  _parent->add(this);
}

void NetWizardField::toJson(JsonObject obj) {
  obj["id"] = _id;
  obj["t"] = _type;
  obj["n"] = _name;
}

bool NetWizardField::parseInt(const char* str, long& out) {
  char* end = nullptr;
  errno = 0;
  out = strtol(str, &end, 10);
  if (end == str || errno == ERANGE) return false;
  while (*end == ' ') end++;
  return *end == '\0';
}

bool NetWizardField::parseFloat(const char* str, double& out) {
  char* end = nullptr;
  errno = 0;
  out = strtod(str, &end);
  if (end == str || errno == ERANGE || isnan(out) || isinf(out)) return false;
  while (*end == ' ') end++;
  return *end == '\0';
}

NetWizardField::~NetWizardField() {
  if (_parent != nullptr) {
    _parent->remove(this);
  }
  _parent = nullptr;
}

NetWizardHeader::NetWizardHeader(NetWizard *parent, const char* title, const char* description)
  : NetWizardField(parent, "h", title), _description(description) {}

void NetWizardHeader::setTitle(const char* title) {
  _name = title;
}

void NetWizardHeader::setDescription(const char* description) {
  _description = description;
}

void NetWizardHeader::toJson(JsonObject obj) {
  NetWizardField::toJson(obj);
  // the portal shows a header's value as its description
  obj["v"] = _description;
}
