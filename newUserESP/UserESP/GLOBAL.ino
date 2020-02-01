// Load Wi-Fi librarySOFT
#include <WiFi.h>
#include <EEPROM.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>

#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
//#include <SimpleTimer.h>

#include "index.h"  //Web page header file
//#include "softAPSettings.h"  //softAP settings lapa

//SimpleTimer timer;

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

int INCREMENTER;
// Replace with your network credentials
//const char* DEFAULT_WLAN_SSID = "esp32";
//const char* DEFAULT_WLAN_PASS = "password";

const char* WLAN_SSID     = "ElektronikasKlubs";
const char* WLAN_PASSWORD = "ViitaisPaaris";

//const char* WLAN_SSID     = "MyHomeNetV2.0";
//const char* WLAN_PASSWORD = "Rammy12345";
// Set web server port number to 80
AsyncWebServer server(80);


#define EEPROM_SIZE 192//EEPROM rezervētā atmiņa
char USER_SSID[32];//saglabā lietotāja wifi nosaukumu eepromā
char USER_PASSWORD[32];//saglabā lietotāja paroli eepromā

char SOFT_AP_MDNS[32];//saglabā softAP nosaukumu

//iesūtot vairākas vērtības reizē (pieņemsim 60 krāsu iestatīšanas<01-1#000000255000><02-2#255000000000><03-3#000255000000>) , tas maina krāsu vērtības uz 96 vai 168, pēc kā nestrādā arī funkcijas

//BUG: pēcgaismas mūzikas vairs neiestatās krāsas

/*Iestatot masīvos vērtības ir nepieciešams, lai neesošas vērtības būtu nulle un kkādas vērtības būtu 1,
   tātad, kad tiek izmantotas vērtības no masīva,
   tas tās vērtība ir vērtība -1 izņemot nulli,
   piemēram funcPar vai oldTimeInt, lai būtu 0 nevis 1
*/

#define redIn 22
#define greenIn 23
#define blueIn 24

const int numLeds = 30; //diožu daudzums, jābūt +1, jo mēdz nokrašot esp
const byte colorCount = 4;//krāsu daudzums, rgb vai rgbw atbilstoši

const byte numChars = 32;

bool divide = false;//mainīgais, kas seko tam vai iekš adrStartEnd ievadītā vērtība atrodas pa vidu jau esošajai vērtībai
bool newData = false;//nepieciešams, lai veiktu izmaiņas pie jaunu datu saņemšanas
bool clearLedPartArrAllowed = false;

int blinkOff[numLeds + 1];
int isFirstTime[numLeds + 1]; //seko līdzi atbilstošajām vērtībām funkciju masīvā, vai tās izpildās pirmo reizi vai arī nē

int incColor[numLeds + 1];
int decColor[numLeds + 1];
uint8_t rainbowCounter[numLeds + 1];

int adrStartEnd[numLeds + 1][2]; //masīvs, kurā glabājas esošās diožu daļas pa komplektiem

int funcNumArr[numLeds + 1];

int funcParArr[numLeds + 1]; //glabā sevī katras daļas funkcijas parametrus


int funcNum;
int funcPar;
int oldAdrStartEnd[numLeds + 1][2]; //iepriekšējā adrStartEnd masīva vērtība, salīdzināšanai
int startIn;//mainīgais, kas atrod 2d masīvā sev atbilstošās vietas atkarībā no sākuma un beigu vērtībām
int dataType;//saņemto datu veids
int adrStartEndUpdateNum;

char receivedChars[numChars];//uzglabā sevī ienākošos simbolus

uint32_t oldTimeInt[numLeds + 1]; //nepieciešams priekš salīdzinājumiem ar millis()

byte adrRainbowCounter[numLeds + 1];//adresējamo diožu funkcijas rainbow skaitītājs
byte highVal[numLeds + 1][colorCount];
byte rgb[numLeds + 1][colorCount]; //rgb kopējais krāsu saraksts
byte rgbReceive[colorCount]; //saglabā ienākošās krāsu vērtības

int ledPartStartEnd[2];
