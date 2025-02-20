---
title: Installation
nextjs:
  metadata:
    title: Installation
    description: A step-by-step guide to setup up your system and install NetWizard.
---

In this article you will learn how to get NetWizard installed so that you can use it in your project. Please read this article carefully before using NetWizard.

---

## Dependencies

NetWizard depends on the following dependencies to work properly. Please stricly install the compatible versions of these dependencies only! Using any other version might break NetWizard or may cause NetWizard to work partially.

### For ESP32

- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) >= **v3.1.0**
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - **v7.3.0**


### For RP2040 + W (Example: RaspberryPi Pico W)

- [Arduino Pico Core](https://github.com/earlephilhower/arduino-pico) - **v4.4.3**
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - **v7.3.0**
- [Preferences](https://github.com/vshymanskyy/Preferences) - **v2.1.0**

### For RP2350 + W (Example: RaspberryPi Pico 2W)

- [Arduino Pico Core](https://github.com/earlephilhower/arduino-pico) - **v4.4.3**
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - **v7.3.0**
- [Preferences](https://github.com/vshymanskyy/Preferences) - **v2.1.0**

---

## For Arduino IDE

### 1. Directly Through Arduino IDE (Library Manager)

Go to Sketch > Include Library > Library Manager > Search for "NetWizard" > Install

### 2. Import through Arduino IDE

- Download the [Repository](https://github.com/ayushsharma82/NetWizard/archive/master.zip)
- Go to `Sketch > Include Library > Add .zip Library > Select the downloaded .zip File.`

### 3. Manual Install

#### For Windows:
- Download the [Repository](https://github.com/ayushsharma82/NetWizard/archive/master.zip)
- Extract the .zip in `Documents > Arduino > Libraries > {Place "NetWizard" folder Here}`

#### For Linux:
- Download the [Repository](https://github.com/ayushsharma82/NetWizard/archive/master.zip) 
- Extract the .zip in `Sketchbook > Libraries > {Place "NetWizard" folder Here}`

## For PlatformIO

### Modifications in platformio.ini

As NetWizard supports multiple platforms, before you install/import NetWizard in your PlatformIO projects, it's neccessary to add these following lines in your `platformio.ini` file for your project to compile successfully:

```ini
lib_compat_mode = strict
lib_ldf_mode = deep # This line may or may not be neccessary depending on your project
```

**For ESP32:** Switch to the `pioarduino/platform-espressif32` platform inside your platformio.ini file so that you have the latest Arduino ESP32 core. *Currently, official releases from PIO team of ESP32 platform is stuck on Arduino Core v2 which doesn't have the required features for NetWizard to compile.*

```ini
platform = https://github.com/pioarduino/platform-espressif32/releases/download/53.03.10/platform-espressif32.zip
```

### 1. Import through PlatformIO

Go to Libraries tab in PIO > Search for "NetWizard" > Import in your project

### 2. Manual Install

- Download the [Repository](https://github.com/ayushsharma82/NetWizard/archive/master.zip)
- Extract the .zip in your project's `lib` folder
