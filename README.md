# Green Fields, Smart Yields: Precision Agriculture Empowered by LoRa Wireless Sensor Networks

## Overview
This project utilizes LoRa wireless sensor networks to enable precision agriculture by gathering data from various sensors and transmitting it wirelessly for analysis. The collected data includes temperature, humidity, motion detection, distance measurements using an ultrasonic sensor, and control of a servo motor.

## Components Used
- Arduino Uno
- LoRa module
- DHT11 temperature and humidity sensor
- PIR motion sensor
- Ultrasonic sensor
- Servo motor

## Setup
The Arduino board is equipped with the necessary sensors and actuators to collect and transmit data. The LoRa module enables long-range communication between the device and a central server or data collection point.

## Code
The code is written in C++ using the Arduino IDE. It initializes the sensors and LoRa module in the setup() function and continuously collects data from the sensors in the loop() function. The data is then formatted and transmitted via the LoRa module.

## Data Collected
1. **DHT11 Sensor**: Measures temperature and humidity levels in the environment.
2. **PIR Motion Sensor**: Detects motion and sends alerts when motion is detected or stopped.
3. **Ultrasonic Sensor**: Measures distance using sound waves and transmits the distance data.
4. **Servo Motor**: Controls the movement of the servo motor from 0 to 180 degrees and back.

The collected data can be used for monitoring environmental conditions, detecting intruders or wildlife, and controlling physical devices remotely.

## Future Enhancements
- Integration with a web or mobile application for remote monitoring and control.
- Add more sensors for comprehensive agricultural monitoring including soil moisture, light intensity, and air quality.

## Video Demonstration: 
URL: https://www.youtube.com/watch?v=deF0g87tDbU
