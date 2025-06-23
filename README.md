# 🛡️ Guardian 360 — Smart Emergency Detection & Alert System

**Guardian 360** is a real-time, multi-sensor emergency detection system that safeguards your home or facility from gas leaks, fires, and unauthorized intrusions. It combines the power of **Arduino**, **NodeMCU**, **DFPlayer**, **SIM800L**, **GPS**, and **Blynk IoT** to provide instant alerts via SMS, audio, and live app notifications.

---

## 🌟 Why Guardian 360?

- ✅ **All-in-One Safety**: Detects gas leaks, fire, motion, and intrusion in a single compact device
- 📍 **Accurate Location Sharing**: Sends real-time GPS coordinates via SMS
- 📲 **Instant Alerts**: Voice alerts, buzzer sirens, SMS to fire/police/user, and app notifications
- 🔊 **DFPlayer Voice Playback**: Plays pre-recorded emergency messages during incidents
- 👁️ **Smart Motion Detection**: Captures snapshot and sends to Blynk with image link
- ⚡ **DIY & Cost-Effective**: Built with affordable, widely available components
- 🔋 **Battery Operated & Safe**: Includes charging protection, regulated output, and power backup
- 🛜 **Expandable Architecture**: Designed for future integration with ESP32-CAM and cloud services

![Guardian 360](https://user-images.githubusercontent.com/demo/guardian360.png)

---

## ⚙️ Features

- 🔥 **Gas & Flame Detection** — using MQ6 and flame sensors
- 🔊 **Audible Siren & Voice Alert** — via DFPlayer Mini and buzzer
- 🛰️ **Live GPS Location** — embedded in alert message
- 📩 **SMS Alerts** — auto-sent to emergency contacts via SIM800L
- 👁️ **Motion Detection** — with PIR sensor on NodeMCU
- 📷 **Snapshot Upload on Intrusion** — imgbb-hosted and linked in Blynk app
- 🖥️ **Blynk IoT Monitoring** — push notifications and visual feed
- 🎥 **ESP32-CAM Support** — optional real-time video stream via motion trigger
- 🔋 **Battery Powered** — via TP4056 and buck converter for field deployment

---

## 🔧 Hardware Required

| Component                 | Quantity |
|---------------------------|----------|
| Arduino UNO               | 1        |
| NodeMCU (ESP8266)         | 1        |
| SIM800L GSM Module        | 1        |
| DFPlayer Mini + Speaker   | 1        |
| GPS Module (NEO-6M)       | 1        |
| MQ6 Gas Sensor            | 1        |
| Flame Sensor              | 1        |
| PIR Motion Sensor         | 1        |
| ESP32-CAM (optional)      | 1        |
| LEDs, Buzzer, Breadboard  | as needed |
| TP4056 Charging Module    | 1        |
| LM2596 / AMS1117 Regulator| 1 each   |

---

## 🚨 Alert Channels

| Channel      | Triggered By            | Method         |
|--------------|--------------------------|----------------|
| SMS          | Gas/Flame Detection      | SIM800L        |
| Voice Alert  | Gas/Fire Detection       | DFPlayer Audio |
| Siren        | Any Emergency            | PWM Buzzer     |
| Blynk Notify | Motion Detection         | NodeMCU Wi-Fi  |
| Snapshot     | Motion Detection         | imgbb + Blynk  |

---

## 🛠️ Setup Guide

### 1️⃣ Clone the Repository
```bash
git clone https://github.com/yourusername/guardian-360.git

2️⃣ Upload Arduino Code (Emergency Controller)

Open guardian_arduino.ino in Arduino IDE

Install the required libraries:

TinyGPS++

SoftwareSerial

DFRobotDFPlayerMini


Connect Arduino UNO and upload the sketch


3️⃣ Upload NodeMCU Code (Motion + IoT Handler)

Open guardian_nodemcu.ino in Arduino IDE

Install libraries:

ESP8266WiFi

ESP8266HTTPClient

base64


Replace:

YOUR_WIFI, YOUR_PASSWORD

YOUR_BLYNK_TOKEN

YOUR_IMGBB_API_KEY


Upload to NodeMCU



---

📷 Optional: ESP32-CAM Integration

For live video streaming and surveillance snapshots via motion trigger, integrate ESP32-CAM using the esp32-cam-motion.ino file (coming soon).


---

🔋 Power Design Summary

SIM800L → 3.7V–4.2V via AMS1117 or Li-ion cell (⚠️ avoid direct 5V)

Arduino/NodeMCU → 5V regulated from LM2596 Buck Converter

Charging Circuit → TP4056 with battery protection

ESP32-CAM → Dedicated 5V/2A USB or battery



---

🧠 Use Cases

🔐 Home & Office Intrusion Detection

🚨 Fire Early Warning System

🧪 Industrial Gas Leak Monitoring

👵 Elderly Care Monitoring with Emergency Alert

📷 Smart IoT Surveillance System



---

🏷️ Tags

arduino iot nodemcu esp8266 smart-home fire-alarm
gas-detector gsm dfplayer emergency-system blynk
esp32-cam motion-detection sos-alert home-security


---

🧪 License

This project is licensed under the MIT License — see the LICENSE file for details.


---

✍️ Author

Made with 💡 and purpose by U Chethan Raj
Want to contribute or deploy it in the field? Fork it, modify it, and build better safety together!
