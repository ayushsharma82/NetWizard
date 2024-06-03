---
title: startPortal
nextjs:
  metadata:
    title: startPortal | API
    description: Learn more about startPortal function in NetWizard.
---

The startPortal function will **start the captive portal on demand**. It will default to AP credentials set when `autoConnect` function was called.

Note: This function is still governed by portal timeout which can be set using `setPortalTimeout` function. The portal will be stopped once the timeout is reached.

## API Reference

```cpp
NW.startPortal();
```
