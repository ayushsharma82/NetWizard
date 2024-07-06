---
title: localIP
nextjs:
  metadata:
    title: localIP | API
    description: Learn more about localIP function in NetWizard.
---

The localIP function will return the local IP address of the connected network.

Note: the network connection status should be `CONNECTED` in order for this function to work properly. You can verify this using [`getConnectionStatus`](/docs/api/get-connection-status) function.

## API Reference

```cpp
IPAddress ip = NW.localIP();
```

```cpp
String ip = NW.localIP().toString();
```
