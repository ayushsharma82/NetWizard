---
title: Getting started
---

Learn more about NetWizard and know how to get started with it.  {% .lead %}

- 🛜 No hard-coded WiFi credentials
- ⚙️ Create an custom configuration page using just C++
- ⚡ Intuitive step-by-step setup flow which makes user interaction easier
- 🎷 No need to learn HTML/CSS/JS
- 🛫 Ready to use within 4-5 lines of code

---

## What is NetWizard?

NetWizard is a WiFi manager library for microcontrollers that have WiFi capabilities. The library is designed to eliminate the need to hard-code WiFi credentials in your project/device which is always a need when you are:

1. Developing a product for market
2. Frequently switching between different WiFi networks
3. Eliminating the need to re-compile your device firmware every time you switch WiFi networks

NetWizard completely handles all the WiFi setup and management tasks, so you don't need to worry about it. It also comes with a captive portal interface that means there's very little friction when setting up your device.

---

## What is Dynamic Captive Portal?

Often there's a requirement to gather certain parameters from user while they setup the device. This can include MQTT credentials, various application specific settings and all.

To solve this need, **netwizard comes with a dynamic captive portal** that makes it super easy to do this and makes it all possible from C++ itself. You can create these parameters in your C++ code and those will appear automatically in the captive portal for user to fill.

---

## Quick Links

{% quick-links %}

{% quick-link title="Installation" icon="installation" href="/docs/intro/installation" description="Step-by-step guide to setting up your dependencies and installing the library." /%}

{% quick-link title="NetWizard Example" icon="presets" href="/docs/intro/example" description="Study the source code to learn more about how it works." /%}

{% quick-link title="Async Mode" icon="plugins" href="/docs/intro/async-mode" description="Learn how to enable async mode of NetWizard." /%}

{% quick-link title="Adding Parameters" icon="lightbulb" href="/docs/adding-parameters" description="Learn how to build your own configuration page." /%}

{% /quick-links %}

---

This documentation serves both NetWizard Lite and NetWizard Pro. Therefore, if you notice `(Pro)` mentioned on any of the features in the documentation, it means that particular feature is only available in [NetWizard Pro](https://netwizard.pro).
