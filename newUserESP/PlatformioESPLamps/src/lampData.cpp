#include "funcHeader.h"

void setRgbColors(byte arr[30 /*numLeds*/][4 /*colorCount*/], byte valueToPut[4 /*colorCount*/])
{ //iestata 2d krasu masiva atbilstosas krasu vertibas
  bool breakOut = false;
  for (int i = 0; i < 30 /*numLeds*/; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      for (int x = 0; x < 30 /*numLeds*/; x++)
      {
        for (int y = 0; y < 2; y++)
        {
          if (oldAdrStartEnd[i][j] == adrStartEnd[x][y] && adrStartEnd[x][y] != 0)
          {
            breakOut = true;
            break;
          }
          else if (adrStartEnd[x][y] == 0)
          {
            for (int z = 0; z < 4 /*colorCount*/; z++)
            {
              rgb[i][z] = 0;
            }
            break;
          }
        }
        if (breakOut)
        {
          break;
        }
      }
      if (breakOut)
      {
        break;
      }
    }
    breakOut = false;
  }

  for (int i = 30 /*numLeds*/; i > startIn; i--)
  { //pabida vertibas uz labo pusi lidz startIn+1, jo startIn vertibu aiztikt nevar ta iemesla del, ka tad var par vienu vienibu pabidities nepareiza vertiba ta, kas atradas ieks startIn ieprieks
    if (adrStartEnd[i][0] != oldAdrStartEnd[i][0] && adrStartEnd[i][1] != oldAdrStartEnd[i][1])
    {
      for (int j = 0; j < 4 /*colorCount*/; j++)
      {
        rgb[i][j] = rgb[i - 1][j];
      }
    }
  }

  for (int i = 0; i < 4 /*colorCount*/; i++)
  {
    rgb[startIn][i] = rgbReceive[i]; //ievieto jauno vertibu masiva
  }

  if (divide)
  { //ja 2d vertiba, kas ievadita 2d masiva atradas pa vidu esosai
    for (int i = 0; i < 4 /*colorCount*/; i++)
    {
      rgb[startIn + 1][i] = rgb[startIn - 1][i]; //ievieto jauno vertibu masiva
    }
  }

  bool breakCheck = true;  //darbina un izbeidz while ciklu
  int countFreeSpaces = 0; //skaita brivas vietas starp startIn un visu, kas atrodas masiva labaja puse
  int startFreeSpace = 1;  //skaita pedejo atskaites punktu, sunu, kas pedejo reizi tika aiznemta
  while (breakCheck)
  {
    for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++)
    {
      byte zeroCount = 0; //skaita cik no masiva krasu vertibam ir 0
      for (int j = 0; j < 4 /*colorCount*/; j++)
      {
        if (rgb[i][j] != 0)
        {
          break;
        }
        else
        {
          zeroCount++;
        }
      }
      if (zeroCount == 4 /*colorCount*/)
      { //ja visas masiva krasu vertibas bija nulle
        countFreeSpaces++;
      }
      else if (countFreeSpaces > 0)
      {
        break;
      }
      if (i == 30 /*numLeds*/ - 1)
      { //ja visas veribas pec pedejas aizpilditas sunas ir nulle tad funkcija beidz savu darbibu
        breakCheck = false;
        break;
      }
    }
    if (breakCheck == false)
    {
      break;
    }
    for (int i = 0; i < 4 /*colorCount*/; i++)
    {
      rgb[startIn + startFreeSpace][i] = rgb[countFreeSpaces + startFreeSpace + startIn][i];
      rgb[countFreeSpaces + startFreeSpace + startIn][i] = 0;
    }
    countFreeSpaces = 0;
    startFreeSpace++;
  }
  for (int i = 0; i < 30 /*numLeds*/; i++)
  { //pedeja parbaude, kas nosaka to vai pretim 2d dalai, kuras vertiba ir nulle atrodas 1d suna, kuras vertiba lielaka par nulli
    if (adrStartEnd[i][0] == 0)
    {
      for (int j = 0; j < 4 /*colorCount*/; j++)
      {
        rgb[i][j] = 0;
      }
    }
  }
  /*Serial.println("Colors: ");
    Serial.println('{');
    for (int i = 0; i <= 2 numLeds; i++) {
    for (int j = 0; j < 4 colorCount; j++) {
      if (j == 0) {
        Serial.println('{');
      }
      Serial.println(rgb[i][j]);

      if (j != 4 colorCount - 1) {
        Serial.println(',');
      }
    }
    Serial.println('}');
    }
    Serial.println('}');*/
}

