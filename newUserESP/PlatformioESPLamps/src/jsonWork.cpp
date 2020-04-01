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
  Serial.println();
  // Close the file
  file.close();
}

void setJsonData(String action, String type, String input[5], int index = -1) //Manipule ar saglabatajiem JSON datiem ieks FS
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
    else if (type == "wlan")
    { //if changing saved wlan data
      doc["UserWlanSsid"] = input[0];
      doc["UserWlanPass"] = input[1];
      doc["WIFIMode"] = "WLAN";
      // startMDNS(doc["UserMDNS"]);
      resetWifi(input[0], input[1], doc["WIFIMode"]);
    }
    else if (type == "softap")
    { //if changing saved softAP data
      doc["SoftAPSSID"] = input[0];
      doc["SoftAPPass"] = input[1];
      doc["WIFIMode"] = "softAP";
      // startMDNS(doc["UserMDNS"]);
      resetWifi(input[0], input[1], doc["WIFIMode"]);
    }
    else if (type == "newLampCount")
    { //if setting new lamp quant
      doc["LampNum"] = input[0].toInt();
    }
    else if (type == "newMdns")
    { //if setting new mdns link
      doc["UserMDNS"] = input[0];
    }
    else if (type == "changeWifi")
    { //if user changes wifi mode
      doc["WIFIMode"] = input[0];
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
  {
    Serial.println(F("Failed to create file"));
    return;
  }
  if (serializeJson(doc, file) == 0) //Jaunie json dati tiek ierakstiti jaunaja faila
  {
    Serial.println(F("Failed to write to file"));
  }
  file.close();
  // Serial.print("Time: ");Serial.println(millis());
  // printFile(fileName);
}