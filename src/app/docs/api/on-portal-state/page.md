---
title: onPortalState
nextjs:
  metadata:
    title: onPortalState Callback | API
    description: Learn more about onPortalState callback in NetWizard.
---

The captive portal itself has its own state which is often transmitted back to UI for displaying the neccessary prompt. This makes sure that the UI is always in sync with the captive portal state even after the device reconnects to the network.

The onPortalState callback is called whenever this captive portal state changes. The callback will be called with `NetWizardPortalState` enum as its parameter.

By listening to this callback, you can react to these changes in your code. For example: changing LED color to green when configuraiton is successful or performing any task based on the state etc.

## Captive Portal States

Here are all the possible captive portal states that can be returned by the `onPortalState` callback:

- `NetWizardPortalState::IDLE`
- `NetWizardPortalState::CONNECTING_WIFI`
- `NetWizardPortalState::WAITING_FOR_CONNECTION`
- `NetWizardPortalState::SUCCESS`
- `NetWizardPortalState::FAILED`
- `NetWizardPortalState::TIMEOUT`

## API Reference

```cpp
void setup() {
  ...

  // This callback will be called upon captive portal state changes
  NW.onPortalState([&](NetWizardPortalState state) {
    ... // <-- add your own logic here
  });

  ...
}
```
