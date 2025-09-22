# Line Follower Robot

A microcontroller-based **line follower robot** project developed as part of a robotics course.  
The robot uses infrared sensors to detect a black line and follows it using two different control strategies.

---

## 🚀 Features
- **Bang-Bang Control**  
  Simple logic-based control:
  - Both sensors on line → go straight  
  - Left sensor on line → turn left  
  - Right sensor on line → turn right  
  - No line detected → short reverse  

- **Proportional Control (P-Regler)**  
  Smooth steering using proportional correction based on sensor error.

- **Failsafe**  
  If no valid input is detected, motors stop to avoid uncontrolled motion.

---

## 🛠️ Hardware
- Arduino Nano (ATmega328P)
- 2 × IR sensors (line detection)
- 2 × DC motors with motor driver
- Power supply (Li-ion battery pack)
- Track with black line on white background

---

## 📂 Repository Contents
- `code/` → Source code (Arduino)
- `README.md` → This project description
- `LICENSE` → License file (MIT by default)

---

## 🔧 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR-USERNAME/line-follower-robot.git
   ```
2. Open the code in Arduino IDE (or compile with AVR-GCC).
3. Connect the hardware (sensors + motors).
4. Upload the firmware to Arduino Nano.
5. Place the robot on the track and watch it follow the line!

---

## 📖 License
This project is licensed under the **MIT License** – free to use, modify, and distribute.
