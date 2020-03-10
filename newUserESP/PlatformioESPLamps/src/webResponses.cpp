#include "funcHeader.h"

void serverFunctions()
{ //Tiek ievietots setup funkcija, izpilda visas nepieciesamas funkcijas sanemot vai nosutot datus
  //  server.on("/", handleRoot);      //Lapas paradisanai
  server.on("https://esp32.local/", HTTP_GET, [](AsyncWebServerRequest *request) { //vai mdns vajag laiku lai ieladetos?
    Serial.println("GOT IT");
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  server.on("/iro-transparency-plugin.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/iro-transparency-plugin.min.js", "text/js");
  });

  server.on("/iro.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/iro.min.js", "text/js");
  });

  server.on("/loadingScreen.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/loadingScreen.js", "text/js");
  });
  server.on("/global.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/global.js", "text/js");
  });

  server.on("/Constructor.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/Constructor.js", "text/js");
  });

  server.on("/CollapsibleButton.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/CollapsibleButton.js", "text/js");
    Serial.println("aaaaaa");
  });

  server.on("/Icon.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/Icon.js", "text/js");
  });
  server.on("/SGLSscripts.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/SGLSscripts.js", "text/js");
  });

  server.on("/data.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/data.js", "text/js");
  });
  server.on("/ColorBlock.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/ColorBlock.js", "text/js");
  });
  server.on("/AnimationsBlock.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/AnimationsBlock.js", "text/js");
  });

  server.on("/LampBlock.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/LampBlock.js", "text/js");
  });

  server.on("/SettingsPopUp.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/SettingsPopUp.js", "text/js");
  });

  server.on("/iroSet.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/iroSet.js", "text/js");
  });

  server.on("/InputForm.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/InputForm.js", "text/js");
  });

  server.on("/configFile.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/configFile.js", "text/js");
  });

  /*SETTINGS LAPA*/
  server.on("/settings.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("SETTINGS SEND");
    request->send(SPIFFS, "/settings.html", "text/html");
  });

  server.on("/setConstructor.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/setConstructor.js", "text/html");
  });

  server.on("/configFile.txt", HTTP_ANY, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/configFile.txt", "text/txt");
  });

  server.on("/setlamp", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Serial.println("INCOMIIIIIIIIING");
    String keyVal;
    String recData;

    if (request->hasParam("lamp", true))
    {
      keyVal = request->getParam("lamp", true)->value();
      recvWithStartEndMarkers(keyVal);
      //     //Apstrada datus un sak datu iesutisanu uz lampam
    }
    else
    {
      //handle an incomplete request
      keyVal = "some default value";
    }
    request->send(200, "text/plain", "Post route");
  });

  server.on("/setJson", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Serial.println(F("setJsonData"));
    String action;      //the action that has to be done (add, delete, edit)
    String type;        //gets the query string
    String dataType;    //gets the data type that has to be updated
    String index;       //gets the index of data type array to be updated
    String valueArr[5]; //stores variables

    String turnOnBool;
    bool doTurnOn;

    // int args = request->args();
    // for (int i = 0; i < args; i++)
    // {
    //   Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
    // }

    if (request->hasParam("type", true)) //Gets query parameters
    {
      type = request->getParam("type", true)->value();
    }
    // Serial.print("REC_STRING: ");
    // Serial.println(type);

    int lastParamId = 0;     //For getting next parameter after we got previous param
    String currentData;      //Stores name or parameter
    String currentDataValue; //Store parameter value
    do                       //asssigns new values to variables
    {
      currentData = type.substring(lastParamId, type.indexOf('=', lastParamId));                             //current parameter name
      currentDataValue = type.substring(type.indexOf('=', lastParamId) + 1, type.indexOf('|', lastParamId)); //current parameter value
      lastParamId = type.indexOf('|', lastParamId + 1) + 1;

      if (currentData == "action")
      {
        action = currentDataValue;
      }
      else if (currentData == "dataType")
      {
        dataType = currentDataValue;
      }
      else if (currentData == "name")
      {
        valueArr[0] = currentDataValue;
      }
      else if (currentData == "value")
      {
        valueArr[1] = currentDataValue;
      }
      else if (currentData == "r")
      {
        valueArr[1] = currentDataValue;
      }
      else if (currentData == "g")
      {
        valueArr[2] = currentDataValue;
      }
      else if (currentData == "b")
      {
        valueArr[3] = currentDataValue;
      }
      else if (currentData == "w")
      {
        valueArr[4] = currentDataValue;
      }
      else if (currentData == "index")
      {
        index = currentDataValue;
      }
      else if (currentData == "funcNum")
      {
        valueArr[0] = currentDataValue;
      }
      else if (currentData == "param")
      {
        valueArr[1] = currentDataValue;
      }
      else if (currentData == "turnOn")
      {
        doTurnOn = true;
        turnOnBool = currentDataValue;
      }

    } while (lastParamId != 0);

    if (!doTurnOn)
    {
      setJsonData(action, dataType, valueArr, index.toInt()); //updates file
    }
    else
    {
      bool arrSaveType;
      if (turnOnBool == "true")
      {
        arrSaveType = true;
        setJsonArrData(arrSaveType, saveTxt);
      }
      else
      {
        arrSaveType = false;
        setJsonArrData(arrSaveType, saveTxt);
        setJsonArrData(!arrSaveType, defaultTxt);
      }
      for (int i = 0; i < 30; i++)
      {
        if (adrStartEnd[i][0] != 0)
        {
          displayAdrColors(adrStartEnd[i], rgb[i]);
        }
        else
        {
          break;
        }
      }
    }
    request->send(200, "text/plain", "Json updated");
  });
}

int countChars(char findChar, String findString) //return number of occurances of given char in given String
{
  int appCount;
  for (int i = 0; i < findString.length(); i++)
  {
    if (findString[i] == findChar)
    {
      appCount++;
    }
  }
  return appCount;
}