void setValueInArr(uint32_t arr[30 /*numLeds*/], uint32_t valueToPut, bool debug = false)
{ //ievieto ievadito vertibu atbilstosaja 1d masiva atkariba no esosa 2d masiva
  if (!newGroupValue)//checks if led part start end arr has changed and puts value in exact place
  {
    arr[startIn] = valueToPut;
  }
  else
  {
    if (debug)
    {
      Serial.println("befdef: ");
      Serial.print('{');
      for (int i = 0; i <= 30; i++)
      {

        Serial.print(arr[i]);
        Serial.print(',');
      }
      Serial.println('}');
    }

    for (int i = 30 /*numLeds*/; i > startIn; i--)
    { //pabida vertibas uz labo pusi lidz startIn+1, jo startIn vertibu aiztikt nevar ta iemesla del, ka tad var par vienu vienibu pabidities nepareiza vertiba ta, kas atradas ieks startIn ieprieks
      arr[i] = arr[i - 1];
    }

    if (debug)
    {
      Serial.println("bef: ");
      Serial.print('{');
      for (int i = 0; i <= 30; i++)
      {

        Serial.print(arr[i]);
        Serial.print(',');
      }
      Serial.println('}');
    }

    for (int i = 0; i < 30; i++) //deletes values that matches old led part array values
    {
      if (oldAdrStartEnd[i][0] >= ledPartStartEnd[0] && (oldAdrStartEnd[i][1] <= ledPartStartEnd[1]+1 || oldAdrStartEnd[i][0] <= ledPartStartEnd[1]+1))
      {
        arr[i] = 0;
      }
    }

    arr[startIn] = valueToPut; //ievieto jauno vertibu masiva

    if (debug)
    {
      Serial.println("after: ");
      Serial.print('{');
      for (int i = 0; i <= 30; i++)
      {

        Serial.print(arr[i]);
        Serial.print(',');
      }
      Serial.println('}');
    }
    if (divide)
    {                                                    //ja 2d vertiba, kas ievadita 2d masiva atradas pa vidu esosai
      for (int i = 30 /*numLeds*/; i > startIn + 1; i--) //moves values to right side to make space for divided value
      {
        arr[i] = arr[i - 1];
      }
      arr[startIn + 1] = arr[startIn - 1]; //puts divided value in array
    }

    bool breakCheck = true;  //darbina un izbeidz while ciklu
    int countFreeSpaces = 0; //skaita brivas vietas starp startIn un visu, kas atrodas masiva labaja puse
    int startFreeSpace = 1;  //skaita pedejo atskaites punktu, sunu, kas pedejo reizi tika aiznemta
    while (breakCheck)
    {
      for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++)
      {
        if (arr[i] == 0)
        {
          countFreeSpaces++;
        }
        else if (countFreeSpaces > 0)
        {
          break;
        }
        if (i == 30 /*numLeds*/ - 1)
        { //ja visas veribas pec pedejas aizpilditas sunas ir nulle tad funkcija beidz savu darbibu
          breakCheck = false;
          break;
        }
      }
      if (breakCheck == false)
      {
        break;
      }
      arr[startIn + startFreeSpace] = arr[countFreeSpaces + startFreeSpace + startIn];
      arr[countFreeSpaces + startFreeSpace + startIn] = 0;

      countFreeSpaces = 0;
      startFreeSpace++;
    }

    for (int i = 0; i < 30 /*numLeds*/; i++)
    {
      if (adrStartEnd[i][0] == 0)
      {
        arr[i] = 0;
      }
    }

    if (debug)
    {
      Serial.println("setVal: ");
      Serial.print('{');
      for (int i = 0; i <= 30; i++)
      {

        Serial.print(arr[i]);
        Serial.print(',');
      }
      Serial.println('}');
      Serial.println();
    }
  }
}

