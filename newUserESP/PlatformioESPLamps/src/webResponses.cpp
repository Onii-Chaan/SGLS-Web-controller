#include "funcHeader.h"

void serverFunctions()
{ //Tiek ievietots setup funkcija, izpilda visas nepieciesamas funkcijas sanemot vai nosutot datus
  //  server.on("/", handleRoot);      //Lapas paradisanai
  server.on("/esp32.local", HTTP_GET, [](AsyncWebServerRequest *request) { //vai mdns vajag laiku lai ieladetos?
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
    Serial.println("INCOMIIIIIIIIING");
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
    Serial.println(F("setJsonData"));
    String action;
    String type;
    String name;
    String value;
    String index;
    String valueArr[5];

    // int params = request->params();
    // Serial.print("ParamCount: ");
    // Serial.println(params);
    // for (int i = 0; i < params; i++)
    // {
    //   AsyncWebParameter *p = request->getParam(i);
    //   Serial.print("Data: ");
    //   Serial.println(p->value());
    // }

    int args = request->args();
    for (int i = 0; i < args; i++)
    {
      Serial.printf("ARG[%s]: %s\n", request->argName(i).c_str(), request->arg(i).c_str());
    }

    if (request->hasParam("type", true))
    {
      type = request->getParam("type", true)->value();
    }

    if (request->hasParam("name", true))
    {
      valueArr[0] = request->getParam("name", true)->value();
    }

    if (request->hasParam("index", true))
    {
      index = request->getParam("index", true)->value();
    }

    if (request->hasParam("r", true))
    {
      valueArr[1] = request->getParam("r", true)->value();
    }

    if (request->hasParam("g", true))
    {
      valueArr[2] = request->getParam("g", true)->value();
    }

    if (request->hasParam("b", true))
    {
      valueArr[3] = request->getParam("b", true)->value();
    }

    if (request->hasParam("w", true))
    {
      valueArr[4] = request->getParam("w", true)->value();
    }

    if (request->hasParam("funcNum", true))
    {
      valueArr[1] = request->getParam("funcNum", true)->value();
    }

    if (request->hasParam("param", true))
    {
      valueArr[2] = request->getParam("param", true)->value();
    }

    if (request->hasParam("value", true))
    {
      valueArr[1] = request->getParam("value", true)->value();
    }

    if (request->hasParam("?action", true))
    {
      action = request->getParam("?action", true)->value();
      Serial.println("hasAction");
    }


    for (int i = 0; i < 5; i++)
    {
      Serial.print("valarr: ");
      Serial.println(valueArr[i]);
    }

    setJsonData(action, type, valueArr, index.toInt());
    request->send(200, "text/plain", "Json updated");
  });

  //   server.on("/setlamp", HTTP_POST, [](AsyncWebServerRequest * request) {
  //     Serial.println(F("INCOMIIIIIIIIING"));
  //     String keyVal;
  //     String recData;

  //     if (request->hasParam("lamp", true)) {
  //       keyVal = request->getParam("lamp", true)->value();
  // //      Serial.println("Post data: "); Serial.println(keyVal);
  //       recvWithStartEndMarkers(keyVal);
  //       //     //Apstrada datus un sak datu iesutisanu uz lampam
  //     } else {
  //       //handle an incomplete request
  //       keyVal = "some default value";
  //     }
  //     request->send(200, "text/plain", "Post route");
  //   });
}
