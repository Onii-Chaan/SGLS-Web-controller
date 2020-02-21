#include "funcHeader.h"
//SAMAZINAT BAUD RATE UZ 74880

// Load Wi-Fi librarySOFT
// #include <WiFi.h>
// #include <EEPROM.h>
// #include <ESPmDNS.h>
// #include <AsyncTCP.h>

// #include <WiFiClient.h>
// #include <ESPAsyncWebServer.h>
// #include <SPIFFS.h>

// #include <SoftwareSerial.h>
// SoftwareSerial Serial(16, 17); // RX, TX

//#include <SimpleTimer.h>

// #include "index.h"  //Web page header file
//#include "softAPSettings.h"  //softAP settings lapa

//SimpleTimer timer;

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup()
{
  // pinMode(2, OUTPUT);
  Serial.begin(9600);
  // while (!Serial)
    // continue;


  startWifi();
  startEEPROM();
  startServer();
  serverFunctions();
  // setTimerFunctions();
  startSPIFFS();
  startMDNS();
  clearEEPROM(96, 192);

  adrStartEnd[0][0] = 1;
  adrStartEnd[0][1] = numLeds;

  funcNumArr[0] = 1;
  funcParArr[0] = 1;
  isFirstTime[0] = 1;
  blinkOff[0] = 1;
  oldTimeInt[0] = 1;

  // delay(1000);//lai lampas paspetu ieladeties
  Serial.println("<00>");
  // digitalWrite(2, HIGH);
}

void loop()
{
  funcExecute(); //konstanti darbina lampu dinamisko krasu funkcijas
}
