# ADOZ Guitar pedal
Projektni zadatak iz predmeta algoritmi digitalne obrade zvuka (RT-RK 3. godina)

This project implements a **real-time digital guitar pedal** based on the **ESP32** platform.  
The audio signal is digitized using a **PCM1808 24-bit audio ADC**, processed in real time on the ESP32, and then forwarded to the output using **PCM5102 audio DAC**.

---

## Tools
**Platform** io vscode extension
**framework**: ESP-IDF
**platform**: espressif32
**board**: ESP32-wroover

---

## Compile
- Add Platform IO extension to your vs code.
- PlatformIo --> Home --> Open project
- Select "source" directory
- PlatformIo generates needed dependcies and allows upload to ESP32
