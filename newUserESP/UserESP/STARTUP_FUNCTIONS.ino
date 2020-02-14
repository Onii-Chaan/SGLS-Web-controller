void startWifi() {
  // Connect to Wi-Fi network with SSID and password
  //  mySerial.print("Connecting to wifi...");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  //  WiFi.mode(WIFI_AP);
  WiFi.begin(WLAN_SSID, WLAN_PASSWORD);
  delay(100);

  //  IPAddress IP (192, 168, 4, 1);
  //  IPAddress NMask(255, 255, 255, 0);
  //  WiFi.softAPConfig(IP, IP, NMask);



  //  mySerial.print("AP IP address: ");
  //  mySerial.println(WiFi.softAPIP());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    mySerial.println("Connecting to WiFi..");
  }
  mySerial.println("Connected to the WiFi network");
  mySerial.println(WiFi.localIP());
}

void startEEPROM() {
  EEPROM.begin(EEPROM_SIZE);
  mySerial.println("EEPROM START: ");
  readEEPROM();
  mySerial.println(" EEPROM END");
}

void startMDNS() {
  /* http://esp32.local */
  MDNS.begin("esp32");
  if (!MDNS.begin("esp32")) {
    mySerial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  MDNS.addService("http", "tcp", 80);
}

void startServer() {
  server.begin();//Start server
  mySerial.println("HTTP server started");
}

void startSPIFFS() {
  if (!SPIFFS.begin(true)) {
    mySerial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}
