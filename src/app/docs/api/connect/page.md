---
title: connect
nextjs:
  metadata:
    title: connect | API
    description: Learn more about connect function in NetWizard.
---

The connect function if supplied without any parameters will connect to your saved network credentials. Once executed, you can monitor the connection status via [`onConnectionStatus`](/docs/api/on-connection-status) callback.

If you would like to re-write the saved network credentials, then you can supply `ssid` and `password` parameters to this connect function. This will overwrite the saved credentials.

## API Reference

You can call this function anywhere in your code.

```cpp
NW.connect();  // <-- connect to saved credentials
```

```cpp
NW.connect("ssid", "password");  // <-- connect to new credentials
```