void displayAdrColors(int startEnd[2], byte colorToDisplay[4 /*colorCount*/])
{ //iestata krasas spidesanu kadam gabalam adresejamam diodem
  String sendOut;
  for (int i = startEnd[0]; i <= startEnd[1]; i++)
  {
    sendOut = "<";
    if (i < 10)
    {
      sendOut += 0;
      sendOut += i;
    }
    else
    {
      sendOut += i;
    }
    for (int j = 0; j < 4 /*colorCount*/; j++)
    {
      if (colorToDisplay[j] < 10)
      {
        sendOut += "00";
        sendOut += colorToDisplay[j];
      }
      else if (colorToDisplay[j] < 100)
      {
        sendOut += 0;
        sendOut += colorToDisplay[j];
      }
      else
      {
        sendOut += colorToDisplay[j];
      }
    }
    sendOut += ">";
    // digitalWrite(2, HIGH);
    // delay(1000);
    // digitalWrite(2, LOW);
    // delay(1000);
    if(turnOn)
      Serial.println(sendOut);
    // digitalWrite(2, HIGH);
    // delay(1000);
    // digitalWrite(2, LOW);
  }
}

void recvWithStartEndMarkers(String inputString)
{ //datu nolasisanas funkcija
  //  Serial.println("In recvWithStartEndMarkers");
  int countDataSwCase; //recvWithStartEndMarkers switch operatora skaititajs
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char ledPartEndMarker = '#';
  char adrLedNumDivider = '-';

  char rc; //saja mainigaja tiek saglabats katrs ienakosais baits

  for (int x = 0; x < inputString.length(); x++)
  {
    //      Serial.println("LoopVal: ");Serial.println(x);
    rc = inputString[x];
    if (recvInProgress == true)
    {
      if (rc != endMarker)
      {
        receivedChars[ndx] = rc; //no siem datiem tiek pieskirtas mainigo vertibas, kas tiek iesutitas un no saraksta parveidotas skaitli
        ndx++;
        switch (countDataSwCase)
        {
        case 1: //tiek noteikts ienakoso datu tips
          dataType = atoi(receivedChars);
          ndx = 0;
          break;
        case 2: //tiek noteikts kuriem led pikseliem ir jastrada
          ndx = 0;
          adrStartEndUpdateNum = 0;

          do
          {
            x++;
            //              if (Serial.available() > 0) {
            if (isDigit(rc))
            { //ja sanemtais baits ir cipars, tad tas tiek ievietots ieks saraksta talakai apstradei
              receivedChars[ndx] = rc;
              ndx++;
            }
            rc = inputString[x];
            if (rc == adrLedNumDivider)
            { //ja sanemtais baits ir '-', tad tas nozime, ka tiek sanemti adresejamo diozu lentas dati
              ledPartStartEnd[0] = atoi(receivedChars);
              ndx = 0;
            }
            else if (rc == ledPartEndMarker)
            {
              ledPartStartEnd[1] = atoi(receivedChars);
              ndx = 0;
              for (int i = 0; i < 3; ++i)
              { //notira receivedChars masivu
                receivedChars[i] = (char)0;
              }
            }
            //                x++;
            //
          } while (rc != ledPartEndMarker); //kamer nav sanemts # simbols
          ndx = 0;
          break;
        case 4:
          if (dataType == 1)
          { //funkcijas numura iestatisana
            funcNum = atoi(receivedChars);
            ndx = 0;
          }
          break;
        case 5:
          if (dataType == 0)
          { //sarkanas krasas iestatisana
            rgbReceive[0] = atoi(receivedChars);
            ndx = 0;
          }
          break;
        case 7:
          if (dataType == 1)
          { //funkcijas parametru vertibas iestatisana
            funcPar = atoi(receivedChars);
            ndx = 0;
          }
          break;
        case 8: //zalas krasas iestatisana
          if (dataType == 0)
          { //zalas krasas iestatisana
            rgbReceive[1] = atoi(receivedChars);
          }
          ndx = 0;
          break;
        case 11: //zilas krasas iestatisana
          if (dataType == 0)
          { //zalas krasas iestatisana
            rgbReceive[2] = atoi(receivedChars);
          }
          ndx = 0;
          break;
        case 14: //baltas krasas iestatisana
          if (dataType == 0)
          { //zalas krasas iestatisana
            rgbReceive[3] = atoi(receivedChars);
          }
          ndx = 0;
          break;
        default:
          break;
        }
        if (ndx >= numChars)
        {
          ndx = numChars - 1;
        }
      }
      else
      {
        receivedChars[sizeof(receivedChars)] = '\0'; // terminate the string, svariga koda rindina, kur ieprieks [] ieksa bija ndx. Ndx patstavigi mainas, tapec bija nepieciesams ievietot citu garuma vertibu
        recvInProgress = false;
        //        newData = true;
        //        Serial.println("SETNEWDATA");
        setNewData();
      }
      countDataSwCase++; //datu sadalisanas dalas skaititajs
    }
    else if (rc == startMarker)
    {
      recvInProgress = true;
      countDataSwCase = 1; //reseto mainigo no ieprieksejas vertibas
    }
  }
}

