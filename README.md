# ESP32-CAM Covert GPS Reconnaissance Drop-Box

An autonomous, location-aware physical security asset tracking and surveillance node built on the ESP32-CAM architecture and the NEO-6M GPS module. This project serves as a proof-of-concept for hardware penetration testing, demonstrating how low-cost microcontrollers can execute out-of-band visual reconnaissance and inject live satellite telemetry directly into image metadata.

## 🚀 Overview
Upon triggering a capture event, the microcontroller queries the NEO-6M GPS module over UART to parse real-time geospatial coordinates. The system processes the incoming image frame, dynamically injects the precise latitude, longitude, and altitude data directly into the JPEG’s EXIF metadata header, and commits the geotagged file to an onboard MicroSD card. 

The node can operate completely untethered as a physical drop-box, utilizing its independent power source and built-in Wi-Fi connectivity to exfiltrate reconnaissance data away from monitored target networks.

---

## 🛠️ Hardware Architecture

### Components
* **Microcontroller / Sensor:** ESP32-CAM Development Board (with OV2640 Camera Module)
* **Telemetry Sensor:** NEO-6M GPS Module (with ceramic antenna)
* **Storage:** MicroSD Card (formatted to FAT32)
* **Interface:** USB-to-TTL Serial Adapter (for flashing and debugging)

### Schematic Blueprint
To program the board or view live telemetry, connect the hardware according to the following layout:

| ESP32-CAM Pin | NEO-6M GPS Pin | USB-to-TTL Pin | Notes |
| :--- | :--- | :--- | :--- |
| **5V / 3.3V** | VCC | - | Ensure stable power |
| **GND** | GND | GND | Common ground link |
| **GPIO 14 (HS2_CLK)**| - | - | Reserved for MicroSD SPI |
| **GPIO 15 (HS2_CMD)**| - | - | Reserved for MicroSD SPI |
| **GPIO 2 (HS2_DATA)**| - | - | Reserved for MicroSD SPI |
| **GPIO 3 (U0RXD)** | - | TX | Required for flashing firmware |
| **GPIO 1 (U0TXD)** | - | RX | Required for flashing firmware |
| **GPIO 16 (U2RXD)**| TX | - | SoftwareSerial GPS Data Input |
| **GPIO 0** | - | - | **Tie to GND during boot to flash code** |

---

## 📁 Repository Structure
* `/src` — Core Arduino C++ (`.ino`) firmware source code.
* `/docs` — Schematic layout blueprints and metadata specifications.
* `README.md` — Project entry point and documentation.

---

## ⚙️ Core Dependencies
This firmware compiles via the Arduino IDE and targets the ESP32 platform architecture. The following libraries must be installed:
* **TinyGPS++** (by Mikal Hart) — Advanced NMEA sentence parsing.
* **Esp32-cam core libraries** — Frame buffer manipulation and camera control.

---

## 🔒 Security & Penetration Testing Context
In a red-team or auditing environment, this node acts as an **independent physical drop-box**. It showcases:
1. **Covert Physical Surveillance:** Captures high-resolution visual evidence without relying on standard facility infrastructure.
2. **Geofenced Activation:** Validates deployment coordinates natively before activating high-power wireless arrays.
3. **Out-of-Band Exfiltration:** Transmits collected assets over an ad-hoc Wi-Fi Access Point, entirely bypassing local enterprise firewalls, IDSes, or network monitors.
