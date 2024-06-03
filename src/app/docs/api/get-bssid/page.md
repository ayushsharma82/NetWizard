---
title: getBSSID
nextjs:
  metadata:
    title: getBSSID | API
    description: Learn more about getBSSID function in NetWizard.
---

The getBSSID function will return the BSSID of the configured/saved network.

Note: the network connection status should be `CONNECTED` in order for this function to work properly.

## API Reference

```cpp
uint8_t bssid[6];

NW.getBSSID(bssid);
```
