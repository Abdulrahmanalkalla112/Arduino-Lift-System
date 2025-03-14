# Arduino-Lift-System
The Arduino Lift System is an elevator simulation controlled by an Arduino Uno/Nano and powered by a stepper motor with a driver. Users can select floors using push buttons, and the system detects the lift’s position via limit switches (normally open sensors). The lift moves precisely to the selected floor and stops automatically upon reaching its destination.."# Arduino Lift System 🚀


## 📌 Features
- Supports 6 floors (0-5)
- Uses stepper motor driver for precise movement
- Button-based floor selection with debounce logic
- Floor detection via normally open (NO) sensors

## 🛠️ Components
- Arduino Uno/Nano
- Stepper motor & driver (e.g., A4988)
- Limit switches as floor sensors
- Push buttons for floor selection

## 📜 Code Explanation
The `lift_system.ino` file controls:
- Button press detection
- Stepper motor movement
- Floor detection & safety checks

## 🚀 Installation
1. Upload `lift_system.ino` to Arduino.
2. Connect stepper driver & buttons.
3. Power on and test.

## 📖 License
This project is open-source under the MIT License.
