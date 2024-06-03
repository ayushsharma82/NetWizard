---
title: Divider
nextjs:
  metadata:
    title: Parameters | Divider
    description: Learn more about on divider parameter type in NetWizard.
---

![Divider](/nw-divider.png)

You can create an `Divider` parameter type that will be displayed as a divider in the UI. It's a simple parameter which doesn't take any input from the user or hold a value, it's just used for segmenting your configuration page.

## API Reference

```cpp

NetWizard NW(&server);

NetWizardParameter nw_divider(&NW, NW_DIVIDER); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```
