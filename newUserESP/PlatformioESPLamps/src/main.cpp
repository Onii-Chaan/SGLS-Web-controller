#include "funcHeader.h"

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  startSPIFFS();
  startMDNS();
  startWifi();
  startServer();
  serverFunctions();

  // setDefaultSave();

  // delay(5000);//so lamps could turn on
  Serial.println("<00>");
  

  

  if(jsonTurnOn()) //turns on or off lamps based on their last saved state in json file
    setJsonArrData(true, saveTxt);
  else
    setJsonArrData(true, defaultTxt);

  turnOn = true;
  loopThroughStartEnd();
  turnOn = jsonTurnOn();
}

void loop()
{
  funcExecute(); //konstanti darbina lampu dinamisko krasu funkcijas
  quitTrans = false;//allows data transmit
}

