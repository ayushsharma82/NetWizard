---
title: subnetMask
nextjs:
  metadata:
    title: subnetMask | API
    description: Learn more about subnetMask function in NetWizard.
---

The subnetMask function will return the subnet mask of the connected network.

Note: the network connection status should be `CONNECTED` in order for this function to work properly. You can verify this using [`getConnectionStatus`](/docs/api/get-connection-status) function.

## API Reference

```cpp
IPAddress subnet = NW.subnetMask();
```

```cpp
String subnet = NW.subnetMask().toString();
```
