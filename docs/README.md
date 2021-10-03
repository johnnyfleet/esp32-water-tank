# ESP32 Setup
- [ESP32 Setup](#esp32-setup)
  - [Device](#device)
  - [Pin out Diagram](#pin-out-diagram)
  - [Tips to setup Arduino in VSCode](#tips-to-setup-arduino-in-vscode)
  - [Setup Arduino IDE](#setup-arduino-ide)
    - [Setup ESP32 in ArduinoIDE](#setup-esp32-in-arduinoide)
    - [Fix 'No "Serial" module' issue.](#fix-no-serial-module-issue)
    - [Fix Python issues on Ubuntu](#fix-python-issues-on-ubuntu)
    - [Set baud rate to 9600](#set-baud-rate-to-9600)

This page outlines the tips I've learnt as I've tried to set up an internal weather station to compliment the external station. I started with Arduino IDE but prefer VSCode so quickly ported over to that. 

## Device

I've used the ESP32S Dev kit board. I bought this one from [AliExpress](https://www.aliexpress.com/item/1005001798651086.html?spm=a2g0s.9042311.0.0.3a774c4dBNpL3M).

## Pin out Diagram

This guide is a useful diagram to get the wiring right. Also the names are labelled on tbe bottom. 

![ESP32S Pin Diagram](./images/esp32-pin-diagram.png "ESP32S Pin Diagram")

## Tips to setup Arduino in VSCode

If needing to set up again. My working setup uses platform.io extension to work

1. Follow [these instructions](https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/)
2. Make sure permissions to USB setup right on Manjaro. [This page](https://forum.manjaro.org/t/arduino-ide-dev-ttyacm0-permission-denied/45013) was useful. Specifically:

``` bash
sudo pamac install arduino arduino-avr-core
sudo usermod -a -G uucp $USER     # log out and back in of course
```

## Setup Arduino IDE
This information for reference if wanting to use the ArduinoIDE

### Setup ESP32 in ArduinoIDE
Follow [these instructions](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

Make sure permissions to USB setup right on Manjaro. [This page](https://forum.manjaro.org/t/arduino-ide-dev-ttyacm0-permission-denied/45013) was useful. Specifically:

``` bash
sudo pamac install arduino arduino-avr-core
sudo usermod -a -G uucp $USER     # log out and back in of course
```

### Fix 'No "Serial" module' issue. 

Similar to reported [here](https://github.com/espressif/arduino-esp32/issues/13).

`sudo pip install pyserial`

### Fix Python issues on Ubuntu
https://github.com/espressif/arduino-esp32/issues/13
On ubuntu 20.04 Python2 is gone and Python3 is default. But python program not visible (instead python3). 

Run this to add a symlink

`sudo ln -s /usr/bin/python3 /usr/bin/python`

### Set baud rate to 9600

Check in the code for the serial baud rate set and set up the serial monitor for the same. 

9600 is on the standard program. 