void setNewData()
{ //sanemto datu apstrade
  Serial.println();//!!!!!!!!!!!!
  for (int i = 0; i < 3; ++i)
  { //notira receivedChars masivu
    receivedChars[i] = (char)0;
  }
  updateAdrLedPart(ledPartStartEnd); //apdeito diozu dalu masivu
  if (dataType == 0)
  { //ja ir iestatita krasa, tad atbilstosajas vietas funkcijas parametrs un funkcijas numurs tiks mainits uz nulli
    funcNum = 1;
    funcPar = 1;
  }
  //    Serial.println("a");
  setValueInArr((uint32_t *)funcNumArr, (uint32_t)funcNum);
  //    Serial.println("b");
  setValueInArr((uint32_t *)oldTimeInt, 1);
  //    Serial.println("c");
  setValueInArr((uint32_t *)funcParArr, (uint32_t)funcPar);
  //    Serial.println("d");
  isFirstTime[startIn] = 1; //saglaba pirmo reizi, tikai tad, kad ir tas iestatits
  //    Serial.println("e");
  setValueInArr((uint32_t *)blinkOff, 1);

  if (dataType == 0)
  { //ta pati funkcija, kas setValueInArr, bet paredzeta darbam ar 2d masivu. Krasu iestatisana atbilstosajas sunas
    // Serial.println("COLOR SET");
    setRgbColors(rgb, rgbReceive);
    displayAdrColors(ledPartStartEnd, rgbReceive);
  }
  else
  { //ja tika iestatita funkcijas vertiba, tad jaatbrivo atbilstosa krasas vieniba
    // Serial.println("ANIM SET");

    for (int i = 0; i < 4 /*colorCount*/; i++)
    { //jo funkcijai setRgbColors nevar padot rgvReceive no ieprieksejas vertibas, vai pointeri uz rgb[startIn]
      rgbReceive[i] = rgb[startIn][i];
    }
    setRgbColors(highVal, rgbReceive);
  }
  //  newData = false;
}

void funcExecute()
{ //iet cauri funcNum masiva vertibam un atbilstosi izpilda katru funkciju, kas der
  for (int i = 0; i < 30 /*numLeds*/; i++)
  { //nepieciesams, lai dzitu uz prieksu for ciklu un ta vertibu izmantot jau ka parametru izpildamajai funkcijai
    if (funcNumArr[i] == 0)
    { //izbeidz funkcijas darbibu, ja funcNum masiva tiek atrasta vertiba 0
      //      Serial.println("Found 0");
      break;
    }
    if (funcNumArr[i] != 1)
    {
      switch (funcNumArr[i])
      {       //funkciju numuri sakas no 2 ieskaitot
      case 2: //izpildas solid rainbow
        if (isFirstTime[i])
        { //ja funkcija notiek pirmo reizi, tad tiek iestatitas sakuma vertibas
          oldTimeInt[i] = millis();
          solidRainbow(i, 1);
          isFirstTime[i] = 0;
        }
        else if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          oldTimeInt[i] = millis();
          solidRainbow(i);
        }
        break;
      case 3: //solid fade
        if (isFirstTime[i])
        { //vienu reizi tiek saglabatas augstakas krasu vertibas, kas ari velak tiek feidotas
          for (int x = 0; x < 4 /*colorCount*/; x++)
          {
            highVal[i][x] = rgb[i][x];
          }
          isFirstTime[i] = 0;
        }
        if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          oldTimeInt[i] = millis();
          solidFade(highVal[i], funcParArr[i] * 100, millis(), i);
        }
        break;
      case 4: //blink
        if (isFirstTime[i])
        {
          for (int x = 0; x < 4 /*colorCount*/; x++)
          {
            highVal[i][x] = rgb[i][x];
          }
        }
        isFirstTime[i] = 0;
        if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          if (blinkOff[i] == true)
          { //sis globalais buls seko lidzi tam vai gaisma tiek ieslegta vai izslegta
            blinkOff[i] = false;
          }
          else
          {
            blinkOff[i] = true;
          }
          solidBlink(highVal[i], blinkOff[i], i);
          oldTimeInt[i] = millis();
        }
        break;
      case 5: //fire
        if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          fire(i);
          oldTimeInt[i] = millis();
        }
        break;
      case 6: //adr rainbow
        if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          rainbow(i);
          oldTimeInt[i] = millis();
        }
        break;
      case 7:
        if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i])
        {
          lightMusic(i);
        }
        break;
      }
    }
  }
}

