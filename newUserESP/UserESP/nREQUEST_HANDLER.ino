void serverFunctions() {//Tiek ievietots setup funkcijā, izpilda visas nepieciešamās funkcijas saņemot vai nosūtot datus
  //  server.on("/", handleRoot);      //Lapas parādīšanai
  server.on("/esp32.local", HTTP_GET, [](AsyncWebServerRequest * request) {//vai mdns vajag laiku lai ielādētos?
    mySerial.println("GOT IT");
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/styles.css", "text/css");
  });

  server.on("/iro-transparency-plugin.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/iro-transparency-plugin.min.js", "text/js");
  });

  server.on("/iro.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/iro.min.js", "text/js");
  });

  server.on("/loadingScreen.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/loadingScreen.js", "text/js");
  });
  server.on("/global.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/global.js", "text/js");
  });

  server.on("/Constructor.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/Constructor.js", "text/js");
  });

  server.on("/CollapsibleButton.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/CollapsibleButton.js", "text/js");
    mySerial.println("aaaaaa");
  });

  server.on("/Icon.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/Icon.js", "text/js");
  });
  server.on("/SGLSscripts.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/SGLSscripts.js", "text/js");
  });

  server.on("/data.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/data.js", "text/js");
  });
  server.on("/ColorBlock.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/ColorBlock.js", "text/js");
  });
  server.on("/AnimationsBlock.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/AnimationsBlock.js", "text/js");
  });


  server.on("/LampBlock.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/LampBlock.js", "text/js");
  });


  server.on("/SettingsPopUp.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/SettingsPopUp.js", "text/js");
  });





  server.on("/iroSet.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/iroSet.js", "text/js");
  });


  server.on("/InputForm.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/InputForm.js", "text/js");
  });



  /*SETTINGS LAPA*/
  server.on("/settings.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    mySerial.println("SETTINGS SEND");
    request->send(SPIFFS, "/settings.html", "text/html");
  });

  server.on("/setConstructor.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/setConstructor.js", "text/html");
  });



  /*TEST*/

  //  server.on("/check_ap_connection", HTTP_POST, [](AsyncWebServerRequest * request) {
  //    String recData = request->getParam("check_ap_connection")->value();
  //    mySerial.println(recData);
  //    request->send(200, "text/plain", "Post route");
  //  });
  server.on("/setlamp", HTTP_POST, [](AsyncWebServerRequest * request) {
    mySerial.println("INCOMIIIIIIIIING");
    String keyVal;
    String recData;


    if (request->hasParam("lamp", true)) {
      keyVal = request->getParam("lamp", true)->value();
//      mySerial.print("Post data: "); mySerial.println(keyVal);
      recvWithStartEndMarkers(keyVal);
      //      test(keyVal);
      //     //Apstrādā datus un sāk datu iesūtīšanu uz lampām
    } else {
      //handle an incomplete request
      keyVal = "some default value";
    }

    //    if (request->hasParam("data", true)) {
    //      mySerial.println(request->getParam("data", true)->value());
    //    } else {
    //      //handle an incomplete request
    //      keyVal = "some default value";
    //    }


//    recvWithStartEndMarkers(keyVal);
    request->send(200, "text/plain", "Post route");
  });
  //  server.on("/_set_lamp_", HTTP_ANY, [](AsyncWebServerRequest * request) {
  //    mySerial.println("dataRec");
  //    request->send(200, "text/plain", "yey");
  //  });


}

void test(String testString) {
  mySerial.print("TestData: "); mySerial.println(testString);
}
