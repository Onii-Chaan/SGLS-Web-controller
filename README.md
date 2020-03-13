# RayLight controllable RGBW room light

## Table of contents:
- [Usage](https://github.com/Onii-Chaan/SGLS-Web-controller#usage)
- [Libraries used](https://github.com/Onii-Chaan/SGLS-Web-controller#libraries-used)
- [Lamp code](https://github.com/Onii-Chaan/SGLS-Web-controller#lamp-code)
- [Lamp hub code](https://github.com/Onii-Chaan/SGLS-Web-controller#lamp-hub-code)
- [Server code](https://github.com/Onii-Chaan/SGLS-Web-controller#server-code)
- [Main controller web page](https://github.com/Onii-Chaan/SGLS-Web-controller#main-controller-web-page)
- [First time set web page](https://github.com/Onii-Chaan/SGLS-Web-controller#first-time-set-web-page)
- [Communication](https://github.com/Onii-Chaan/SGLS-Web-controller#communication)
- [Saving data](https://github.com/Onii-Chaan/SGLS-Web-controller#saving-data)

## Usage
- This code was developed for RayLight RGBW light bulbs. May be used for addresable led strips with appropriste changes.
- Microcontroller used for hub - ESP32
- Microcontroller used for lamps - ATmega328PB
- Provides all the code necessary for hub, lamps, hub server, communication, web controller pages. 

## Libraries, languages, extensions used
Code was written in C++/Javascript/HTML/CSS
For microcontroller programming platformIO IDE was used
For programming web pages, Visual Studio code with basic HTML/CSS/JS extensions were used
For uploading webpage data to ESP32, SPIFFS Sketch data upload were used

Libraries used
- Web pages:
  - Web pages run purely on Javascript. No frameworks used, because of limitated SPIFFS storage capacity on ESP32
- Lamps:
  - Arduino.h
- Hub:
  - Arduino.h
  - WiFi.h
  - EEPROM.h
  - ESPmDNS.h
  - AsyncTCP.h
  - WiFiClient.h
  - ESPAsyncWebServer.h
  - SPIFFS.h
  - ArduinoJson.h

## Lamp code
Lamps have to receive UART data on their Rx pin. When lamp receives new data it immediately starts processing it using '''recvWithStartEndMarkers();''' function   

## Lamp hub code

## Server code

## Main controller web page

## First time set web page

## Communication
- For communication with hub, lamps use UART Rx/Tx communication
- Hub works in user local WLAN or directly using softAP, depends on user settings choice

