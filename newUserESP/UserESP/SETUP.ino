void setup() {
  Serial.begin(115200);
  startWifi();
  startEEPROM();
  startServer();
  serverFunctions();  
  setTimerFunctions();
  startSPIFFS();
  startMDNS();
  clearEEPROM(96, 192);

  adrStartEnd[0][0] = 1;
  adrStartEnd[0][1] = numLeds;

  funcNumArr[0] = 1;
  funcParArr[0] = 1;
  isFirstTime[0] = 1;
  blinkOff[0] = 1;
  oldTimeInt[0] = 1;

  delay(250);//lai lampas paspētu ielādēties
//  Serial.begin(9600);
  Serial.println("<00>");
  //strip.begin();
  //strip.clear();//notīra iepriekšējās krāsas no krāsu lentas
  //strip.show();//apdeito krāsu lentu, lai iepriekšējās krāsas tiktu notīrītas
}
