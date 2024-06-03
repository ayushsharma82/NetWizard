---
title: erase
nextjs:
  metadata:
    title: erase | API
    description: Learn more about erase function in NetWizard.
---

The erase function will only erase any saved network credentials. So the next time you reboot the device, it will be in it's initial network state.

Note: This function will **not** disconnect the device or stop the captive portal.

## API Reference

You can call this function anywhere in your code.

```cpp
NW.erase();
```
