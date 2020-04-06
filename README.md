Copyright 2020, Onii-Chaan, All Rights Reserved

# RayLight controllable RGBW room lights
# Table of contents:
- [Usage](https://github.com/Onii-Chaan/SGLS-Web-controller#usage)
- [Libraries used](https://github.com/Onii-Chaan/SGLS-Web-controller#libraries-used)
- [Lamp code](https://github.com/Onii-Chaan/SGLS-Web-controller#lamp-code)
- [Lamp hub](https://github.com/Onii-Chaan/SGLS-Web-controller#lamp-hub)
  - [Lamp hub code](https://github.com/Onii-Chaan/SGLS-Web-controller#lamp-hub-code)
  - [Server code](https://github.com/Onii-Chaan/SGLS-Web-controller#server-code)
- [Main controller web page](https://github.com/Onii-Chaan/SGLS-Web-controller#main-controller-web-page)
- [First time set web page](https://github.com/Onii-Chaan/SGLS-Web-controller#first-time-set-web-page)
- [Communication](https://github.com/Onii-Chaan/SGLS-Web-controller#communication)
- [Saving data](https://github.com/Onii-Chaan/SGLS-Web-controller#saving-data)

# Usage
- This code was developed for RayLight RGBW light bulbs. May be used for addresable led strips with appropriste changes.
- Microcontroller used for hub - ESP32
- Microcontroller used for lamps - ATmega328PB
- Provides all the code necessary for hub, lamps, hub server, communication, web controller pages. 

# Libraries, languages, extensions used
Code was written in C++/Javascript/HTML/CSS
For microcontroller programming platformIO IDE was used
For programming web pages, Visual Studio code with basic HTML/CSS/JS extensions were used
For uploading webpage data to ESP32, SPIFFS Sketch data upload were used

##### Libraries used
- Web pages:
  - Web pages run purely on HTML/CSS/Javascript. No frameworks used, because of limitated SPIFFS storage capacity on ESP32
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

# Lamp code
Lamps have to receive UART data on their Rx pin. When lamp receives new data it immediately starts processing it using ```recvWithStartEndMarkers();``` function that runs in ```loop();```. First time receiving data, lamps uses it to get their index and passes its index to next lamp for counting. After counting lamps start to work in their normal mode, using received data to set appropriate PWM output for colors.

##### Received data examples:
  - <\[lampNum]\> sets \[lampNum]\+1 to its index. Two digits to display a number are required. Example: ```<01>```
  - <\[lampNum]\[red]\[green]\[blue]\[white]\> sets lamp color. Three digits for displaying a color number are required. Color ranges from 000 to 255. Example: ```<011202550000010>``` sets *first* lamp red - 120, green - 255, blue - 0, white - 10

All data received must be in ```<>``` brackets 

# Lamp hub
Hub has two main tasks:
1. Send data to lamps through UART
2. Work as server and process incoming data and connections

## Server code
Hub can work two ways - as WiFi Access Point or either connected to user local WiFi network. Server listens for incoming connection and sends files saved on ESP32 file system. Server listens for incoming POST data from webpages and processes it. After receiving POST data, server either saves data in Json file (if for example user saved new color or changed animation parameters, or user pressed turn off button), or sets new lamp colors or animations.

##### Receiving new lamp data:
If server receives POST data with the name "setlamp" it sets received data in ```lamp``` parameter into arrays and variables for sending it to lamps using the same ```recvWithStartEndMarkers();``` function as lamps do, but modified a little. 
Received data from webpage example for setting color: ```lamp=<[dataType][fromLamp]-[toLamp]#[red][green][blue][white]>``` where:
1. ```dataType``` is 0 or 1
  - 0 - color set
  - 1 - animation set
2. ```fromLamp``` is one or two digit number from 1 to 30
3. ```-``` divides start number and end number
4. ```toLamp``` is one or two digit number from 1 to 30 that is bigger or equal to ```fromLamp```
5. ```#``` ends lamp number set 
6. ```red``` three digit number from 000 to 255, sets red color
7. ```green``` three digit number from 000 to 255, sets green color
8. ```blue``` three digit number from 000 to 255, sets blue color
9. ```white``` three digit number from 000 to 255, sets white color

Received data from webpage example for setting animation: ```lamp=<[dataType][fromLamp]-[toLamp]#[funcNum][funcParam]>``` where:
1. ```dataType``` is 0 or 1
  - 0 - color set
  - 1 - animation set
2. ```fromLamp``` is one or two digit number from 1 to 30
3. ```-``` divides start number and end number
4. ```toLamp``` is one or two digit number from 1 to 30 that is bigger or equal to ```fromLamp```
5. ```#``` ends lamp number set 
6. ```funcNum``` two digit number from 00 to 99, sets function number
7. ```funcParam``` three digit number from 000 to 999, sets function parameter

Received POST data with name ```setJson``` from webpage example for saving new user set webpage data:  
```type=action=[actionType]|dataType=[dataTypeValue]|name=[nameValue]``` after which can follow one of several lines:
    - ```|r=[red]|g=[green]|b=[blue]|w=[white]```
    - ```|num=[funcNum]|param=[parameter]```
    - ```|value=[groupValue]```
Where:
- ```type``` is the only POST parameter, because of difficulities with receiving POST data. The ```=``` sign that comes after is the only ```=``` sign for parameters in the received payload, other ```=``` are just values of ```type```. Because such data receiving method were used, ```|``` sign is used instead of ```&``` for dividing parameter values from each other without any further problems. Other strings like ```action=``` are just for giving values their names
1. ```actionType``` may be one of these:
  - ```delete``` deletes data from SPIFFS JSON file
  - ```add``` adds data to SPIFFS JSON file
  - ```edit``` edis data in SPIFFS JSON file
2. ```dataTypeValue``` may be one of these:
  - ```LampGroups``` takes action with ```LampGroups``` SPIFFS JSON array
  - ```FuncArr``` takes action with ```FuncArr``` SPIFFS JSON array
  - ```RgbwArr``` takes action with ```RgbwArr``` SPIFFS JSON array
3. ```name``` is used for assigning or making a new name for something in SPIFFS JSON array 

After comes one of three lines with parameters where:
1. Color set:
  - ```red``` is a 1 to 3 digits long number from 0 to 255 representing red color
  - ```green``` is a 1 to 3 digits long number from 0 to 255 representing green color
  - ```blue``` is a 1 to 3 digits long number from 0 to 255 representing blue color
  - ```white``` is a 1 to 3 digits long number from 0 to 255 representing white color
2. Animation set:
  - ```num``` is a 1 to 2 digits long number from 1 to 99 representing animation number
  - ```param``` is a 1 to 3 digits long number from 1 to 999 representing animation parameter
3. Group set:
  - ```groupValue``` is a string representing start and end value of lamp. Example
    - ```1-12#``` from 1 to 12 
  
## Lamp hub code
Lamp hub works as main lamp controller by sending lamp color data using UART Rx/Tx. After receiving data from Webpage it splits data into corresponding variables and changes global array values. 
Global 2d array ledPartStartEnd follows which lamps should be working in which functions. Regardless of ledPartStartEnd array there are other global arrays, that changes it's values depending on ledPartStartEnd. 
For example: 
ledPartStartEnd is ```{{1,1},{2,5},{6,10},{11,30},{0,0},{0,0},{0,0},...,{0,0}}```
funcNumArr is ```{1,3,2,1,0,0,0...,0}```
- First lamp (```{1,1}```) just turns on color because of funcNumArr[0] (```1```).
- Second to fifth lamp (```{2,5}```) executes third function, because of funcNumArr[0] (```3```)
- Etc. until ledPartStartEnd is ```{0,0}```, meaning that no lamp values are saved there

After setting new data it keeps executing and sending data to lamps using ```funcExecute()```. Each lamp and its group delays are saved in array just like funcNumArr. Data gets sent using ```displayAdrColors()``` function.

# Main controller web page
All webpage files are stored in ESP32 SPIFFS file system.  
Main webpage can work both offline and in user local WiFi net.
Every time loading it loads JSON file that it uses for creating user webpage with all previous changes made, dynamically. 
User can:
- Choose and save new colors
- Choose and save new animations
- Make new lamp groups and save them
- Delete all data created
- Turn on or turn off lamps
- Change some basic options in option menu
    

# First time set web page
When user opens controller page for the first time he has to set local WLAN SSID and password or change softAP credentials (changing softAP credentials is not obligatory if user doesn't want to connect to WLAN, but it's recomended to change default data). For changing this data user has to go to settings page from main page. There user has various options:
- Choose connection mode
  - User can switch hub wifi mode from WLAN to Access Point and vice versa. Hub uses saved JSON data when setting up wlan modes
  - After user hits the "Save" button, data sends to hub in format: 
    - ```type=changeWifi=[wifiMode]```, where ```[wifiMode]``` could be ```softAp``` or ```WLAN``` 
  - Hub saves new data in JSON file and resets WiFi in chosen mode
- Change your WiFi credentials
  - User enters new local WLAN credentials
  - After user hits the "Save" button, data sends to hub in format:
    - ```type=ssid=[newSsid]|pass=[newPassword]|data=wlan```, where ```[newSsid]``` is new WLAN ssid and ```[newPassword]``` is new WLAN password, all other sent data remains constant
  - Hub saves new data and starts WiFi in WLAN mode
- Change your Access Point credentials
  - User enters new Access Point credentials
  - After user hits the "Save" button, data gets sent hub in format: 
    - ```type=ssid=[newSSID]|pass=[newPassword]]|data=softap```, where ```[newSSID]```  is new AP ssid and ```[newPassword]``` is new AP password, all other send data remains constant
  - Hub saves new data and starts WiFi in AP mode
- Change your lamp quantity
  - Users enters a number of connected lamps to hub
  - After user hits the "Save" button, data gets sent hub in format: 
    - ```type=num=[newLampQuantity]|data=newLampCount```, where ```[newLampQuantity]``` is number of currently connected lamps to hub
  - Hub saves new data, and when user returns to main page, it gets loaded according to new changes
# Communication
- For communication with hub, lamps use UART Rx/Tx communication
- Hub works in user local WLAN or directly using softAP, depends on user settings choice

# Saving data
Every time user creates new color, or group, or animation, or turns off lamps, or anything else, data is saved. All user changes are saved and stored in ESP32 SPIFFS file system in json format. ArduinoJSON library is used for this purpose. There are 3 main text files, that stores JSON data. configFile.txt for creating main controller page, default.txt for setting default values for variables, save.txt for last hub variable values. 


