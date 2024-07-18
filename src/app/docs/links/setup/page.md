---
title: Setup Links
nextjs:
  metadata:
    title: Setup Links
    description: Learn more about on how to setup links in NetWizard which lets you add buttons in the captive portal that redirect to other pages in AP mode.
---

{% callout title="Pro Feature" %}
This is an exclusive feature of NetWizard Pro. Check it out [here](https://netwizard.pro).
{% /callout %}

![Links](/links.png)

NetWizard Pro comes with `Links` module which lets you add buttons in the captive portal that redirect to other pages in AP mode. Use links to redirect the user to for example [ElegantOTA](https://elegantota.pro) portal or your own application's AP mode webpage.


All the links are added sequentially to the config page in between `Setup` & `Exit` buttons. You can add as many links as you want.

## API Reference

### Initialization

```cpp

NetWizard NW(&server);

NetWizardLink nw_link(&NW, "Firmware Update", "/update"); // <-- add this line here

void setup() {
  ...
}

void loop() {
  ...
}
```

### Setters

```cpp
nw_link.setLabel("Label");
```

```cpp
nw_link.setURL("/update");
```