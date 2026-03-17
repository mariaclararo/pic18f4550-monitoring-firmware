# Board Bring-up & Monitoring Firmware (PIC18F4550)

This repository contains the firmware developed for the **Board Bring-up and Validation of Electronic Prototypes** course at UNIFEI. The project focused on the physical assembly, hardware validation, and full-stack firmware development for a monitoring system based on the PIC18 architecture.

## 🚀 Project Scope

The core objective was to perform a complete *bring-up* of a pre-existing PCB design. The goals included:
1. **Soldering & Assembly:** Manual installation of all discrete and integrated components on the PCB.
2. **Hardware Validation:** Continuity testing, power rail verification, and peripheral functional testing.
3. **Firmware Development:** Implementation of low-level drivers and application logic in C.

## 🛠️ Tech Stack & Tools
- **Language:** C
- **Microcontroller:** Microchip PIC18F4550 / PIC18F4520
- **Environment:** MPLAB X IDE
- **Compiler:** XC8 / SDCC
- **Protocols:** I2C (Software & Hardware) and Serial (UART)

## 📋 Key Features

The firmware manages a monitoring system with a complete Human-Machine Interface (HMI):

- **Event-Driven Architecture:** Uses a **Finite State Machine (FSM)** to manage UI screens and alarm conditions efficiently.
- **Real-Time Clock:** Integrated with the DS1307 RTC via I2C for accurate date and time management.
- **Custom Peripheral Drivers:** drivers for:
  - **LCD:** Custom character support and optimized positioning.
  - **Keypad:** Matrix scanning with software-based debouncing.
  - **ADC:** Real-time sensor reading and data processing.
  - **PWM:** Control of external loads and actuators.
- **Alarm System:** Monitoring of high/low thresholds with visual LED signaling and data persistence.
- **Multilingual Support:** Switchable interface between English and Portuguese.

## 📂 Project Structure
- `main.c`: Main entry point and system loop.
- `stateMachine.c/h`: Logic for the system states and transitions.
- `ds1307.c/h` & `i2c.c/h`: RTC communication and I2C protocol implementation.
- `lcd.c/h` & `keypad.c/h`: User interface and input management.
- `adc.c/h` & `pwm.c/h`: Analog signal processing and power control.

