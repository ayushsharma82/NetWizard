---
title: Setup Statistics
nextjs:
  metadata:
    title: Setup Statistics
    description: Learn more about on how to setup statistics in NetWizard which lets you show key-value pairs in the captive portal.
---

{% callout title="Pro Feature" %}
This is an exclusive feature of NetWizard Pro. Check it out [here](https://netwizard.pro).
{% /callout %}

NetWizard Pro comes with `Statistics` module which lets you show key-value pairs in the captive portal. These are quite essential when you want to add your own application specific data to captive portal.

![Statistics](/statistics.png)

All the statistics are added sequentially to the config page and you can add as many statistics as you want.

## API Reference

### Initialization

```cpp

NetWizard NW(&server);

NetWizardStatistic nw_stat(&NW, "Label", "Value"); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```

### Setters

```cpp
nw_stat.setLabel("Label");
```

```cpp
nw_stat.setValue("Value");
```