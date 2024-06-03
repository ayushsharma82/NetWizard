---
title: setStrategy
nextjs:
  metadata:
    title: setStrategy | API
    description: NetWizard comes with 2 strategies, learn how to set them up.
---


setStrategy in NetWizard is used to set the captive portal strategy which alters the behavior of captive portal when it is active. NetWizard comes with 2 captive portal strategies:

1. `NetWizardStrategy::BLOCKING`
2. `NetWizardStrategy::NON_BLOCKING`

## Blocking Strategy

By default NetWizard uses the `BLOCKING` strategy where the captive portal blocks further execution of the code (after `autoConnect`) until any of the following conditions are met:

- User has exited the portal upon request
- Portal has been timed out

## Non-Blocking Strategy

`NON_BLOCKING` strategy is similar to `BLOCKING` but does not block the execution of the code after `autoConnect`. Your code should be prepared to handle every connection state updates during runtime.

`NON_BLOCKING` strategy is quite essential if your project/product depends on doing important background tasks while the captive portal is up, otherwise it's recommended to stick to blocking strategy.

## API Reference

```cpp
void setup() {
  ...

  NW.setStrategy(NetWizardStrategy::BLOCKING);  // <-- add this line before autoConnect

  NW.autoConnect("NetWizard Demo", "");

  ...
}
```
