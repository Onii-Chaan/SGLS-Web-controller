#include "funcHeader.h"

void serverFunctions()
{ //Tiek ievietots setup funkcija, izpilda visas nepieciesamas funkcijas sanemot vai nosutot datus
  //  server.on("/", handleRoot);      //Lapas paradisanai
  server.on("https://esp32.local/", HTTP_GET, [](AsyncWebServerRequest *request) { //vai mdns vajag laiku lai ieladetos?
    Serial.println("GOT IT");
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, sendPage(request, "/index.html"), "text/html");
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, sendPage(request, "/index.html"), "text/html");
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
    request->send(SPIFFS, sendPage(request, "/settings.html"), "text/html");
  });

  server.on("/setConstructor.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/setConstructor.js", "text/html");
  });

  server.on("/configFile.txt", HTTP_ANY, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/configFile.txt", "text/txt");
  });

  server.on("/signUp.html", HTTP_ANY, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, sendPage(request, "/signUp.html"), "text/html");
  });

  server.on("/signIn.html", HTTP_ANY, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, sendPage(request,"/signIn.html"), "text/html");
  });

  server.on("/loginStyle.css", HTTP_ANY, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/loginStyle.css", "text/css");
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
      quitTrans = true; //stops data transmit for one cycle

    }
    else
    {
      //handle an incomplete request
      keyVal = "some default value";
    }

    request->send(200, "text/plain", "post route");

    // AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Post route");
    // response->addHeader("Set-Cookie", "id=espTestCookie; expires=Sat, 19 Apr 2020 12:00:00 UTC"); //Secure; HttpOnly
    // request->send(response);
  });

  server.on("/setJson", HTTP_POST, [](AsyncWebServerRequest *request) {
    // Serial.println(F("setJsonData"));
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Json updated");

    String action;      //the action that has to be done (add, delete, edit)
    String type;        //gets the query string
    String dataType;    //gets the data type that has to be updated
    String index;       //gets the index of data type array to be updated
    String valueArr[5]; //stores variables

    String turnOnBool;
    bool doTurnOn = false;
    bool sign = false;
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

      // Serial.print("CurrentData: ");
      // Serial.println(currentData);
      // Serial.print("Value: ");
      // Serial.println(currentDataValue);

      if (currentData == "action")
      {
        action = currentDataValue;
      }
      else if (currentData == "dataType" || currentData == "data" /*New network credentials*/)
      {
        dataType = currentDataValue;
        if (dataType == "signupdata" || dataType == "signindata")
          sign = true;
      }
      else if (currentData == "name" || currentData == "ssid" || currentData == "linkName" || currentData == "num")
      {
        valueArr[0] = currentDataValue;
      }
      else if (currentData == "value" || currentData == "r" || currentData == "pass" || currentData == "funcNum")
      {
        valueArr[1] = currentDataValue;
      }
      else if (currentData == "g" || currentData == "param")
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
      else if (currentData == "turnOn")
      {
        doTurnOn = true;
        turnOnBool = currentDataValue;
        action = "edit";
        dataType = currentData;
        valueArr[0] = currentDataValue;
      }
      else if (currentData == "changeWifi")
      {
        dataType = currentData;
        valueArr[0] = currentDataValue;
      }

    } while (lastParamId != 0);

    if (!doTurnOn && !sign)
    {
      if (dataType == "wlan" || dataType == "softap" || dataType == "newLampCount" || dataType == "newMdns" || dataType == "changeWifi" || dataType == "data" || dataType == "factoryReset")
      {
        action = "edit";
      }
      // Serial.print("action: ");Serial.println(action);
      // Serial.print("dataType: ");Serial.println(dataType);
      // Serial.print("valueArr[0]: ");Serial.println(valueArr[0]);
      // Serial.print("valueArr[1]: ");Serial.println(valueArr[1]);
      // Serial.println();

      setJsonData(action, dataType, valueArr, index.toInt()); //updates file

      if (dataType == "factoryReset")
      { //resets saved array JSON values
        setJsonArrData(true, defaultTxt);
        setJsonArrData(false, saveTxt);
        loopThroughStartEnd();
      }
      else if (dataType == "resetPassword")
      {
        saveJsonPassword("userPass", "");
        saveJsonPassword("sessions", "null");
        request->redirect("/signUp.html");
      }
    }
    else if (doTurnOn)
    {
      setJsonData(action, dataType, valueArr, index.toInt()); //updates file
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
      turnOn = true;
      loopThroughStartEnd();
      if (turnOnBool == "true") //sets turnOn bool on needed value without need of using json
        turnOn = true;
      else
        turnOn = false;
    }
    else if (sign) //if sign in or sign up data has been received
    {
      Serial.print("DataType: ");
      Serial.println(dataType);
      Serial.print("Pass: ");
      Serial.println(valueArr[1]);

      if (dataType == "signupdata") //if user signs ups
      {
        saveJsonPassword("userPass", valueArr[1]); //saves password
        // response = request->beginResponse(200, "text/plain", "redirect");
        request->redirect("/signIn.html");
      }
      else if (dataType == "signindata")
      {

        AsyncWebHeader *h;
        if (request->hasHeader("SESSID")) //tiek pārbaudīts vai nepieciešamais headeris vispār eksistē
        {
          h = request->getHeader("SESSID");
          if (checkJsonSessId(h->value()))
          {
            Serial.println("REDIRECT TO CONTROLLER SESSID");
            request->redirect("/index.html");
          }
          else if (valueArr[1] == getJsonPass("userPass"))
          {
            sessIdAns(response, valueArr[2]); //valueArr[2] tiek glabāts cookie expiration date
            response->addHeader("ReqRedirect", "/index.html");
            request->send(response);

            Serial.println("REDIRECT TO CONTROLLER NEW PASS BUT DELETE OLD COOKIE");
          }
          else
          {
            Serial.println("INCORRECT PASS");
          }
        }
        else if (valueArr[1] == getJsonPass("userPass")) //redirect to controller
        {
          sessIdAns(response, valueArr[2]); //valueArr[2] tiek glabāts cookie expiration date
          response->addHeader("ReqRedirect", "/index.html");
          request->send(response);
          Serial.println("REDIRECT TO CONTROLLER NEW PASS");
        }
        else
        {
          Serial.println("INCORRECT PASS");
        }
      }
    }
    request->send(response);
  });
}

