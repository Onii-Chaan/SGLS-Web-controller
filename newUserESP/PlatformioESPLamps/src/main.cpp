#include "funcHeader.h"

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  startSPIFFS();
  startMDNS();
  startWifi();
  startServer();
  serverFunctions();

  


  // setDefaultSave();

  digitalWrite(2, HIGH);
  // delay(5000);//so lamps could turn on
  Serial.println("<00>");
  digitalWrite(2, LOW);

  setJsonArrData(true, saveTxt);
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

void loop()
{
  funcExecute(); //konstanti darbina lampu dinamisko krasu funkcijas

  // delay(500);
  // MDNS.begin("esp32");
}
