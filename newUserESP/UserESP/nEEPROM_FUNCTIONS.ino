void writeToEEPROM(String dataToWrite, int startPlace) {//Ieraksta vērtības iekš EEPROM
  char storeChars[32];
  dataToWrite.toCharArray(storeChars, 32);//Pārveido iegūto vārdu char masīvā
  for (byte i = startPlace; i < startPlace + dataToWrite.length(); i++) { //Ievada vērtības iekš EEPROM
    EEPROM.write(i, storeChars[i - startPlace]);
  }
  EEPROM.commit();
}

void readEEPROM() {//Izvada EEPROM vērtības seriālī
  for (byte i = 0; i < EEPROM_SIZE; i++) {
    char readChar = EEPROM.read(i);
    mySerial.print(readChar);
  }
}

String returnEEPROMData(int startSearch, int endSearch) {//nolasa datus no eeprom un atgriež tos 
  String eepromData;
  char rc;
  for (int i = startSearch; i < endSearch; i++) {
    rc = EEPROM.read(i);
    eepromData += rc;
  }
  return eepromData;
}

void clearEEPROM(int startOfCount, int endOfCount) {//Notīra EEPROMu
  for (byte i = startOfCount; i < endOfCount; i++) {
    EEPROM.write(i, '\0');
  }
  EEPROM.commit();
}
