---
title: onConnectionStatus
nextjs:
  metadata:
    title: onConnectionStatus Callback | API
    description: Learn more about onConnectionStatus callback in NetWizard.
---

The onConnectionStatus callback is called whenever the device changes its network connection status. The callback will be called with `NetWizardConnectionStatus` enum as its parameter.

## Connection Statuses

Here are all the possible connection statuses that can be returned by the `onConnectionStatus` callback:

- `NetWizardConnectionStatus::DISCONNECTED`
- `NetWizardConnectionStatus::CONNECTING`
- `NetWizardConnectionStatus::CONNECTED`
- `NetWizardConnectionStatus::CONNECTION_FAILED`
- `NetWizardConnectionStatus::CONNECTION_LOST`
- `NetWizardConnectionStatus::NOT_FOUND`


## API Reference

```cpp
void setup() {
  ...

  // This callback will be called upon connection status changes
  NW.onConnectionStatus([&](NetWizardConnectionStatus status) {
    ... // <-- add your own logic here
  });

  ...
}
```
