# ADOZ Guitar pedal
Projektni zadatak iz predmeta algoritmi digitalne obrade zvuka (RT-RK 3. godina)

This project implements a **real-time digital guitar pedal** based on the **ESP32** platform.
The audio signal is digitized using a **PCM1808 24-bit audio ADC**, processed in real time on the ESP32, and then forwarded to the output using **PCM5102 audio DAC**.

---

## Tools
- **PlatformIO**: VS code extension
- **Framework**: ESP-IDF
- **Platform**: espressif32
- **Board**: ESP32-WROVER
- **Modules**: PCM1808 (ADC), PCM5102 (DAC)
- **Display**: Picocom

---

## Compile
1. Add PlatformIO extension to your VS code.
2. Open PlatformIO --> Home --> Open project.
3. Select the "source" directory of the project.
4. PlatformIO generates needed dependcies.
5. Use PlatformIO to build and upload the firmware to your ESP32.

---

## Monitoring effect settings via UART
ESP32 prints all effect states over UART. To monitor them:

1. Install picocom on Linux:

```
sudo apt update
sudo apt install picocom
```

2. Check which USB port your ESP32 is connected to:

```ls /dev/ttyUSB*```

3. Run picocom with the correct port:

```picocom -b 115200 /dev/ttyUSB{port number}```

To exit picocom, press:

```CTRL+a then CTRL+x```

---

## Hardware Scheme

This diagram shows the wiring between the ESP32 and the audio
modules. Potentiometers and buttons used for effect control are not shown.

![Project_scheme](scheme/scheme.png)
