#include "funcHeader.h"

// IPAddress local_ip(192, 168, 1, 1);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

void startWifi()
{
  File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
  DynamicJsonDocument doc(10000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
  if (error)
  {
    // Serial.println(F("Failed to read file, using default configuration"));
    // return;
  }
  file.close();

  doc["WIFIMode"] = "WLAN";
  // doc["WIFIMode"] = "softAP";

  file = SPIFFS.open(webdata, FILE_WRITE); //Tiek atverts fails datu apstradei
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }
  if (serializeJson(doc, file) == 0) //Jaunie json dati tiek ierakstiti jaunaja faila
  {
    Serial.println(F("Failed to write to file"));
  }
  file.close();

  if (doc["WIFIMode"] == "WLAN" || doc["WIFIMode"] == "softAP") //starts working in local WLAN if it's written in JSON file
    resetWifi(doc["UserWlanSsid"], doc["UserWlanPass"], doc["WIFIMode"]);
  else
    Serial.println("Error: Could not start WiFi");
}

void startEEPROM()
{
  EEPROM.begin(EEPROM_SIZE);
  Serial.println("EEPROM START: ");
  readEEPROM();
  Serial.println("EEPROM END");
}

void startMDNS()
{

  /* http://esp32.local */
  File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
  DynamicJsonDocument doc(10000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
  if (error)
  {
  }
  file.close();
  MDNS.begin(doc["UserMDNS"]);
  // if (!MDNS.begin("esp32")) {
  // Serial.println(F("Error setting up MDNS responder!"));
  // while (1) {
  // delay(1000);
  // }
  // }
  MDNS.addService("http", "tcp", 53);
  String instance = doc["UserMDNS"];
  MDNS.setInstanceName(instance);
  Serial.println(MDNS.IP(0));
}

void startServer()
{
  server.begin(); //Start server
  Serial.println(F("HTTP server started"));
}

void startSPIFFS()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println(F("An Error has occurred while mounting SPIFFS"));
    return;
  }
}
