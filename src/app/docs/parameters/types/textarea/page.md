---
title: Textarea
nextjs:
  metadata:
    title: Parameters | Textarea
    description: Learn more about textarea parameter type in NetWizard.
---

![Textarea](/nw-textarea.png)

You can create an `Textarea` parameter type that will be displayed as a multi-line text input on the configuration page. This is particularly useful when you want to collect application specific input from the user. For example: TLS certificates, keys or other data which is best suited to be entered in a multi-line format.

## Constructor

The constructor of `Textarea` parameter type takes 3 useful parameters:

- `name` - The name of the parameter
- `value` - The default value of the parameter *(optional - can be set as empty string)*
- `placeholder` - The placeholder which is displayed when the input is empty *(optional - can be set as empty string)*

```cpp
NetWizardParameter nw_textarea(&NW, NW_TEXTAREA, "Name", "Value", "Placeholder");
```

## API Reference

### Initialization

```cpp
NetWizard NW(&server);

NetWizardParameter nw_textarea(&NW, NW_TEXTAREA, "Root CA", "", "-----BEGIN CERTIFICATE-----\n-----END CERTIFICATE-----"); // <-- add this line

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
nw_textarea.getValue(val);
```

```cpp
String val = nw_textarea.getValueStr(); // <-- get value inline
```

### Setters

```cpp
// Set the value of the input using `setValue`
nw_textarea.setValue("Value123");
```
