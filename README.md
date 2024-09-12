<img src="assets/ISA.svg" width=200 align="right">

# ISA - Input Sound A
This is a Sound Sensor measuring **Sound Waves** 
| Specifications | |
| --: | :--: |
| Communication | I²S |
| ChipSet | TDK InvenSense ICS-43434|
| Datasheet | [.pdf](https://invensense.tdk.com/wp-content/uploads/2016/02/DS-000069-ICS-43434-v1.2.pdf) |
| Suggested Arduino Library | ESP32 Built-In |

### Features
| Specifications | High Performance Mode | Low Power Mode|
| --: | :--: | :--: |
| Sensitivity | −26 dB FS ±1 dB | −26 dB FS ±1 dB | 
| SNR |  65 dBA| 64 dBA | 
| Current| 490 μA | 230 μA | 
| AOP | 120 dB SPL | 120 dB SPL  | 
| Sample Rate| 23 – 51.6 kHz | 6.25 – 18.75 kHz | 
| Precision | 24-bit data| 24-bit data| 
| Frequency response | from 60 Hz to 20 kHz| from 60 Hz to 20 kHz| 
| Power supply rejection|  −100 dB FS| −100 dB FS| 


## I²S Connection
The xChip does not have an I²S connection so the Serial Port is reused for I²S:
- **WS** is connected to **TX**, (CWA v2: pin **43**)
- **SCK** is connected to **RX**, (CWA v2: pin **44**)
- **SD** is connected to **IO**, (CWA v2: pin **1**)
- The default channel is the **right** channel

The xChip allow for alternative pin use by cutting & soldering the jumpers on the back of the xChip:
- Use I²C instead of Serial Port
  - **WS** is connected to **SDA**, (CWA v2: pin **18**)
  - **SCK** is connected to **SCL**, (CWA v2: pin **19**)  
- Use **left** channel

## I²S Connection WARNING
Because the I²S is connected to the Serial Port, the xChip has to be removed if programming using the [PPU](https://github.com/domino4com/PPU). If programming using the USB port (CWA v2), then the ISA can be kept plugged in.
Also using the Serial Port over the PPU as a Serial Monitor is also impossible, while it works over the USB. Remember to enable USB CDC on Boot, if using the USB port as a serial monitor. 
Finally the PPU can't be plugged in at all while using the ISA.
Because the I²S is also connected to the IO pin used by the [Soil Moisture sensor - IWC](https://github.com/domino4com/IWC), the Soil Moisture sensor cannot be used together with the ISA.
### TL;DR
No PPU and no IWA with the ISA.


# License: 
<img src="assets/CC-BY-NC-SA.svg" width=200 align="right">
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License

[View License Deed](https://creativecommons.org/licenses/by-nc-sa/4.0/) | [View Legal Code](https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode)
