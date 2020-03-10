#include <Arduino.h>
#include <ArduinoJson.h>
// #include <SD.h>
#include <SPIFFS.h>

// Our configuration structure.
//
// Never use a JsonDocument to store the configuration!
// A JsonDocument is *not* a permanent storage; it's only a temporary storage
// used during the serialization phase. See:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/
struct Config
{
  char hostname[64];
  int port;
  int userIP;
  int arrayData[3];
};
const char *webdata = "/save.txt"; // <- SD library uses 8.3 webdatas

const char *defaultTxt = "/default.txt";
const char *saveTxt = "/save.txt";
int funcNumArr[30 + 1];
byte rgb[30 + 1][4];        //rgb kopejais krasu saraksts
int adrStartEnd[30 + 1][2]; //masivs, kura glabajas esosas diozu dalas pa komplektiem

void setDefaultSave()
{
  SPIFFS.remove(saveTxt);
  File saveFile = SPIFFS.open(saveTxt, FILE_WRITE);
  File defaultFile = SPIFFS.open(defaultTxt, FILE_READ);
  saveFile.print(defaultFile.readString());
  saveFile.close();
  defaultFile.close();
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

Config config; // <- global configuration object

// Loads the configuration from a file
void loadConfiguration(const char *webdata, Config &config)
{
  // Open file for reading
  File file = SPIFFS.open(webdata);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  config.port = doc["port"] | 2731;
  config.userIP = doc["userIP"] | 1000;
  strlcpy(config.hostname,                 // <- destination
          doc["hostname"] | "example.com", // <- source
          sizeof(config.hostname));        // <- destination's capacity

  // JsonArray& array = doc.createNestedArray("arrayData");
  // array.arrayData[0] = doc[];

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *webdata, const Config &config)
{
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(webdata);

  // Open file for writing
  File file = SPIFFS.open(webdata, FILE_WRITE);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["hostname"] = config.hostname;
  doc["userIP"] = config.userIP;
  doc["port"] = config.port;

  // doc.remove("userIP");

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

void printFile(const char *webdata)
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

void setJsonData(char *action, char *type, String input[5], int index = -1) //Manipulē ar saglabātajiem JSON datiem iekš FS
{
  File file = SPIFFS.open(webdata);                        //Tiek atvērts fails datu apstrādei
  StaticJsonDocument<3000> doc;                            /*!!!NEPIECIEŠAMS PALIELINĀT HEAP VAI STACK LIELUMU!!!!*/
  DeserializationError error = deserializeJson(doc, file); //dati no faila tiek nolasīti un deserializēti sagatavojot tos JSON apstrādei
  if (error)
  {
    // Serial.println(F("Failed to read file, using default configuration"));
    // return;
  }
  file.close();

  printFile(webdata);
  SPIFFS.remove(webdata); //iepriekšējais faila saturs tiek dzēsts, lai varētu ielādēt jaunus JSON datus

  Serial.println("TYPE: ");

  Serial.println(type);

  if (strcmp(action, "edit") == 0) //JSON dati tiek modificēti
  {
    int i = 0;
    while (i != 5 && input[i] != "")
    {
      doc[type][index][i] = input[i];
      i++;
    }
  }
  else if (strcmp(action, "delete") == 0) //Json dati tiek dzēsti
  {
    doc[type].remove(index);
  }
  else if (strcmp(action, "add") == 0) //Json datiem tiek pievienoti jauni dati
  {
    JsonArray newArray = doc[type].createNestedArray(); //Tiek izveidots jauns JSON masīvs
    int i = 0;
    while (i != 5 && input[i] != "") //JSON masīvā tiek ielādētas jaunās padotās vērtības
    {
      newArray.add(input[i]);
      i++;
    }
    doc[type].add(newArray); //Jaunizveidotais masīvs tiek pievienots visiem pārējiem json datiem
  }

  file = SPIFFS.open(webdata, FILE_WRITE); //tiek atvērts fails rakstīšanai
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }
  if (serializeJson(doc, file) == 0) //Jaunie json dati tiek ierakstīti jaunajā failā
  {
    Serial.println(F("Failed to write to file"));
  }
  file.close();
  Serial.println();
  printFile(webdata);
}

// Prints the content of a file to the Serial

void setup()
{
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial)
    continue;

  // Initialize SD library
  while (!SPIFFS.begin())
  {
    Serial.println(F("Failed to initialize SD library"));
    delay(1000);
  }

  // Should load default config if run for the first time
  // Serial.println(F("Loading configuration..."));
  // loadConfiguration(webdata, config);

  // Create configuration file
  // Serial.println(F("Saving configuration..."));
  // saveConfiguration(webdata, config);

  // Dump config file
  Serial.println(F("Print config file..."));
  // printFile(webdata);

  // String jsonSet[5] = {"a", "b", "c", "d", "e"};
  // char jsonAction[] = "delete";
  // char jsonType[] = "ExploreArr";

  // setJsonData(jsonAction, jsonType, jsonSet, 1);

  funcNumArr[0] = 23;
  funcNumArr[2] = 65;
  funcNumArr[23] = 103;
  funcNumArr[5] = 102;

  rgb[0][0] = 255;
  rgb[0][1] = 255;
  rgb[0][2] = 255;
  rgb[0][3] = 255;

  rgb[14][0] = 23;
  rgb[14][1] = 0;
  rgb[14][2] = 87;
  rgb[14][3] = 129;

  adrStartEnd[0][0] = 2;
  adrStartEnd[0][1] = 2;

  adrStartEnd[4][0] = 5;
  adrStartEnd[4][1] = 6;
  // printFile(webdata);

  // setDefaultSave();
  save1DData(0, (uint32_t *)funcNumArr, false);
  int(*p_2d2)[31][2] = &adrStartEnd;
  save2D2Data(0, p_2d2, false);
  int(*p_2d2)[31][2] = &adrStartEnd;
  save2D2Data(0, p_2d2, false);
  byte(*p_2d4)[31][4] = &rgb;
  save2D4Data(0, p_2d4, false);
  printFile(webdata);

  Serial.println(rgb[0][1]);
  Serial.println(adrStartEnd[0][1]);
  Serial.println(adrStartEnd[4][1]);
}

void loop()
{
  // not used in this example
}
