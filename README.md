# 🏫 ESP32 Classroom Environment Monitoring System (Wi-Fi UDP)

This project presents an IoT-based solution for real-time monitoring of classroom conditions such as temperature, humidity, pressure, and occupancy. It uses two ESP32 boards:  
- An **ESP32-S3** (sensor node) to collect environmental data  
- An **ESP32 with OLED** (display node) to receive and visualize the data

Communication between the two devices is established over **Wi-Fi using the UDP protocol**.

---

## 📂 Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Project Structure](#project-structure)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Design](#circuit-design)
- [How to Set Up](#how-to-set-up)
- [Code Explanation](#code-explanation)
- [Usage](#usage)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

## 🧠 Introduction

Modern classrooms require efficient environmental control systems to ensure optimal learning conditions. This project aims to provide a scalable and cost-effective monitoring solution using ESP32 microcontrollers and basic sensors. It focuses on collecting and displaying key environmental data remotely over a shared Wi-Fi network.

---

## ✨ Features

- Real-time temperature, humidity, and pressure monitoring using BME280
- Occupancy detection using PIR motion sensor
- Wireless communication via UDP
- OLED display visualization on remote ESP32 device
- JSON-based data transmission

---

## 🔧 Hardware Requirements

- 1 × ESP32-S3 development board  
- 1 × ESP32 development board with SPI support  
- 1 × BME280 (Temperature, Humidity, Pressure) sensor  
- 1 × HC-SR501 PIR motion sensor  
- 1 × 1.3" OLED Display (SH1106/SPI)  
- Breadboard and jumper wires  
- USB cables for programming  
- Computer with Arduino IDE installed  

---

## 💻 Software Requirements

- Arduino IDE  
- ESP32 Board Package (via Boards Manager)

### Libraries to Install via Library Manager:

- Adafruit BME280  
- Adafruit Sensor  
- Adafruit GFX  
- Adafruit SH110X  
- ArduinoJson  
- WiFi  
- WiFiUdp  
- Wire  

---

## 🔌 Circuit Design

### ESP32-S3 (Sensor Node):
- **BME280** → I2C  
  - SDA → GPIO 8  
  - SCL → GPIO 9  
- **PIR Motion Sensor**  
  - OUT → GPIO 33

### ESP32 (Display Node):
- **OLED via SPI**  
  - MOSI → GPIO 23  
  - CLK  → GPIO 18  
  - DC   → GPIO 17  
  - RESET → GPIO 16  
  - CS   → GPIO 5

> ⚠️ Both devices must be connected to the **same Wi-Fi network**.

---

## 🚀 How to Set Up

1. Open Arduino IDE and install all required libraries and board packages.  
2. Upload the `sensor_node` code to the ESP32-S3 device.  
3. Upload the `display_node` code to the ESP32 with OLED display.  
4. Open Serial Monitor to check:
   - Sensor node is successfully sending data  
   - Display node is receiving and showing values on the OLED screen  
5. Power both boards and place them in different locations or classrooms.

---

## 🧾 Code Explanation

### Sensor Node (ESP32-S3)
- Reads temperature, humidity, and pressure from BME280 sensor.  
- Detects motion using HC-SR501 PIR sensor.  
- Creates a JSON string with all sensor values.  
- Sends the JSON data to the display node using UDP protocol over Wi-Fi.

### Display Node (ESP32 + OLED)
- Listens for UDP packets on a specific port.  
- Parses the incoming JSON data.  
- Displays the sensor values on the OLED screen in real-time.

---

## 📷 Usage

Once both ESP32 devices are powered and connected:

- The **sensor node** periodically collects data and transmits it wirelessly via UDP.
- The **display node** listens for incoming data, decodes it, and shows:
  - 🌡️ Temperature (°C)  
  - 💧 Humidity (%)  
  - 🧭 Pressure (hPa)  
  - 🚶‍♂️ Motion status (YES / NO)

---
