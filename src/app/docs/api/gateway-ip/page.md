---
title: gatewayIP
nextjs:
  metadata:
    title: gatewayIP | API
    description: Learn more about gatewayIP function in NetWizard.
---

The gatewayIP function will return the gateway IP address of the connected network.

Note: the network connection status should be `CONNECTED` in order for this function to work properly. You can verify this using [`getConnectionStatus`](/docs/api/get-connection-status) function.

## API Reference

```cpp
IPAddress ip = NW.gatewayIP();
```

```cpp
String ip = NW.gatewayIP().toString();
```