void updateAdrLedPart(int startEnd[2])
{ //Jaizveido vertibu pastumsana uz kreiso pusi pec labas masiva puses apstrades
  divide = false;
  startIn = 0;
  for (int i = 0; i < 30 /*numLeds*/; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      oldAdrStartEnd[i][j] = adrStartEnd[i][j];
    }
  }

  for (int i = 0; i < 30 /*numLeds*/; i++)
  { //atrod startIn vertibu
    if (adrStartEnd[i][0] >= startEnd[0])
    {
      startIn = i + 1;
      break;
    }
    else if (adrStartEnd[i][0] < startEnd[0] && !(adrStartEnd[i + 1][0] > adrStartEnd[i][0]))
    {
      if (adrStartEnd[i + 1][1] == startEnd[1])
      {
        startIn = i + 3;
        break;
      }
      startIn = i + 2;
      break;
    }
    else if (adrStartEnd[i][0] == 0)
    {
      startIn = i + 1;
      break;
    }
  }
  startIn--;
  //Serial.println(startIn);////////////////////////////////////////////////////////////////////////START IN///////////////////////////////
  for (int i = 30 /*numLeds*/; i >= startIn; i--)
  { //"pabida" vertibas uz labo pusi
    for (int x = 0; x < 2; x++)
    {
      if (startEnd[0] > adrStartEnd[startIn - 1][0] && startEnd[1] < adrStartEnd[startIn - 1][1] /*&& i - startIn >= 2*/ && adrStartEnd[i - 2][1] > 0)
      {
        adrStartEnd[i][x] = adrStartEnd[i - 2][x]; //novieto vertibu divas vertibas aiz, uz kreiso pusi
        divide = true;
      }
      else if (adrStartEnd[i - 1][1] > 0)
      {
        adrStartEnd[i][x] = adrStartEnd[i - 1][x];
      }
    }
  }

  for (int i = 0; i < 2; i++)
  { //Ievieto vertibas atbilstosajas dalas
    adrStartEnd[startIn][i] = startEnd[i];
  }

  if (startEnd[0] <= adrStartEnd[startIn - 1][1])
  { //masiva pirms ievadita masiva tiek salidzinatas vertibas un ja ta ir mazaka par ievadita masiva sakuma vertibu, tad ta paliek par 1 mazaka
    adrStartEnd[startIn - 1][1] = startEnd[0] - 1;
  }

  if (adrStartEnd[startIn - 1][1] < adrStartEnd[startIn - 1][0])
  { //ja izmainu rezultata masiva beigu vertiba ir lielaka par sakuma vertibu, tad masiva vertiba klust par 0
    adrStartEnd[startIn - 1][0] = 0;
    adrStartEnd[startIn - 1][1] = 0;
  }

  bool breakCheck = false; //nepieciesams, lai tiktu ara no galvena lupa
  for (int i = startIn + 1; i < 30 /*numLeds*/; i++)
  { //parbauda cik talu sniedzas ievadita vertiba masiva pa labi un maina vertibas atbilstosi tam
    for (int x = 0; x < 2; x++)
    {
      if (adrStartEnd[i][x] == 0)
      {
        breakCheck = true;
        break;
      }
      if (adrStartEnd[i][x] > startEnd[1])
      {

        if (x == 0)
        {
          //adrStartEnd[i - 1][x + 1] = 0;/////////////////////////////////////////////////////////////////////////////////////////////
        }
        else
        {
          adrStartEnd[i][x - 1] = startEnd[1] + 1;
        }
        breakCheck = true;
        break;
      }
      else if (adrStartEnd[i][0] == startEnd[0] && adrStartEnd[i][1] == startEnd[1])
      {
        adrStartEnd[i][x] = 0;
        adrStartEnd[i][x + 1] = 0;
      }
      else if (adrStartEnd[i][x] == startEnd[1])
      {
        if (x == 0)
        {
          adrStartEnd[i][x] = adrStartEnd[i][x] + 1;
          if (adrStartEnd[i][x] > adrStartEnd[i][x + 1])
          {
            adrStartEnd[i][x] = 0;
            adrStartEnd[i][x + 1] = 0;
          }
        }
        else
        {
          adrStartEnd[i][x] = 0;
          adrStartEnd[i][x - 1] = 0;
        }
        breakCheck = true;
        break;
      }
      else if (adrStartEnd[i][0] < startEnd[1] && adrStartEnd[i][1] > startEnd[1])
      {
        adrStartEnd[i][x] = startEnd[1] + 1;
        breakCheck = true;
        break;
      }
      else
      {
        adrStartEnd[i][x] = 0;
      }
    }
    if (breakCheck == true)
    {
      breakCheck = false;
      break;
    }
  }

  breakCheck = true;       //darbina un izbeidz while ciklu
  int countFreeSpaces = 0; //skaita brivas vietas starp startIn un visu, kas atrodas masiva labaja puse
  int startFreeSpace = 1;  //skaita pedejo atskaites punktu, sunu, kas pedejo reizi tika aiznemta
  while (breakCheck)
  {
    for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++)
    {
      if (adrStartEnd[i][0] == 0)
      {
        countFreeSpaces++;
      }
      else if (countFreeSpaces > 0)
      { //ja adrStartEnd[i][0]>0, tad iziet ara no dota for cikla
        break;
      }
      if (i == 30 /*numLeds*/ - 1)
      { //ja visas veribas pec pedejas aizpilditas sunas ir nulle tad funkcija beidz savu darbibu
        breakCheck = false;
        break;
      }
    }
    if (breakCheck == false)
    {
      break;
    }
    for (int i = 0; i < 2; i++)
    {
      adrStartEnd[startIn + startFreeSpace][i] = adrStartEnd[countFreeSpaces + startFreeSpace + startIn][i];
      adrStartEnd[countFreeSpaces + startFreeSpace + startIn][i] = 0;
    }
    countFreeSpaces = 0;
    startFreeSpace++;
  }

  // Serial.println("Final: ");
  // Serial.print('{');
  // for (int i = 0; i <= 30; i++)
  // {
  //   for (int j = 0; j < 2; j++)
  //   {
  //     if (j == 0)
  //     {
  //       Serial.print('{');
  //       Serial.print(adrStartEnd[i][j]);
  //       Serial.print(',');
  //     }
  //     else
  //     {
  //       Serial.print(adrStartEnd[i][j]);
  //       Serial.print('}');
  //     }
  //   }
  // }
  // Serial.print('}');
  // Serial.println();

  newGroupValue = false;
  for (byte i = 0; i < 30; i++)//checks if old start end arr has changed
  {
    for (byte j = 0; j < 2; j++)
    {
      if (oldAdrStartEnd[i][j] != adrStartEnd[i][j])
      {
        newGroupValue = true;
        break;
      }
    }
    if (newGroupValue)
    {
      break;
    }
  }
}

bool newGroupValue;

void loopThroughStartEnd()
{
  for (int i = 0; i < 30; i++)
    if (adrStartEnd[i][0] != 0 && adrStartEnd[i][1] != 0){
      displayAdrColors(adrStartEnd[i], rgb[i]);
    }
    else
      break;
}