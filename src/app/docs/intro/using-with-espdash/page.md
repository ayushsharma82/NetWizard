---
title: Using with ESP-DASH
nextjs:
  metadata:
    title: Using with ESP-DASH
    description: Learn how to use NetWizard with ESP-DASH library
---

## What is ESP-DASH?

ESP-DASH is a on-device dashboard library for wireless microcontrollers through which you can setup your very own web dashboard to visualize or control things in your firmware. Know more about ESP-DASH - [click here](https://github.com/ayushsharma82/ESP-DASH).

## Sample Code

Using NetWizard along with ESP-DASH can be easily done as illustrated in this sample code. You can also skip to bottom of the page to see what changes were applied.

{% callout title="Enable Async Mode" %}
Please make sure you have enabled async mode of NetWizard before compiling your firmware. Ref: [Async Mode](/docs/intro/async-mode)
{% /callout %}

```cpp
#include <Arduino.h>
#if defined(ESP8266)
  /* ESP8266 Dependencies */
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(ESP32)
  /* ESP32 Dependencies */
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#elif defined(TARGET_RP2040) || defined(PICO_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2350)
  /* RP2040 or RP2350 Dependencies */
  #include <WiFi.h>
  #include <RPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif
#include <NetWizard.h>
#include <ESPDash.h>

// Start AsyncWebServer
AsyncWebServer server(80);

// Initialize NetWizard
NetWizard NW(&server);

// Setup configuration parameters
NetWizardParameter nw_header(&NW, NW_HEADER, "MQTT");
NetWizardParameter nw_divider1(&NW, NW_DIVIDER);
NetWizardParameter nw_mqtt_host(&NW, NW_INPUT, "Host", "", "mqtt.example.com");
NetWizardParameter nw_mqtt_port(&NW, NW_INPUT, "Port", "", "1883");

// Initialize ESP-DASH
ESPDash dashboard(&server, "/dashboard", true);    // <--- We initialize ESP-DASH at "/dashboard" URL so that NetWizard logic is not distrupted

/* 
  Dashboard Cards 
  Format - (Dashboard Instance, Card Type, Card Name, Card Symbol(optional) )
*/
Card temperature(&dashboard, TEMPERATURE_CARD, "Temperature", "°C");
Card humidity(&dashboard, HUMIDITY_CARD, "Humidity", "%");


void setup(void) {
  delay(3000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starting NetWizard & ESP-DASH Demo...");

  // ----------------------------
  // Configure NetWizard Strategy
  // ----------------------------
  // BLOCKING - Connect to WiFi and wait till portal is active
  // (blocks execution after autoConnect)
  // 
  // NON_BLOCKING - Connect to WiFi and proceed while portal is active in background
  // (does not block execution after autoConnect)
  NW.setStrategy(NetWizardStrategy::BLOCKING);

  // Listen for connection status changes
  NW.onConnectionStatus([](NetWizardConnectionStatus status) {
    String status_str = "";

    switch (status) {
      case NetWizardConnectionStatus::DISCONNECTED:
        status_str = "Disconnected";
        break;
      case NetWizardConnectionStatus::CONNECTING:
        status_str = "Connecting";
        break;
      case NetWizardConnectionStatus::CONNECTED:
        status_str = "Connected";
        break;
      case NetWizardConnectionStatus::CONNECTION_FAILED:
        status_str = "Connection Failed";
        break;
      case NetWizardConnectionStatus::CONNECTION_LOST:
        status_str = "Connection Lost";
        break;
      case NetWizardConnectionStatus::NOT_FOUND:
        status_str = "Not Found";
        break;
      default:
        status_str = "Unknown";
    }

    Serial.printf("NW connection status changed: %s\n", status_str.c_str());
    if (status == NetWizardConnectionStatus::CONNECTED) {
      // Local IP
      Serial.printf("Local IP: %s\n", NW.localIP().toString().c_str());
      // Gateway IP
      Serial.printf("Gateway IP: %s\n", NW.gatewayIP().toString().c_str());
      // Subnet mask
      Serial.printf("Subnet mask: %s\n", NW.subnetMask().toString().c_str());
    }
  });

  // Listen for portal state changes
  NW.onPortalState([](NetWizardPortalState state) {
    String state_str = "";

    switch (state) {
      case NetWizardPortalState::IDLE:
        state_str = "Idle";
        break;
      case NetWizardPortalState::CONNECTING_WIFI:
        state_str = "Connecting to WiFi";
        break;
      case NetWizardPortalState::WAITING_FOR_CONNECTION:
        state_str = "Waiting for Connection";
        break;
      case NetWizardPortalState::SUCCESS:
        state_str = "Success";
        break;
      case NetWizardPortalState::FAILED:
        state_str = "Failed";
        break;
      case NetWizardPortalState::TIMEOUT:
        state_str = "Timeout";
        break;
      default:
        state_str = "Unknown";
    }

    Serial.printf("NW portal state changed: %s\n", state_str.c_str());
  });

  NW.onConfig([&]() {
    Serial.println("NW onConfig Received");

    // Print new parameter values
    Serial.printf("Host: %s\n", nw_mqtt_host.getValueStr().c_str());
    Serial.printf("Port: %s\n", nw_mqtt_port.getValueStr().c_str());
    return true; // <-- return true to approve request, false to reject
  });

  // Start NetWizard
  NW.autoConnect("NetWizard Demo", "");
  
  // Check if configured
  if (NW.isConfigured()) {
    Serial.println("Device is configured");
  } else {
    Serial.println("Device is not configured!");
  }

  // Demo Route
  server.on("/demo", HTTP_GET, []() {
    server.send(200, "text/plain", "Hi! This is NetWizard Demo.");
  });

  // Internal rewrite for ESP-DASH dashboard
  server.rewrite("/", "/dashboard").setFilter(ON_STA_FILTER);    // <---  Add this server.rewrite so that we display ESP-DASH at "/" on STA connections

  // Start WebServer
  server.begin();
}

void loop(void) {
  // NetWizard Loop Task
  NW.loop();
}
```

## So what was the catch?

1. We had to initialze ESP-DASH at "/dashboard" URL so that it doesn't clash with the NetWizard's portal in AP mode.
2. Create a `server.rewrite` inside `setup()` block for STA connections, so that we display the dashboard on "/" when your device is being accessed by user on LAN.


Once these changes were applied, both libraries work with each other without any problems!
