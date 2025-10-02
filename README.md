# Line Follower Robot

![License](https://img.shields.io/badge/license-MIT-green.svg)
![Top language](https://img.shields.io/github/languages/top/LeoTomy/Line-Follower-Robot)

## 📖 Overview
A microcontroller-based **line follower robot** built with Arduino/AVR.  
The robot uses infrared (IR) sensors to detect a black line on a white surface and controls its motors using two strategies:
- **Bang-Bang Control** → simple left/right logic  
- **Proportional Control (P-Regler)** → smoother corrections based on error  

This project was developed as part of a robotics/microcontroller course and demonstrates real-time sensor integration, motor control, and basic robotics algorithms.

---

## 🧭 Demo
📷 Robot hardware setup:  
![Line Follower Robot](docs/robot.jpg)

🎥 Demo video:  
https://youtu.be/47YR9N_rXyM



---

## 🔧 Required Hardware
- Arduino Nano (ATmega328P)
- 2 × IR line sensors
- 2 × DC motors + motor driver (e.g., L298N, TB6612, or similar)
- Battery pack (7.4–12V recommended)
- Robot chassis + wheels
- Potentiometer (for calibration)
- Wires and breadboard/PCB for connections

---

## ⚙️ Features
- Two control modes:
  - **Bang-Bang Control:**  
    - Left sensor on line → turn left  
    - Right sensor on line → turn right  
    - Both on line → go straight  
    - No line detected → short reverse
  - **Proportional Control (P-Regler):**  
    Smooth correction using proportional gain (Kp) for motor speed adjustment
- Safety stop if no valid sensor input detected
- Threshold calibration with EEPROM storage
- PWM motor control via timers

---

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/LeoTomy/Line-Follower-Robot
2. Open the code in Arduino IDE (or compile with AVR-GCC).
3. Connect the hardware (sensors + motors).
4. Upload the firmware to Arduino Nano.
5. Place the robot on the track and watch it follow the line!

---

## 📖 License
This project is licensed under the **MIT License** – free to use, modify, and distribute.
