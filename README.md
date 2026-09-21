# Parking_sensor
A project to design and create a functional parking sensor using a RaspberryPi Pico W microcontroller
By Dominik Swieboda, 09/2026

Build 1:
Setting up the logic voltage converter --> No software at this stage hence no build 1 folder in repository

Build 2:
Ultrasound Distance Sensor --> set up and testing of the ultrasound sensor itself
Changes to code: new DISTANCE_SENSOR_OUTPUT() function as well as GPIO 12,13 definition and set-up

Build 3:
LED Implementation --> set up and testing of the LEDs to communicate distance with user
Changes to code: new LED_RESPONSE() function as well as GPIO 4,5,6 definition and set-up

Build 4:
Yellow LED Improvement + Sensor on indicator --> replacing yellow LED with RGB LED for better brightness (difference in hardware only) + turning on the on-board LED when the parking sensor is on
Changes to code: initialisation of cyw43_arch library and setting the wireless chip's pin 0 to HIGH to turn LED on when code is executed

Build 5:
Buzzer Implementation --> set up and testing of the buzzer to communicate distance with user
Changes to code: new BUZZER_RESPONSE() function as well as GPIO 15 definition and set-up
