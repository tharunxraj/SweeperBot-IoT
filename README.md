# 🤖 SweeperBot-IoT
### Autonomous Floor Cleaning Robot with Dual-Mode Operation (Auto + WiFi Manual Control)

![Arduino](https://img.shields.io/badge/Arduino-Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-blue?style=for-the-badge)
![IoT](https://img.shields.io/badge/IoT-WiFi%20Enabled-green?style=for-the-badge)
![MIT License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

---

## 📌 Overview

**SweeperBot-IoT** is a low-cost, intelligent autonomous floor-cleaning robot that supports both **automatic navigation mode** and **manual WiFi control mode**. It combines embedded systems, IoT, and motor control to perform **simultaneous sweeping and mopping** with smart obstacle avoidance.

Designed for homes, offices, classrooms, and small commercial spaces — making daily floor cleaning effortless.

---

## ✨ Features

- 🔁 **Dual Mode Operation** — Switch between Autonomous and Manual (WiFi) mode
- 🚧 **Smart Obstacle Detection** — Ultrasonic sensor stops/redirects robot on detecting objects
- 🧹 **Wet + Dry Cleaning** — Simultaneous sweeping and mopping
- 📱 **MIT App Inventor Control App** — Android app for real-time WiFi control
- ⚙️ **6-Wheel Drive System** — Superior stability and balance on all floor surfaces
- 💡 **Energy Efficient** — Low power consumption with 12V 1.3A battery
- 🔌 **Regulated Power Supply** — LM2596 step-down converter for stable 5V output

---

## 🛠️ Hardware Components

| Component | Specification | Qty |
|-----------|--------------|-----|
| Arduino Nano | Microcontroller (Main Controller) | 1 |
| NodeMCU ESP8266 | WiFi Module (IoT Communication) | 1 |
| LM2596 | DC-DC Step Down Converter (12V → 5V) | 1 |
| 12V Battery | 1.3A Rechargeable Power Supply | 1 |
| L298D | Motor Driver (Speed & Direction Control) | 1 |
| Two Channel Relay Module | Controls Pump & Clean Motor | 1 |
| DC Gear Motor (100 RPM) | Wheel Drive Motors | 6 |
| Cleaning Motor (10 RPM) | Brush/Sweeping Motor | 2 |
| Pump Motor | Water Pump for Mopping | 1 |
| Ultrasonic Sensor (HC-SR04) | Obstacle Detection | 1 |

---

## 📁 Project Structure

```
SweeperBot-IoT/
│
├── src/
│   └── sweeperbot_main.ino        # Main Arduino source code
│
├── app/
│   └── SweeperBot_Control.aia     # MIT App Inventor source file
│   └── SweeperBot_Control.apk     # Android APK (ready to install)
│
├── docs/
│   └── circuit_diagram.png        # Full wiring/circuit diagram
│   └── project_report.pdf         # Detailed project report
│   └── demo_video_link.txt        # Link to demo video
│
├── images/
│   └── robot_front.jpg            # Robot front view
│   └── robot_side.jpg             # Robot side view
│   └── app_screenshot.jpg         # Control app screenshot
│
├── README.md
└── LICENSE
```

---

## ⚙️ How It Works

### 🔄 Automatic Mode (MainSW = HIGH)
1. Robot powers on and initializes all components
2. Ultrasonic sensor continuously scans for obstacles
3. If path is clear → moves forward automatically
4. If obstacle detected within **10 cm** → turns left to avoid
5. Cleaning motor and pump motor operate simultaneously

### 📱 Manual Mode (MainSW = LOW)
1. NodeMCU ESP8266 connects to WiFi
2. MIT App Inventor Android app sends commands via WiFi
3. User controls direction and cleaning functions in real time

### 📡 App Control Commands

| Command | Action |
|---------|--------|
| `f` | Move Forward |
| `b` | Move Backward |
| `l` | Turn Left |
| `r` | Turn Right |
| `s` | Stop |
| `con` | Turn ON Cleaning Motor |
| `coff` | Turn OFF Cleaning Motor |
| `pon` | Turn ON Pump Motor |
| `poff` | Turn OFF Pump Motor |

---

## 🔌 Circuit Overview

- **Arduino Nano** → Controls motors (via L298D), ultrasonic sensor, relay module
- **NodeMCU ESP8266** → Connected to Arduino via SoftwareSerial (TX=0, RX=1)
- **LM2596** → Steps down 12V battery to 5V for Arduino & ESP8266
- **L298D Motor Driver** → ENA (Pin 5), ENB (Pin 10), Motor pins (6,7,8,9)
- **Ultrasonic Sensor** → TRIG (A4), ECHO (A5)
- **Relay Module** → Clean Motor (A0), Pump Motor (A1)
- **Main Switch** → Pin 3 (INPUT_PULLUP) — toggles Auto/Manual mode

> 📷 See `/docs/circuit_diagram.png` for the full wiring diagram.

---

## 📲 App Setup (MIT App Inventor)

1. Download `SweeperBot_Control.apk` from the `/app` folder
2. Enable **Unknown Sources** on your Android device
3. Install the APK
4. Connect your phone to the **same WiFi network** as the NodeMCU
5. Enter the **NodeMCU IP address** in the app
6. Start controlling the robot!

> Or open `SweeperBot_Control.aia` in [MIT App Inventor](https://appinventor.mit.edu/) to view/edit the source.

---

## 💻 Arduino Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Connect Arduino Nano via USB
3. Open `src/sweeperbot_main.ino`
4. Select Board: **Arduino Nano**
5. Select Processor: **ATmega328P (Old Bootloader)** *(if needed)*
6. Upload the code

### Libraries Required
- `SoftwareSerial.h` *(built-in with Arduino IDE)*

---

## 📊 Performance Results

- ✅ Successful obstacle detection and avoidance at ≤ 10 cm range
- ✅ Stable 6-wheel drive on tiles, marble, and rough surfaces
- ✅ Simultaneous wet and dry cleaning achieved
- ✅ Real-time WiFi control via Android app
- ✅ Low power consumption — suitable for 12V 1.3A battery runtime
- ✅ Smooth mode switching between Auto and Manual

---

## 🚀 Future Enhancements

- [ ] AI-based path planning and room mapping
- [ ] Automatic docking and charging station
- [ ] Mobile app with live camera feed
- [ ] Gyroscope for improved navigation accuracy
- [ ] Scheduled cleaning via mobile app
- [ ] Larger water tank with auto-refill detection

---

## 👨‍💻 Author

> Built as part of an embedded systems & IoT project.  
> Feel free to fork, improve, and contribute!

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

⭐ **If you found this project helpful, please give it a star!**