void sessIdAns(AsyncWebServerResponse *reponseRef, String expTime) //creates and saves cookie, creates header
{
  unsigned long randomId = random(0, 2000000000); //creates sessionID and saves it
  saveJsonPassword("sessions", String(randomId));
  reponseRef->addHeader("Set-Cookie", String(randomId) + "; Expires=" + expTime); //gets ready cookie for sendout
  Serial.println(expTime);
}

int countChars(char findChar, String findString) //return number of occurances of given char in given String
{
  int appCount = 0;
  for (int i = 0; i < findString.length(); i++)
    if (findString[i] == findChar)
      appCount++;

  return appCount;
}

String sendPage(AsyncWebServerRequest *requestRef, String defPage) //checks if cookie value matches with saved sessids
{
  if (getJsonPass("userPass") == "") //if password is not saved yet
  {
    return "/signUp.html";
  }
  else if (defPage == "/signUp.html") //if password is saved and user tries to sign in
  {
    return "/signIn.html";
  }
  else
  {
    AsyncWebHeader *h;                   // for storing header object
    if (requestRef->hasHeader("Cookie")) //tiek pārbaudīts vai nepieciešamais headeris vispār eksistē
    {
      h = requestRef->getHeader("Cookie"); //for getting cookie from header
      if (!checkJsonSessId(h->value()))
        return "/signIn.html"; //redirects to sign in page if there are no cookie value requested
      else
        return defPage;
    }
  }
  return "/signIn.html";
}