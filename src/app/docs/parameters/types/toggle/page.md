---
title: Toggle (Pro)
nextjs:
  metadata:
    title: Parameters | Toggle
    description: Learn more about toggle parameter type in NetWizard.
---

{% callout title="Pro Feature" %}
This is an exclusive feature of NetWizard Pro. Check it out [here](https://netwizard.pro).
{% /callout %}

![Toggle](/nw-toggle.png)

You can create an `Toggle` parameter type that will be displayed as a clickable toggle switch on the configuration page. Toggle parameter takes integer values and return `0` or `1` depending on toggle state.

## Constructor

The constructor of `Toggle` parameter type takes 2 useful parameters:

- `name` - The name of the parameter
- `value` - The default value of the parameter *(optional)*

```cpp
NetWizardParameter nw_toggle(&NW, NW_TOGGLE, "Name", 0);
```

## API Reference

### Initialization

```cpp
NetWizard NW(&server);

NetWizardParameter nw_toggle(&NW, NW_TOGGLE, "Toggle", 0); // <-- add this line

void setup() {
  ...
}

void loop() {
  ...
}
```

### Getters

```cpp
// Store the value of the toggle in `val` using `getValue`
int val;
nw_toggle.getValue(val);
```

```cpp
int val = nw_toggle.getValueInt(); // <-- get value inline
```

### Setters

```cpp
// Set the value of the toggle using `setValue`
nw_toggle.setValue(1);
```