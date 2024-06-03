---
title: Async Mode
nextjs:
  metadata:
    title: Async Mode
    description: Learn how to enable async mode in NetWizard.
---

One of the features of NetWizard is the async mode, which provides asynchronous web server functionality for handling HTTP requests for the captive portal. This mode should only be enabled if you are strictly using ESPAsyncWebServer library in your sketch/firmware.

---

## Dependencies

Async mode depends on the following libraries. Please make sure you have installed these specific versions for a crash-free experience. *We use fork of AsyncWebServer from [mathieucarbou](https://github.com/mathieucarbou) which are stable and maintained regularly.*

<!-- ### For ESP8266

- (mathieucarbou) [esphome-ESPAsyncTCP](https://github.com/mathieucarbou/esphome-ESPAsyncTCP#v2.0.0) - **v2.0.0**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.5) - **v3.0.5** -->

### For ESP32

- (mathieucarbou) [AsyncTCP](https://github.com/mathieucarbou/AsyncTCP#v3.1.4) @ **v3.1.4**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.5) - **v3.0.5**

### For RP2040+W

- (khoih-prog) [AsyncTCP_RP2040W](https://github.com/khoih-prog/AsyncTCP_RP2040W#v1.2.0) @ **v1.2.0**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.5) - **v3.0.5**

---

## Enabling Async Mode

Async mode is enabled by setting the `NETWIZARD_USE_ASYNC_WEBSERVER` macro. Use the approach applicable to your setup:

### For Arduino IDE

1. Go to your Arduino libraries directory
2. Open `NetWizard` library folder and then open `src` folder
3. Locate the `NETWIZARD_USE_ASYNC_WEBSERVER` macro in the `NetWizard.h` file, and set it to `1`:

   ```cpp
   #define NETWIZARD_USE_ASYNC_WEBSERVER 1
   ```

4. Save the changes to the `NetWizard.h` file.

5. You are now ready to use NetWizard in async mode, utilizing the ESPAsyncWebServer library.

### For PlatformIO

If you use PlatformIO then we can use a neat trick! You can set `build_flags` in your `platformio.ini` file that enables async mode of NetWizard for your specific project.

1. Open `platformio.ini` file of your project
2. Paste this line `build_flags=-DNETWIZARD_USE_ASYNC_WEBSERVER=1` at bottom
3. Done!

PlatformIO will now compile NetWizard in async mode!

---

## Benefits of Async Mode

Enabling async mode for NetWizard offers several advantages:

1. **Non-blocking Operation:** In async mode, NetWizard leverages the asynchronous web server capabilities of ESPAsyncWebServer. This means that HTTP requests won't block your device's main loop. It allows your device to continue executing other tasks while handling HTTP requests in the background.

2. **Improved Responsiveness:** Your device can remain responsive to user interactions or other processes during requests in the background, ensuring a smoother user experience.

3. **Improved Compatibility:** There are a lot of projects and libraries that still AsyncWebServer, therefore this increases NetWizard compatibility to work for you in any case.
