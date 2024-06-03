---
title: Spacer
nextjs:
  metadata:
    title: Parameters | Spacer
    description: Learn more about on spacer parameter type in NetWizard.
---

You can create an `Spacer` parameter type that will be added as empty space between other parameters in the UI. It's a simple parameter which doesn't take any input from the user or hold a value, it's just used for segmenting your configuration page.

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
