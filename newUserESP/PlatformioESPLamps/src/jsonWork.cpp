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

void printFile(const char *webdata)//print content of file
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
    DynamicJsonDocument doc(10000);                            /*!!!NEPIECIEsAMS PALIELINaT HEAP VAI STACK LIELUMU!!!!*/
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
        int i = 0;
        while (i != 5 && input[i] != "")
        {
            doc[type][index][i] = input[i];
            i++;
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
}


void save1DData(byte type, uint32_t *array, bool writeToArr) //writes 1d array to file
{
  String arrName[8] = {"funcNumArr", "isFirstTime", "oldTimeInt", "funcParArr", "blinkOff", "decColor", "incColor", "rainbowCounter"}; //JSON 1d array names
  File file = SPIFFS.open(saveTxt);
  DynamicJsonDocument doc(14000);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();
  if (!writeToArr)
  {
    SPIFFS.remove(saveTxt);
    for (byte i = 0; i < 30; i++) //copies from array
      doc[arrName[type]][i] = array[i];
    file = SPIFFS.open(saveTxt, FILE_WRITE); //tiek atverts fails rakstisanai
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
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies to array
      array[i] = doc[arrName[type]][i];
  }
}

void save2D4Data(byte type, byte (*array)[31][4], bool writeToArr)
{
  String arrName[8] = {"rgb", "highVal"}; //JSON 2d4 array names
  File file = SPIFFS.open(saveTxt);
  DynamicJsonDocument doc(14000);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();
  if (!writeToArr)
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 4; j++)
        doc[arrName[type]][i][j] = (*array)[i][j];
    }
    SPIFFS.remove(saveTxt);
    file = SPIFFS.open(saveTxt, FILE_WRITE); //tiek atverts fails rakstisanai
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
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 4; j++)
        (*array)[i][j] = doc[arrName[type]][i][j];
    }
  }
}

void save2D2Data(byte type, int (*array)[31][2], bool writeToArr)
{
  String arrName[8] = {"adrStartEnd", "oldAdrStartEnd"}; //JSON 2d4 array names
  File file = SPIFFS.open(saveTxt);
  DynamicJsonDocument doc(14000);
  DeserializationError error = deserializeJson(doc, file); //copies file contents to doc
  if (error)
  {
  }
  file.close();

  if (!writeToArr)
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 2; j++)
        doc[arrName[type]][i][j] = (*array)[i][j];
    }
    SPIFFS.remove(saveTxt);
    file = SPIFFS.open(saveTxt, FILE_WRITE); //tiek atverts fails rakstisanai
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
  }
  else
  {
    for (byte i = 0; i < 30; i++) //copies array values
    {
      for (byte j = 0; j < 2; j++)
        (*array)[i][j] = doc[arrName[type]][i][j];
    }
  }
  file.close();
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

void setJsonArrData(bool actionType){
      save1DData(0, (uint32_t *)funcNumArr, actionType);
      save1DData(1, (uint32_t *)isFirstTime, actionType);
      save1DData(2, (uint32_t *)oldTimeInt, actionType);
      save1DData(3, (uint32_t *)funcParArr, actionType);
      save1DData(4, (uint32_t *)blinkOff, actionType);
      save1DData(5, (uint32_t *)decColor, actionType);
      save1DData(6, (uint32_t *)incColor, actionType);
      save1DData(7, (uint32_t *)rainbowCounter, actionType);
      
      int(*p_2d2)[31][2] = &adrStartEnd;
      save2D2Data(0, p_2d2, actionType);
      p_2d2 = &oldAdrStartEnd;
      save2D2Data(1, p_2d2, actionType);

      byte(*p_2d4)[31][4] = &rgb;
      save2D4Data(0, p_2d4, actionType);
      p_2d4 = &highVal;
      save2D4Data(0, p_2d4, actionType);
}