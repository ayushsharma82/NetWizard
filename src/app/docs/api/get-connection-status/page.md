---
title: getConnectionStatus
nextjs:
  metadata:
    title: getConnectionStatus | API
    description: Learn more about getConnectionStatus function in NetWizard.
---

The getConnectionStatus function will return the current network connection status of the device. It will return `NetWizardConnectionStatus` enum as its return value, as described [here](/docs/api/on-connection-status#connection-statuses).

## API Reference

```cpp
NetWizardConnectionStatus status = NW.getConnectionStatus();
```
