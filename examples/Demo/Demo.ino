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

#include <WebServer.h>
#include <NetWizard.h>

WebServer server(80);

// Initialize NetWizard
NetWizard NW(&server);

// Setup configuration parameters
NetWizardParameter nw_header(&NW, NW_HEADER, "MQTT");
NetWizardParameter nw_divider1(&NW, NW_DIVIDER);
NetWizardParameter nw_mqtt_host(&NW, NW_INPUT, "Host", "", "mqtt.example.com");
NetWizardParameter nw_mqtt_port(&NW, NW_INPUT, "Port", "", "1883");

void setup(void) {
  delay(3000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Starting NetWizard Demo...");

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

    Serial.printf("NW portal state changed: %s\n", state_str);
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

  // Start WebServer
  server.begin();
}

void loop(void) {
  // Handle WebServer
  server.handleClient();

  // NetWizard Loop Task
  NW.loop();
}