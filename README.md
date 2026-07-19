# Web-Controlled Robotic Arm (ESP32)

This project allows you to control a robotic arm (arm + gripper) via a web interface hosted directly on an ESP32. The system operates in **Access Point (AP) mode**, making it completely autonomous: no external Wi-Fi router is required.

## 🚀 Features
- **Autonomous Access Point:** Creates its own Wi-Fi network (`ESP32_Robot_Control`).
- **Smooth Touch Control:** Supports long-press actions for continuous movement on both smartphones and computers.
- **Motion Smoothing:** Uses a gradual progression algorithm to prevent mechanical jerks/jitters.
- **Minimal Configuration:** Uses only native ESP32 libraries and the `ESP32Servo` library.

## 🛠 Required Hardware
- 1x ESP32 (DevKit V1 recommended)
- 2x **SG90 180° Servomotors**
- Power supply for servos (e.g., 5V battery pack)

## 🔌 Wiring
| Component | ESP32 Pin |
| :--- | :--- |
| **Arm Servo (Signal)** | GPIO 10 |
| **Gripper Servo (Signal)** | GPIO 9 |
| **Power (VCC)** | 5V from Battery Pack |
| **Ground (GND)** | GND from Battery Pack & ESP32 |

*Note: Ensure all Ground (GND) pins (ESP32 and Power Supply) are connected together to maintain a common ground.*

## ⚙️ Installation
1. Install the `ESP32Servo` library in your Arduino IDE (via the Library Manager).
2. Copy the provided source code into a new sketch.
3. Upload the code to your ESP32.

## 📱 Usage
1. On your smartphone or computer, scan for available Wi-Fi networks.
2. Connect to the network named **`ESP32_Robot_Control`** using the password: `password123`.
3. Open your web browser and enter the address: **`http://192.168.4.1`**
4. Use the **(+)** and **(-)** buttons to control the arm and gripper.
   - *Hold the button down for continuous, smooth movement.*

## 📝 Technical Details
- The system uses the `millis()` function to manage movements, allowing the web interface to remain responsive while the servos are being controlled.
- To adjust movement speed, modify the `vitesseServo` constant in the code (a lower value increases speed).
