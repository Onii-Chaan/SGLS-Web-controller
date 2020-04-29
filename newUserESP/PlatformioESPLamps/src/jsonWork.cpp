#include "funcHeader.h"

// struct Config
// {
//   char hostname[64];
//   int port;
//   int userIP;
//   int arrayData[3];
// };
const char *defaultTxt = "/default.txt";
const char *saveTxt = "/save.txt";
const char *webdata = "/configFile.txt"; // <- SD library uses 8.3 webdatas
// Config config;                       // <- global configuration object

void printFile(const char *webdata) //print content of file
{
  // Open file for reading
  File file = SPIFFS.open(webdata);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }
  // Extract each characters by one by one
  while (file.available())
  {
    Serial.print((char)file.read());
  }
  // Serial.println();
  // Close the file
  file.close();
  Serial.println();
}

void setJsonData(String action, String type, String input[5], int index = -1) //Manipule ar saglabatajiem JSON datiem ieks FS
{
  File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
  DynamicJsonDocument doc(14000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
  if (error)
  {
    // Serial.println(F("Failed to read file, using default configuration"));
    // return;
  }
  file.close();

  // printFile(webdata);
  SPIFFS.remove(webdata); //ieprieksejais faila saturs tiek dzests, lai varetu ieladet jaunus JSON datus

  if (action == "edit") //JSON dati tiek modificeti
  {
    if (type == "LampGroups" || type == "FuncArr" || type == "RgbwArr")
    {
      int i = 0;
      while (i != 5 && input[i] != "")
      {
        doc[type][index][i] = input[i];
        i++;
      }
    }
    else if (type == "wlan") //if changing saved wlan data
    {
      doc["UserWlanSsid"] = input[0];
      saveJsonPassword("UserWlanPass", input[1]);
      doc["WIFIMode"] = "WLAN";
      // startMDNS(doc["UserMDNS"]);
      if (!resetWifi(input[0], input[1], doc["WIFIMode"])) //resets and starts wifi in wlan mode
        resetWifi(doc["SoftAPSSID"], getJsonPass("SoftAPPass"), doc["WIFIMode"]);
    }
    else if (type == "softap") //if changing saved softAP data
    {
      doc["SoftAPSSID"] = input[0];
      saveJsonPassword("SoftAPPass", input[1]);
      doc["WIFIMode"] = "softAP";
      // startMDNS(doc["UserMDNS"]);
      resetWifi(input[0], input[1], doc["WIFIMode"]); //resets and starts wifi in softAP mode
    }
    else if (type == "newLampCount") //if setting new lamp quant
    {
      doc["LampNum"] = input[0].toInt();
    }
    else if (type == "newMdns") //if setting new mdns link
    {
      doc["UserMDNS"] = input[0];
      startMDNS(input[0]);
    }
    else if (type == "changeWifi") //if user changes wifi mode
    {
      if (input[0] == "WLAN")
        doc["WIFIMode"] = input[0];
      else if (input[0] == "softAp")
        doc["WIFIMode"] = "softAP";

      if (input[0] == "WLAN" && !resetWifi(doc["UserWlanSsid"], getJsonPass("UserWlanPass"), doc["WIFIMode"]) || input[0] == "softAp")
        resetWifi(doc["SoftAPSSID"], getJsonPass("SoftAPPass"), doc["WIFIMode"]);
    }
    else if (type == "factoryReset") //removes all user saved data (colors, animations, groups)
    {
      doc["OffState"] = false;
      String types[] = {"RgbwArr", "FuncArr", "LampGroups"};
      for (int i = 0; i < 3; i++)
      {
        int arrLen = doc[types[i]].size(); //because arrayList size (when removing) is constantly changing
        for (int j = 0; j < arrLen; j++)
          doc[types[i]].remove(0); //zero because it's array list
      }
    }
    else if (type == "hardReset") //resets core core data using external irritation
    {
      doc["LampNum"] = 0;
      doc["OffState"] = true;
      doc["UserWlanSsid"] = "";
      saveJsonPassword("UserWlanPass", "");
      doc["UserWlanPass"] = "null";
      doc["UserMDNS"] = "raylight";
      doc["WIFIMode"] = "softAP";
      doc["SoftAPSSID"] = "raylight";
      saveJsonPassword("SoftAPPass", "");
      saveJsonPassword("userPass", "");
      saveJsonPassword("sessions", "null");
      resetWifi(doc["SoftAPSSID"], getJsonPass("SoftAPPass"), doc["WIFIMode"]);
    }
    else if (type == "turnOn") //saves turn on or turn off state
    {
      if (input[0] == "true")
        doc["OffState"] = true;
      else
        doc["OffState"] = false;
    }
  }
  else if (action == "delete") //Json dati tiek dzesti
  {
    doc[type].remove(index);
  }
  //Json datiem tiek pievienoti jauni dati
  else if (action == "add")
  {
    JsonArray newArray = doc[type].createNestedArray(); //Tiek izveidots jauns JSON masivs
    int i = 0;
    while (i != 5 && input[i] != "") //JSON masiva tiek ieladetas jaunas padotas vertibas
    {
      Serial.print("Test ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(input[i]);

      newArray.add(input[i]);
      i++;
    }
  }

  file = SPIFFS.open(webdata, FILE_WRITE); //tiek atverts fails rakstisanai
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
  // Serial.println();
  // printFile(webdata);
  // printFile("/configFile.txt");

  // printFile("/configFile.txt");
}

bool jsonTurnOn() //returns true or false depending on last turned on or off state
{
  File file = SPIFFS.open(webdata);                        //Tiek atverts fails datu apstradei
  DynamicJsonDocument doc(14000);                          /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasiti un deserializeti sagatavojot tos JSON apstradei
  if (error)
  {
    // Serial.println(F("Failed to read file, using default configuration"));
    // return;
  }
  file.close();
  return doc["OffState"];
}

void save1DData(byte type, uint32_t *array, bool writeToArr, const char *fileName, DynamicJsonDocument &jsonRef) //writes 1d array to file
{
  String arrName[8] = {"funcNumArr", "isFirstTime", "oldTimeInt", "funcParArr", "blinkOff", "decColor", "incColor", "rainbowCounter"}; //JSON 1d array names

  if (!writeToArr)
  {
    for (byte i = 0; i < 30; i++) //copies from array
      jsonRef[arrName[type]][i] = array[i];
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies to array
      array[i] = jsonRef[arrName[type]][i];
  }
}

void save2D4Data(byte type, byte (*array)[31][4], bool writeToArr, const char *fileName, DynamicJsonDocument &jsonRef)
{
  String arrName[2] = {"rgb", "highVal"}; //JSON 2d4 array names

  if (!writeToArr)
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 4; j++)
        jsonRef[arrName[type]][i][j] = (*array)[i][j];
    }
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 4; j++)
        (*array)[i][j] = jsonRef[arrName[type]][i][j];
    }
  }
}

