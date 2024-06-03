---
title: Setup Parameters
nextjs:
  metadata:
    title: Setup Parameters
    description: Learn more about on how to setup parameters in NetWizard which lets you make dynamic configuration page shown to the user in captive portal.
---


NetWizard comes with a super easy system called `Parameters` to create your own configuration page which is shown to the user in captive portal.

This particularly is useful for gathering settings, information and other data that can be used in your application. For example: MQTT credentials, user data, application specific settings etc.

![Parameters](/parameters.png)

{% callout title="Tip" %}
The configuration page will be hidden automatically when there are no parameters defined in code.
{% /callout %}

<!-- NetWizard library has a class called `NetWizardParameter` which is used to store individual parameters which are then put together automatically in the configuration page. -->

All the parameters are added sequentially to the config page and you can add as many parameters as you want. This allows complete control over the layout of the configuration page.

{% callout title="Note on Persistence" %}
Parameters are **not** persistent and values will be lost when the device is reset, therefore it's recommended to process or save them as per your application upon receiving [`onConfig`](/docs/parameters/on-config) callback.
{% /callout %}

## Parameter Types

Parameters can be of following types, please refer to each type for more details on implementation.

- [Header](/docs/parameters/types/header)
- [Divider](/docs/parameters/types/input)
- [Spacer](/docs/parameters/types/spacer)
- [Input](/docs/parameters/types/input)

## API Reference

```cpp

NetWizard NW(&server);

NetWizardParameter nw_host(&NW, NW_INPUT, "MQTT Host", "", "mqtt.example.com"); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```
