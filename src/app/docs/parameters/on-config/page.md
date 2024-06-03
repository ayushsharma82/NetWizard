---
title: onConfig Callback
nextjs:
  metadata:
    title: onConfig Callback
    description: Learn more about on how to use onConfig callback in NetWizard.
---

The onConfig callback is called whenever the device receives new parameter values from the UI (usually upon clicking `Finish` button in captive portal).

You also approve or deny the request by simply returning `true` or `false` respectively in the callback.

New values are stored within each `NetWizardParameter` class and can be accessed using the `getValue` function for validation/processing etc. *Please refer to each parameter type for more details on their API.*

## API Reference

```cpp
void setup() {
  ...

  NW.onConfig([&]() {
    ... // <-- add your own logic here

    return true; // <-- approve request
  })

  ...
}
```
