---
title: Spacer
nextjs:
  metadata:
    title: Parameters | Spacer
    description: Learn more about spacer parameter type in NetWizard.
---

You can create an `Spacer` parameter type that will be added as empty space between other parameters in the UI.

## API Reference

```cpp

NetWizard NW(&server);

NetWizardParameter nw_spacer(&NW, NW_SPACER); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```
