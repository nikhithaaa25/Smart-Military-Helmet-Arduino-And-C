# Smart-Military-Helmet-Arduino-And-C
# Smart Helmet Monitoring System

## Overview
The **Smart Helmet Monitoring System** is an Arduino-based project designed to monitor a soldier's or worker’s vital parameters in real-time. It tracks **temperature**, **gas concentration**, and **heart rate**, providing immediate alerts through a **buzzer** and displaying readings on an **LCD screen**. The system also logs the location using simulated GPS coordinates. This project can help improve safety in hazardous environments.

## Features
- Real-time monitoring of:
  - Body temperature
  - Gas levels (MQ gas sensor)
  - Heart rate (potentiometer or real sensor)
- Alerts with buzzer when thresholds are crossed
- LCD display for quick reference
- GPS location simulation for tracking
- Data can be logged and visualized in Python

## Components
- Arduino Uno
- LM35 Temperature Sensor
- MQ Gas Sensor
- Potentiometer (for Heart Rate simulation and LCD backlight)
- Buzzer
- Pushbutton (for GPS cycling)
- LCD 16x2 Display
- Breadboard and jumper wires

## Installation
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Connect your sensors and modules to Arduino according to the circuit diagram.
3. Upload the `smartHelmet1.ino` code to the Arduino.
4. For data visualization, install Python 3 and required libraries:
   ```bash
   pip install matplotlib
5. Run the Python script to visualize sensor data and alerts.
