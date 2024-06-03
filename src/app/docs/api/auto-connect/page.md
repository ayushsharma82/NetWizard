---
title: autoConnect
nextjs:
  metadata:
    title: autoConnect | API
    description: Learn more about autoConnect function in NetWizard.
---

The autoConnect function will first try to connect to your saved network credentials and it will start the captive portal if any of the following conditions are met:

1. The device is not configuered (i.e. there is no saved network).
2. The device failed to connect to saved WiFi network (due to invalid credentials or timeout).

autoConnect takes 2 parameters, `ap_ssid` and `ap_password`. These are the credentials of the AP that your device will broadcast when the captive portal is active.

## API Reference

```cpp
void setup() {
  ...

  NW.autoConnect("NetWizard Demo", ""); // <-- add this line before autoConnect

  ...
}
```
