#ifndef HEADERFILE
#define HEADERFILE

#include <Arduino.h>
// Load Wi-Fi librarySOFT
#include <WiFi.h>
#include <EEPROM.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

#include <ArduinoJson.h>
// #include <SoftwareSerial.h>
// struct Config
// {
//   char hostname[64];
//   int port;
//   int userIP;
//   int arrayData[3];
// };

// extern Config config;

extern const char *webdata;

extern AsyncWebServer server;

// SoftwareSerial mySerial(16, 17); // RX, TX



extern int INCREMENTER;
// Replace with your network credentials
//const char* DEFAULT_WLAN_SSID = "esp32";
//const char* DEFAULT_WLAN_PASS = "password";

extern const char* WLAN_SSID;
extern const char* WLAN_PASSWORD;

//const char* WLAN_SSID     = "MyHomeNetV2.0";
//const char* WLAN_PASSWORD = "Rammy12345";
// Set web server port number to 80


#define EEPROM_SIZE 192//EEPROM rezerveta atmina
extern char USER_SSID[32];//saglaba lietotaja wifi nosaukumu eeproma
extern char USER_PASSWORD[32];//saglaba lietotaja paroli eeproma

extern char SOFT_AP_MDNS[32];//saglaba softAP nosaukumu

#define redIn 22
#define greenIn 23
#define blueIn 24

extern const int numLeds; //diozu daudzums, jabut +1, jo medz nokrasot esp
extern const byte colorCount;//krasu daudzums, rgb vai rgbw atbilstosi
extern const byte numChars;

extern bool divide;//mainigais, kas seko tam vai ieks adrStartEnd ievadita vertiba atrodas pa vidu jau esosajai vertibai
extern bool newData;//nepieciesams, lai veiktu izmainas pie jaunu datu sanemsanas
extern bool clearLedPartArrAllowed;

extern int blinkOff[];
extern int isFirstTime[]; //seko lidzi atbilstosajam vertibam funkciju masiva, vai tas izpildas pirmo reizi vai ari ne
extern int incColor[];
extern int decColor[30 + 1];

extern uint8_t rainbowCounter[30 + 1];

extern int adrStartEnd[30 + 1][2]; //masivs, kura glabajas esosas diozu dalas pa komplektiem
extern int funcNumArr[30 + 1];
extern int funcParArr[30 + 1]; //glaba sevi katras dalas funkcijas parametrus


extern int funcNum;
extern int funcPar;
extern int oldAdrStartEnd[30 + 1][2]; //iepriekseja adrStartEnd masiva vertiba, salidzinasanai
extern int startIn;//mainigais, kas atrod 2d masiva sev atbilstosas vietas atkariba no sakuma un beigu vertibam
extern int dataType;//sanemto datu veids
extern int adrStartEndUpdateNum;

extern char receivedChars[32];//uzglaba sevi ienakosos simbolus

extern uint32_t oldTimeInt[30 + 1]; //nepieciesams prieks salidzinajumiem ar millis()

extern byte adrRainbowCounter[30 + 1];//adresejamo diozu funkcijas rainbow skaititajs
extern byte highVal[30 + 1][4];
extern byte rgb[30 + 1][4]; //rgb kopejais krasu saraksts
extern byte rgbReceive[4]; //saglaba ienakosas krasu vertibas

extern int ledPartStartEnd[2];







bool checkSavedData(int startCheck, String stringToCheck);
void clearEEPROM(int startOfCount, int endOfCount);
void displayAdrColors(int startEnd[2], byte colorToDisplay[4 /*4*/]);
void fire(int part);
void funcExecute();
void handleAPSettings();
void handleRoot();
void lightMusic(int part);
void loop();
void rainbow(int part);
void rainbowWheel(byte WheelPos, int led);
void readEEPROM();
void recvWithStartEndMarkers(String inputString);
void responseCheck();
String returnEEPROMData(int startSearch, int endSearch);
void returnWlanMDns();
void sendPlainText(String dataToSend);
void serverFunctions();
bool set32DataInEEPROM(String dataToPut, int start, int end);
void setNewData();
void setRgbColors(byte arr[30 /*30*/][4 /*4*/], byte valueToPut[4 /*4*/]);
void setup();
void setValueInArr(uint32_t arr[30 /*30*/], uint32_t valueToPut);
void softAPLogin();
void solidBlink(byte rgbArr[4 /*4*/], int off, int part);
void solidFade(byte rgbArr[4 /*4*/], int period, unsigned long time, int part);
void solidRainbow(int part, int firstTime = 0);
void startEEPROM();
void startMDNS();
void startServer();
void startSPIFFS();
void startWifi();
void test(String testString);
void updateAdrLedPart(int startEnd[2]);
void wlanLogin();
void writeToEEPROM(String dataToWrite, int startPlace);
void printFile(const char *webdata);
void setJsonData(String action, String type, String input[5], int index);
int countChars(char findChar, String findString);

#endif