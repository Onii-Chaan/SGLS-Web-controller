#include "funcHeader.h"



void softAPLogin() {

}

void handleAPSettings() {
  //  String s = SOFT_AP_settings_page;
  //  server.send(200, "text/html", s);
}

void returnWlanMDns() {//nosuta wlan linku uz lapu
  sendPlainText("_wlan_link_ " + returnEEPROMData(64, 96) + " ");
}

void handleRoot() {//Parada lapu
  //  File file = SPIFFS.open("/index.html");
  //  String s = String(file.read()); //Read HTML contents
  //  request->send(SPIFFS, "/index.html", "text/html");
  //  file.close();
  //  Serial.println("Handle_root");

}

void responseCheck() {//atbild, ja lapa parbauda savienojamibu
  sendPlainText("server_ap_ok");
}
void sendPlainText(String dataToSend) {//nosuta teksta rindinu uz majaslapu
  //  server.send(200, "text/plane", dataToSend);
  Serial.println(dataToSend);
}

void wlanLogin() {//Saglaba ssid un pass datus un parbauda vai tie ir saglabati un atbilstosi nosuta vertibu
  //  String receivedData = server.arg(0);
  bool savedOrNot = false;
  String trimmedRecData;//Sadala ienakoso Stringu nepieciesamajos datos
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



void test(String testString) {
  Serial.println("TestData: "); Serial.println(testString);
}







