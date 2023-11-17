# ESP-WROVER-KIT V4.1 firmware for HORIZOP Energy's EV Charging Station AC Prototype 1 (ECSACP1)


<ins> Preliminary Information on our Electric Charging Station AC Prototype: </ins>
Our current AC Electric Charging Station prototype (ECSACP1) features the following specifications:
AC Input:
- Phase/Lines: 3-phase + Neutral + PE or 1-phase + PE
- Voltage Range: 400V or 220-240V, 50Hz
- Nominal Input Current Power: from [16A to 32A]
- Nominal Input Power: 30KVA
AC Output:
- Current Range: from [16A to 32A] (depending on the plug)
- Rated AC Output Power:
  - 3.4kW (1-phase, 16A)
  - 7.4kW (1-phase, 32A)
  - 22kW (3-phase, 32A)
- Socket: IEC62196-2 Type 2 Female
- RCD: Chint 63A 4-Pole (3-phase + Neutral) 30mA Type B RCD

For the charge controller, this prototype is based on the ESP-WROVER-KIT V4.1 which is an ESP32-based development board produced by Espressif. It features the following integrated components:
- ESP32-WROVER-E module
- LCD screen
- microSD card slot
- Wi-Fi® 2.4GHz 802.11 b/g/n
- Bluetooth Low Energy (BLE)
- Interface Types: JTAG, SPI, UART, USB
- More information about ESP-WROVER-KIT V4.1 can be found here: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-wrover-kit.html


We built the ECSACP1 to have the following abilities:
- Tell the car at which charging speed (0 means off) it can charge via the Pilot Control signal
- Switch on/off the main contactor
- Read back the car's charging state from the Pilot Control signal
- Detect the type of cable plugged in via the Proximity Pilot signal
- Measure the actual current draw for all three phases
- Measure voltage on all three phases
- Use an ESP-WROVER-KIT V4.1 which has the required 8 analog inputs, WiFi, and an LCD screen to serve as a Graphical User Interface (GUI)


# HORIZOP Energy's ECSACP1 Firmware:
- Is based on ESP-IDF
- Has Over-The-Air (OTA) firmware updates. So no need to open the enclosure each time
- Uses IP/TCP to connect to the server via WiFi and keep the connection alive (re-connect if timeout)
- Listens for events from the car and the server simultaneously
- Upon state change from the EV, pushes notification to the server immediately
- All logging is buffered locally in RAM first and then transferred to the server for long-term storage/debugging
- Handles the Control Pilot (CP):
  - Drive signal as requested by server
  - Notify server as soon as a change in voltage is detected
- Measures and reports Proximity Pilot (PP) to the server
- Measures and reports real-time charging load (voltage & current) for all three phases
- Able to handle the following types of requests from the server:
  - Gets all data
  - Installs new firmware: over-the-air firmware upgrades
  - Switches on/off contactor
  - Sets max allowed charge rate on Control Pilot at any given point in time. This can be adjusted fluently (even during ongoing charging), and the EV will follow as commanded. This is key to implementing flexible load sharing to balance power between multiple charging stations.
