#ifndef NETWIZARD_PARAMETER_H
#define NETWIZARD_PARAMETER_H

#include "NetWizard.h"

enum {
  NW_HEADER,
  NW_DIVIDER,
  NW_SPACER,
  NW_INPUT,
};

struct NetWizardParameterTypeNames {
  int value;
  const char* type;
};

class NetWizard;

class NetWizardParameter {
  public:
    NetWizardParameter(NetWizard *parent, const int type);
    NetWizardParameter(NetWizard *parent, const int type, const char* name);
    NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value);
    NetWizardParameter(NetWizard *parent, const int type, const char* name, const char* value, const char* placeholder);

    const int getType();

    String getValue();
    void setValue(const char* value);

    String getPlaceholder();
    void setPlaceholder(const char* placeholder);

    ~NetWizardParameter();
  private:
    NetWizard *_parent;
    uint32_t _id;
    int _type;
    const char* _name;
    String _value;
    String _placeholder;

    friend class NetWizard;
};

#endif