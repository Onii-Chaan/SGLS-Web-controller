void softAPLogin() {

}

void handleAPSettings() {
  //  String s = SOFT_AP_settings_page;
  //  server.send(200, "text/html", s);
}

void returnWlanMDns() {//nosūta wlan linku uz lapu
  sendPlainText("_wlan_link_ " + returnEEPROMData(64, 96) + " ");
}

void handleRoot() {//Parāda lapu
  //  File file = SPIFFS.open("/index.html");
  //  String s = String(file.read()); //Read HTML contents
  //  request->send(SPIFFS, "/index.html", "text/html");
  //  file.close();
  //  Serial.println("Handle_root");

}

void responseCheck() {//atbild, ja lapa pārbauda savienojamību
  sendPlainText("server_ap_ok");
}
void sendPlainText(String dataToSend) {//nosūta teksta rindiņu uz mājaslapu
  //  server.send(200, "text/plane", dataToSend);
  Serial.println(dataToSend);
}

void wlanLogin() {//Saglabā ssid un pass datus un pārbauda vai tie ir saglabāti un atbilstoši nosūta vērtību
  //  String receivedData = server.arg(0);
  bool savedOrNot = false;
  String trimmedRecData;//Sadala ienākošo Stringu nepieciešamajos datos
  //  trimmedRecData = receivedData.substring(receivedData.indexOf("ssid=") + 5, receivedData.indexOf(" "));
  //  savedOrNot = set32DataInEEPROM(trimmedRecData, 0, 32);
  //  trimmedRecData = receivedData.substring(receivedData.indexOf("pass=") + 5, receivedData.indexOf(" ", receivedData.indexOf("pass=") + 5));
  //  savedOrNot = set32DataInEEPROM(trimmedRecData, 32, 64);

  if (savedOrNot) {
    sendPlainText("wlan_login_data_ok");
  } else {
    sendPlainText("wlan_login_data_failed");
  }
}


bool set32DataInEEPROM(String dataToPut, int start, int end) {//saglabā ienākošo paroli wlan tīklam
  clearEEPROM(start, end);
  writeToEEPROM(dataToPut, start);//Ieraksta datus EEPROM
  readEEPROM();//pārbaudei
  if (checkSavedData(start, dataToPut)) {//Pārbauda vai ssid tika saglabāts
    return true;
  } else {
    return false;
  }
}

bool checkSavedData(int startCheck, String stringToCheck) {//Pārbauda vai eeprom saglabātie dati tikuši veiksmīgi saglabāti
  char cE;
  char checkString[32];
  stringToCheck.toCharArray(checkString, 32);
  for (int i = startCheck; i < stringToCheck.length(); i++) {
    cE = EEPROM.read(i);
    if (cE != checkString[i])
      return false;
  }
  return true;
}
