---
title: Input
nextjs:
  metadata:
    title: Parameters | Input
    description: Learn more about input parameter type in NetWizard.
---

![Input](/nw-input.png)

You can create an `Input` parameter type that will be displayed as a text input on the configuration page. This is particularly useful when you want to collect application specific input from the user. For example: credentials and other settings relevant to your application.

## Constructor

The constructor of `Input` parameter type takes 3 useful parameters:

- `name` - The name of the parameter
- `value` - The default value of the parameter *(optional - can be set as empty string)*
- `placeholder` - The placeholder which is displayed when the input is empty *(optional - can be set as empty string)*

```cpp
NetWizardParameter nw_input(&NW, NW_INPUT, "Name", "Value", "Placeholder");
```

## API Reference

### Initialization

```cpp
NetWizard NW(&server);

NetWizardParameter nw_input(&NW, NW_INPUT, "MQTT Host", "", "mqtt.example.com"); // <-- add this line

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