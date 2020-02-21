#include "funcHeader.h"

// struct Config
// {
//   char hostname[64];
//   int port;
//   int userIP;
//   int arrayData[3];
// };

const char *webdata = "/configFile.txt"; // <- SD library uses 8.3 webdatas
// Config config;                       // <- global configuration object

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

    printFile(webdata);
    SPIFFS.remove(webdata); //ieprieksejais faila saturs tiek dzests, lai varetu ieladet jaunus JSON datus

    Serial.print("TYPE: ");Serial.println(type);
    Serial.print("Action: ");Serial.println(action);

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
        Serial.println("inNestedArr");
        Serial.print("typeHere: ");Serial.println(type);
        while (i != 5 && input[i] != "") //JSON masiva tiek ieladetas jaunas padotas vertibas
        {
            newArray.add(input[i]);
            Serial.print("inWhile");Serial.println(input[i]);
            i++;
        }
        // doc[type].add(newArray); //Jaunizveidotais masivs tiek pievienots visiem parejiem json datiem
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
    Serial.println();
    printFile(webdata);
}
