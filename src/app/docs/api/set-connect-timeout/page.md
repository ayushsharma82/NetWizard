---
title: setConnectTimeout
nextjs:
  metadata:
    title: setConnectTimeout | API
    description: Learn more about setConnectTimeout function in NetWizard.
---

The setConnectTimeout function will set the timeout for the WiFi connection attempt that is done inside `autoConnect` function. The default value is 30 seconds (`30000` milliseconds).

If the device fails to connect to the saved network within the timeout, the `autoConnect` function will stop trying to connect to the network and will start the captive portal.

## API Reference

```cpp
void setup() {
  ...

  NW.setConnectTimeout(15000);

  ...
}
```
