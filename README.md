# R307 Fingerprint Sensor Based Door Lock System

An Arduino-based biometric door lock system using a fingerprint sensor, LCD display, buzzer, LEDs, and an electronic lock. The system verifies fingerprints and grants access only to authorized users.

This project is useful for learning biometric authentication, embedded systems, and Arduino-based security systems.

---

# Features

• Fingerprint authentication using a biometric sensor
• Access control with specific allowed fingerprint IDs
• LCD display for system status
• Buzzer feedback for granted and denied access
• Green and red LED indicators
• Electronic lock control (solenoid or relay)
• Optional mode to allow any registered fingerprint

---

# Hardware Required

• Arduino UNO / Nano
• Fingerprint Sensor (R307 / R305 / AS608)
• 16x2 LCD with I2C module
• Electronic Door Lock / Solenoid Lock
• Buzzer
• Green LED
• Red LED
• Resistors for LEDs (220Ω recommended)
• Power supply (12V for solenoid lock if used)
• Connecting wires

---

# Pin Connections

Fingerprint Sensor

VCC → 5V
GND → GND
TX → Arduino Pin 2
RX → Arduino Pin 3

LCD I2C

VCC → 5V
GND → GND
SDA → A4
SCL → A5

Output Devices

LOCK_PIN → Arduino Pin 12
BUZZER → Arduino Pin 8
GREEN LED → Arduino Pin 9
RED LED → Arduino Pin 10

---

# Access Control Mode

The system supports two access modes.

Mode 0
Any fingerprint stored in the sensor will unlock the door.

Mode 1
Only specific fingerprint IDs are allowed.

Example configuration in the code:

```
#define ACCESS_MODE 1

int allowedIDs[] = {1,3,5};
int totalIDs = 3;
```

Only fingerprints with ID **1, 3, and 5** will unlock the door.

---

# System Working

1. The LCD displays "Place Finger".
2. The fingerprint sensor scans the finger.
3. The system compares the fingerprint with stored templates.
4. If the fingerprint matches an allowed ID:

   * Green LED turns ON
   * Buzzer beeps twice
   * Door lock activates for 3 seconds
5. If the fingerprint is not authorized:

   * Red LED stays ON
   * Long buzzer sound indicates access denied

---

# Libraries Used

Install the following libraries from Arduino Library Manager.

Adafruit Fingerprint Sensor Library
LiquidCrystal I2C Library
SoftwareSerial Library (built-in)

---

# Schematic

The full schematic diagram is included in this repository.

See the file:

schematic.png

---

# Installation

1. Clone or download this repository

```
git clone https://github.com/nabatechworld/R307-Finger-Print-Sensor-Based-Door-Lock-System.git
```

2. Open the Arduino sketch.

3. Install required libraries.

4. Upload the code to your Arduino board.

---

# Applications

• Home security system
• Office access control
• Lab equipment security
• Smart locker systems
• Student electronics projects

---

# Author

Nadimul Huq Zulas
Founder & CEO
Naba Tech World

YouTube: https://www.youtube.com/@nabatechworld

---

# License

This project is open-source and free to use for learning and development.
