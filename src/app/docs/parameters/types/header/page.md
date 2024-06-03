---
title: Header
nextjs:
  metadata:
    title: Parameters | Header
    description: Learn more about on header parameter type in NetWizard.
---

![Header](/nw-header.png)

You can create an `Header` parameter type that will be displayed as a header in the UI. It's a simple parameter which doesn't take any input from the user or hold a value, it's just used for segmenting your configuration page.

## API Reference

```cpp

NetWizard NW(&server);

NetWizardParameter nw_header(&NW, NW_HEADER, "MQTT"); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```
