#include "funcHeader.h"

bool set32DataInEEPROM(String dataToPut, int start, int end) {//saglaba ienakoso paroli wlan tiklam
  clearEEPROM(start, end);
  writeToEEPROM(dataToPut, start);//Ieraksta datus EEPROM
  readEEPROM();//parbaudei
  if (checkSavedData(start, dataToPut)) {//Parbauda vai ssid tika saglabats
    return true;
  } else {
    return false;
  }
}

bool checkSavedData(int startCheck, String stringToCheck) {//Parbauda vai eeprom saglabatie dati tikusi veiksmigi saglabati
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


void writeToEEPROM(String dataToWrite, int startPlace) {//Ieraksta vertibas ieks EEPROM
  char storeChars[32];
  dataToWrite.toCharArray(storeChars, 32);//Parveido ieguto vardu char masiva
  for (byte i = startPlace; i < startPlace + dataToWrite.length(); i++) { //Ievada vertibas ieks EEPROM
    EEPROM.write(i, storeChars[i - startPlace]);
  }
  EEPROM.commit();
}

void readEEPROM() {//Izvada EEPROM vertibas seriali
  for (byte i = 0; i < EEPROM_SIZE; i++) {
    char readChar = EEPROM.read(i);
    Serial.println(readChar);
  }
}

String returnEEPROMData(int startSearch, int endSearch) {//nolasa datus no eeprom un atgriez tos 
  String eepromData;
  char rc;
  for (int i = startSearch; i < endSearch; i++) {
    rc = EEPROM.read(i);
    eepromData += rc;
  }
  return eepromData;
}

void clearEEPROM(int startOfCount, int endOfCount) {//Notira EEPROMu
  for (byte i = startOfCount; i < endOfCount; i++) {
    EEPROM.write(i, '\0');
  }
  EEPROM.commit();
}









