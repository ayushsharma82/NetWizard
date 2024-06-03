/*
  ------------------------
  NetWizard - Demo Example
  ------------------------

  Skill Level: Beginner

  This example provides with a bare minimal app with
  NetWizard WiFi manager and captive portal functionality.

  Github: https://github.com/ayushsharma82/NetWizard
  WiKi: https://docs.netwizard.pro

  Works with following hardware:
  - ESP8266
  - ESP32
  - RP2040 (with WiFi) (Example: Raspberry Pi Pico W)


  Important note for RP2040 users:
  - RP2040 requires LittleFS partition for saving credentials.
    Without LittleFS partition, the app will fail to persist any data.
    Make sure to select Tools > Flash Size > "2MB (Sketch 1MB, FS 1MB)" option.
  - If using bare RP2040, it requires WiFi module like Pico W for NetWizard to work.

  -------------------------------

  Upgrade to NetWizard Pro: https://netwizard.pro

*/

#if defined(ESP8266)
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <AsyncTCP.h>
#elif defined(RP2040)
  #include <AsyncTCP_RP2040W.h>
#endif
#include <ESPAsyncWebServer.h>
#include <NetWizard.h>


AsyncWebServer server(80);

// Initialize NetWizard
NetWizard NW(&server);

// Setup configuration parameters
NetWizardParameter nw_header(&NW, NW_HEADER, "MQTT");
NetWizardParameter nw_divider1(&NW, NW_DIVIDER);
NetWizardParameter nw_mqtt_host(&NW, NW_INPUT, "Host", "", "mqtt.example.com");
NetWizardParameter nw_mqtt_port(&NW, NW_INPUT, "Port", "1883");

void setup(void) {
  delay(3000);
  Serial.begin(115200);
  Serial.println("");

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

    Serial.printf("NW connection status changed: %s\n", status_str);
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

    Serial.printf("NW portal state changed: %s\n", state_str);
  });

  // Start NetWizard
  NW.autoConnect("NetWizard Demo", "");
  
  // Check if configured
  if (NW.isConfigured()) {
    Serial.println("Device is configured");
    // Check if we are connected to WiFi
    if (NW.getConnectionStatus() == NetWizardConnectionStatus::CONNECTED) {
      // Print network details
      Serial.print("Connected to ");
      Serial.println(NW.getSSID());
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());;
    } else {
      Serial.println("Not connected to any WiFi");
    }
  } else {
    Serial.println("Device is not configured");
  }

  // Demo Route
  server.on("/demo", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is NetWizard Demo.");
  });

  // Start WebServer
  server.begin();
}

void loop(void) {
  // NetWizard Loop Task
  NW.loop();
}