void save2D2Data(byte type, int (*array)[31][2], bool writeToArr, const char *fileName, DynamicJsonDocument &jsonRef)
{
  String arrName[2] = {"adrStartEnd", "oldAdrStartEnd"}; //JSON 2d4 array names

  if (!writeToArr)
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 2; j++)
        jsonRef[arrName[type]][i][j] = (*array)[i][j];
    }
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 2; j++)
        (*array)[i][j] = jsonRef[arrName[type]][i][j];
    }
  }
}

void setDefaultSave()
{
  SPIFFS.remove(saveTxt);
  File saveFile = SPIFFS.open(saveTxt, FILE_WRITE);
  File defaultFile = SPIFFS.open(defaultTxt, FILE_READ);
  saveFile.print(defaultFile.readString());
  saveFile.close();
  defaultFile.close();
}

void setJsonArrData(bool actionType, const char *fileName)
{
  File file = SPIFFS.open(fileName);
  DynamicJsonDocument doc(14000);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();

  if (!actionType)
  {
    SPIFFS.remove(fileName);
  }

  //TO SPEED UP, YOU HAVE TO BREAK OUT OF FUNCTION FOR LOOPS WHEN ZERO IS MET

  save1DData(0, (uint32_t *)funcNumArr, actionType, fileName, doc);
  save1DData(1, (uint32_t *)isFirstTime, actionType, fileName, doc);
  save1DData(2, (uint32_t *)oldTimeInt, actionType, fileName, doc);
  save1DData(3, (uint32_t *)funcParArr, actionType, fileName, doc);
  save1DData(4, (uint32_t *)blinkOff, actionType, fileName, doc);
  save1DData(5, (uint32_t *)decColor, actionType, fileName, doc);
  save1DData(6, (uint32_t *)incColor, actionType, fileName, doc);
  save1DData(7, (uint32_t *)rainbowCounter, actionType, fileName, doc);

  int(*p_2d2)[31][2] = &adrStartEnd;
  save2D2Data(0, p_2d2, actionType, fileName, doc);
  p_2d2 = &oldAdrStartEnd;
  save2D2Data(1, p_2d2, actionType, fileName, doc);

  byte(*p_2d4)[31][4] = &rgb;
  save2D4Data(0, p_2d4, actionType, fileName, doc);
  p_2d4 = &highVal;
  save2D4Data(1, p_2d4, actionType, fileName, doc);

  file = SPIFFS.open(fileName, FILE_WRITE); //tiek atverts fails rakstisanai
  if (!file)
    Serial.println(F("Failed to create file"));
  if (serializeJson(doc, file) == 0) //Jaunie json dati tiek ierakstiti jaunaja faila
    Serial.println(F("Failed to write to file"));
  file.close();
  // Serial.print("Time: ");Serial.println(millis());
  // printFile(fileName);
}

void saveJsonPassword(String type, String data) //saves password in txt file
{
  const char *fileName = "/secure.txt";
  File file = SPIFFS.open(fileName);
  DynamicJsonDocument doc(500);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();
  SPIFFS.remove(fileName);

  if (type == "sessions" && doc[type].size() == 12) //so no more than 12 passwords and session ids can be added
    doc[type].remove(0);

  if (type == "sessions" && data != "null") //saves session ID
  {
    unsigned long sessionId = data.toInt();
    doc[type].add(sessionId);
  }
  else if (type == "sessions" && data == "null") //deletes all session IDs
  {
    for (int i = 0; i < doc.size(); i++)
      doc[type].remove(0);
  }
  else //saves passwords
  {
    doc[type] = data;
  }

  file = SPIFFS.open(fileName, FILE_WRITE); //tiek atverts fails rakstisanai
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
  printFile(fileName);
}

String getJsonPass(String jsonKey) // getter function to get passwords from password document
{
  const char *fileName = "/secure.txt";
  File file = SPIFFS.open(fileName);
  DynamicJsonDocument doc(500);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();
  return doc[jsonKey];
}

bool checkJsonSessId(String findSessId) //searches through saved session ids to find if parsed sessid exists
{
  const char *fileName = "/secure.txt";
  File file = SPIFFS.open(fileName);
  DynamicJsonDocument doc(500);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();

  unsigned long sessId = findSessId.toInt(); //parses sessid string to sessid unsigned long
  for (int i = 0; i < doc["sessions"].size(); i++)
    if (doc["sessions"][i] == sessId)
      return true;

  return false;
}

