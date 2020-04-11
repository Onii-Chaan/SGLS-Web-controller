#include "funcHeader.h"
// AsyncWebServer server(80);
// AsyncWebServer server();
int INCREMENTER;
// Replace with your network credentials
//const char* DEFAULT_WLAN_SSID = "esp32";
//const char* DEFAULT_WLAN_PASS = "password";

// const char* WLAN_SSID     = "ElektronikasKlubs";
// const char* WLAN_PASSWORD = "ViitaisPaaris";

const char* WLAN_SSID;
const char* WLAN_PASSWORD;

const char* SOFTAP_SSID;
const char* SOFTAP_PASS;
// Set web server port number to 80

AsyncWebServer server(80);
// DNSServer dnsServer;
// #define EEPROM_SIZE 192//EEPROM rezerveta atmina
// char USER_SSID[32];//saglaba lietotaja wifi nosaukumu eeproma
// char USER_PASSWORD[32];//saglaba lietotaja paroli eeproma

// char SOFT_AP_MDNS[32];//saglaba softAP nosaukumu

//iesutot vairakas vertibas reize (pienemsim 60 krasu iestatisanas<01-1#000000255000><02-2#255000000000><03-3#000255000000>) , tas maina krasu vertibas uz 96 vai 168, pec ka nestrada ari funkcijas

//BUG: pecgaismas muzikas vairs neiestatas krasas

/*Iestatot masivos vertibas ir nepieciesams, lai neesosas vertibas butu nulle un kkadas vertibas butu 1,
   tatad, kad tiek izmantotas vertibas no masiva,
   tas tas vertiba ir vertiba -1 iznemot nulli,
   piemeram funcPar vai oldTimeInt, lai butu 0 nevis 1
*/

#define redIn 22
#define greenIn 23
#define blueIn 24

const int numLeds = 30; //diozu daudzums, jabut +1, jo medz nokrasot esp
const byte colorCount = 4;//krasu daudzums, rgb vai rgbw atbilstosi
const byte numChars = 32;

bool divide = false;//mainigais, kas seko tam vai ieks adrStartEnd ievadita vertiba atrodas pa vidu jau esosajai vertibai
bool newData = false;//nepieciesams, lai veiktu izmainas pie jaunu datu sanemsanas
bool clearLedPartArrAllowed = false;

int blinkOff[numLeds + 1];
int isFirstTime[numLeds + 1]; //seko lidzi atbilstosajam vertibam funkciju masiva, vai tas izpildas pirmo reizi vai ari ne

int incColor[numLeds + 1];
int decColor[numLeds + 1];
uint8_t rainbowCounter[numLeds + 1];

int adrStartEnd[numLeds + 1][2]; //masivs, kura glabajas esosas diozu dalas pa komplektiem

int funcNumArr[numLeds + 1];

int funcParArr[numLeds + 1]; //glaba sevi katras dalas funkcijas parametrus


int funcNum;
int funcPar;
int oldAdrStartEnd[numLeds + 1][2]; //iepriekseja adrStartEnd masiva vertiba, salidzinasanai
int startIn;//mainigais, kas atrod 2d masiva sev atbilstosas vietas atkariba no sakuma un beigu vertibam
int dataType;//sanemto datu veids
int adrStartEndUpdateNum;

char receivedChars[numChars];//uzglaba sevi ienakosos simbolus

uint32_t oldTimeInt[numLeds + 1]; //nepieciesams prieks salidzinajumiem ar millis()

byte adrRainbowCounter[numLeds + 1];//adresejamo diozu funkcijas rainbow skaititajs
byte highVal[numLeds + 1][colorCount];
byte rgb[numLeds + 1][colorCount]; //rgb kopejais krasu saraksts
byte rgbReceive[colorCount]; //saglaba ienakosas krasu vertibas

int ledPartStartEnd[2];

bool turnOn;
