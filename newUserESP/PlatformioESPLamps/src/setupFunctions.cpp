#include "funcHeader.h"

void startWifi()
{
  File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
  DynamicJsonDocument doc(10000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
  if (error)
  {
    Serial.println(F("Failed to read file, using default configuration"));
    return;
  }
  file.close();

  // doc["WIFIMode"] = "WLAN";
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

  if (doc["WIFIMode"] == "WLAN" && !resetWifi(doc["UserWlanSsid"], doc["UserWlanPass"], doc["WIFIMode"]) || doc["WIFIMode"] == "softAP") //starts working in local WLAN if it's written in JSON file
    resetWifi(doc["SoftAPSSID"], doc["SoftAPPass"], doc["WIFIMode"]);
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

void startMDNS(String mdnsName)
{
  MDNS.end();

  if (mdnsName != "")
  {
    MDNS.end();//stops previous mdns server
    char mdnsChar[mdnsName.length() + 1]; //stores ssid to pass to wifi method
    mdnsName.toCharArray(mdnsChar, mdnsName.length() + 1);
    MDNS.begin(mdnsChar);
    MDNS.addService("http", "tcp", 53);
    MDNS.setInstanceName(mdnsName);
  }
  else
  {
    File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
    DynamicJsonDocument doc(14000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
    DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
    if (error)
    {
    }
    file.close();
    MDNS.begin(doc["UserMDNS"]);
    MDNS.addService("http", "tcp", 53);
    String instance = doc["UserMDNS"];
    MDNS.setInstanceName(instance);
  }
  Serial.print("MDNS IP: ");Serial.println(MDNS.IP(0));
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
