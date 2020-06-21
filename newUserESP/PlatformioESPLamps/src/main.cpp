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

  if (jsonTurnOn()) //turns on or off lamps based on their last saved state in json file
    setJsonArrData(true, saveTxt);
  else
    setJsonArrData(true, defaultTxt);

  turnOn = true;
  loopThroughStartEnd();
  turnOn = jsonTurnOn();
}

unsigned long testTimeInt = 0;

void loop()
{
  funcExecute();     //konstanti darbina lampu dinamisko krasu funkcijas
  quitTrans = false; //allows data transmit

  // delay(1000);

  if (millis() - testTimeInt >= 1000)
  {
    testTimeInt = millis();
    Serial.println("Colors: ");
    Serial.print('{');
    for (int i = 0; i <= 6; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (j == 0)
        {
          Serial.print('{');
        }
        Serial.print(rgb[i][j]);

        if (j != 4 - 1)
        {
          Serial.print(',');
        }
      }
      Serial.print('}');
    }
    Serial.println('}');
  }
}
