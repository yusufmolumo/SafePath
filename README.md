# SafeGuard: Emergency SMS Tracker

![SafeGuard Logo](https://via.placeholder.com/150) <!-- Replace with your logo URL if you have one -->

**SafeGuard** is an Arduino-based emergency alert system that sends real-time location data via SMS using an **Arduino Nano**, **A6 GPRS Pro Module**, and **NEO-6M GPS Module**. When triggered by a button press, it delivers precise GPS coordinates, date, time, altitude, speed, and a Google Maps tracking link to a designated phone number—perfect for personal safety applications.

This project was developed as part of **CodeXtreme 2025**, emphasizing high-value, high-impact solutions to enhance community safety.

---

## Features
- **Real-Time Location**: Sends accurate latitude and longitude from the NEO-6M GPS module.
- **Detailed Alerts**: Includes date, time, altitude (meters), speed (km/h), and number of satellites tracked.
- **Google Maps Link**: Provides a live tracking URL based on current GPS coordinates.
- **Simple Trigger**: Single button press activates the SMS alert.
- **Reliable Communication**: Uses the A6 GPRS Pro module for SMS delivery.

---

## Hardware Requirements
- **Arduino Nano** (ATmega328P)
- **A6 GPRS Pro Serial GPRS GSM Module** (with SIM card)
- **NEO-6M GPS Module** (with antenna)
- **Push Button**
- **Breadboard**
- **Jumper Wires**
- **USB Cable** (for Nano programming)
- **Optional**: External 5V 2A power supply (recommended for stability)

---

## Software Requirements
- **Arduino IDE** (latest version recommended)
- **Libraries**:
  - `SoftwareSerial` (pre-installed with Arduino IDE)
  - `TinyGPSPlus` (install via Arduino IDE Library Manager)

---

## Cloning the Repository
To get started, clone this repository to your local machine:

```bash
git clone https://github.com/yusufmolumo/SafePath.git
cd safeguard