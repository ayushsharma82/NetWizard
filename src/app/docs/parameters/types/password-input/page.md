---
title: Password Input (Pro)
nextjs:
  metadata:
    title: Parameters | Password Input
    description: Learn more about password input parameter type in NetWizard.
---

{% callout title="Pro Feature" %}
This is an exclusive feature of NetWizard Pro. Check it out [here](https://netwizard.pro).
{% /callout %}

![Password Input](/nw-password-input.png)

Similar to `Input`, a `Password Input` parameter type is used when you want to collect sensitive information from the user. For example: passwords and other settings relevant to your application. This type of input field will mask the value entered by the user.

## Constructor

The constructor of `Password Input` parameter type takes 3 useful parameters:

- `name` - The name of the parameter
- `value` - The default value of the parameter *(optional - can be set as empty string)*
- `placeholder` - The placeholder which is displayed when the input is empty *(optional - can be set as empty string)*

```cpp
NetWizardParameter nw_input(&NW, NW_PASSWORD_INPUT, "Name", "Value", "Placeholder");
```

## API Reference

### Initialization

```cpp
NetWizard NW(&server);

NetWizardParameter nw_input(&NW, NW_PASSWORD_INPUT, "MQTT Password", "", "Enter Password"); // <-- add this line

void setup() {
  ...
}

void loop() {
  ...
}
```

### Getters

```cpp
// Store the value of the input in `val` using `getValue`
String val;
nw_input.getValue(val);
```

```cpp
String val = nw_input.getValueStr(); // <-- get value inline
```

### Setters

```cpp
// Set the value of the input using `setValue`
nw_input.setValue("Value123");
```