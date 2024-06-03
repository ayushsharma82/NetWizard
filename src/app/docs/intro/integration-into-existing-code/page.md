---
title: Integration into Existing Code
nextjs:
  metadata:
    title: Integration into Existing Code
    description: Learn how to integrate NetWizard into your existing code.
---

Integrating NetWizard into your existing code is pretty simple. Follow the steps below to get started.

## Install Dependencies

Please make sure you have followed the [installation guide](/docs/installation) before proceeding.

## Preparing Code

To prepare your existing code, please make sure that you have removed any occurrences of `WiFi.begin` or `WiFi.softAP` from your code. This ensures that your code will not interfere with NetWizard's own logic.

Once done, you may start integrating NetWizard into your existing code.

{% callout title="Note" %}
It's recommended that you remove all occurences of `WiFi` in your code once NetWizard is fully integrated, rather use methods provided by NetWizard library itself to obtain SSID, PSK, Local IP etc.
{% /callout %}

## Integration

### 1. Include NetWizard Library

At the very beginning of sketch include the NetWizard library.

```cpp
#include <NetWizard.h>
```

### 2. Create `NetWizard` Instance

Create an instance of `NetWizard` object which takes your WebServer object as an argument.

```cpp
NetWizard NW(&server);
```

### 3. Setup `autoConnect`

At the point we call `autoConnect`, NetWizard will try to connect to any saved credentials. If none exists, it will start the captive portal and wait for user input ( till timout ). We'll add `autoConnect` in `setup()` function.

```cpp
void setup() {
  ...

  NW.autoConnect("NetWizard Demo", "");  // <-- Add this line

  ...
}
```

### 4. Add `loop` Function

Add the `loop` function into `loop` block of your sketch. This function will be called repeatedly to manage the WiFi connection and perform other tasks under the hood.

```cpp
void loop() {
  ...

  NW.loop();  // <-- Add this line

  ...
}
```

## Conclusion

Congratulations! You have successfully integrated NetWizard into your existing code. This is the most minimal setup of NetWizard, now you can add more features and callbacks by looking at the API reference.