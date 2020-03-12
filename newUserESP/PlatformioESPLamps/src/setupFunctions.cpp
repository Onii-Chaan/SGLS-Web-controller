#include "funcHeader.h"

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
void startWifi()
{
  // WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

  
  WiFi.softAP("RayLight", "12345678") ? Serial.println("Ready") : Serial.println("Failed");


  IPAddress NMask(255, 255, 255, 0);
  IPAddress IP(192, 168, 4, 1);
  WiFi.softAPConfig(IP, IP, NMask);

  delay(500);


  Serial.println("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //     delay(500);
  //     Serial.println(F("Connecting to WiFi.."));
  // }
  // Serial.println(F("Connected to the WiFi network"));
  // Serial.println(WiFi.localIP());
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
  MDNS.begin("esp32");
  // if (!MDNS.begin("esp32")) {
  // Serial.println(F("Error setting up MDNS responder!"));
  // while (1) {
  // delay(1000);
  // }
  // }
  MDNS.addService("http", "tcp", 53);
  MDNS.setInstanceName("esp32");
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
