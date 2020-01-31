void loop() {
  funcExecute();//konstanti darbina lampu dinamisko krāsu funkcijas
}







void setRgbColors(byte arr[30 /*numLeds*/][4 /*colorCount*/], byte valueToPut[4 /*colorCount*/]) { //iestata 2d krāsu masīvā atbilstošās krāsu vērtības
  bool breakOut = false;
  for (int i = 0; i < 30 /*numLeds*/; i++) {
    for (int j = 0; j < 2; j++) {
      for (int x = 0; x < 30 /*numLeds*/; x++) {
        for (int y = 0; y < 2; y++) {
          if (oldAdrStartEnd[i][j] == adrStartEnd[x][y] && adrStartEnd[x][y] != 0) {
            breakOut = true;
            break;
          } else if (adrStartEnd[x][y] == 0) {
            for (int z = 0; z < 4 /*colorCount*/; z++) {
              rgb[i][z] = 0;
            }
            break;
          }
        }
        if (breakOut) {
          break;
        }
      }
      if (breakOut) {
        break;
      }
    }
    breakOut = false;
  }

  for (int i = 30 /*numLeds*/; i > startIn; i--) { //pabīda vērtības uz labo pusi līdz startIn+1, jo startIn vērtību aiztikt nevar tā iemesla dēļ, ka tad var par vienu vienību pabīdīties nepareizā vērtība tā, kas atradās iekš startIn iepriekš
    if (adrStartEnd[i][0] != oldAdrStartEnd[i][0] && adrStartEnd[i][1] != oldAdrStartEnd[i][1]) {
      for (int j = 0; j < 4 /*colorCount*/; j++) {
        rgb[i][j] = rgb[i - 1][j];
      }
    }
  }

  for (int i = 0; i < 4 /*colorCount*/; i++) {
    rgb[startIn][i] = rgbReceive[i];//ievieto jauno vērtību masīvā
  }

  if (divide) {//ja 2d vērtība, kas ievadīta 2d masīvā atradās pa vidu esošai
    for (int i = 0; i < 4 /*colorCount*/; i++) {
      rgb[startIn + 1][i] = rgb[startIn - 1][i]; //ievieto jauno vērtību masīvā
    }
  }

  bool breakCheck = true;//darbina un izbeidz while ciklu
  int countFreeSpaces = 0;//skaita brīvās vietas starp startIn un visu, kas atrodas masīva labajā pusē
  int startFreeSpace = 1;//skaita pēdējo atskaites punktu, šūnu, kas pēdējo reizi tika aizņemta
  while (breakCheck) {
    for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++) {
      byte zeroCount = 0;//skaita cik no masīva krāsu vērtībām ir 0
      for (int j = 0; j < 4 /*colorCount*/; j++) {
        if (rgb[i][j] != 0) {
          break;
        } else {
          zeroCount ++;
        }
      }
      if (zeroCount == 4 /*colorCount*/) {//ja visas masīva krāsu vērtības bija nulle
        countFreeSpaces++;
      } else if (countFreeSpaces > 0) {
        break;
      }
      if (i == 30 /*numLeds*/ - 1) {//ja visas vērības pēc pēdējās aizpildītās šūnas ir nulle tad funkcija beidz savu darbību
        breakCheck = false;
        break;
      }
    }
    if (breakCheck == false) {
      break;
    }
    for (int i = 0; i < 4 /*colorCount*/; i++) {
      rgb[startIn + startFreeSpace][i] = rgb[countFreeSpaces + startFreeSpace + startIn][i];
      rgb[countFreeSpaces + startFreeSpace + startIn][i] = 0;
    }
    countFreeSpaces = 0;
    startFreeSpace++;
  }
  for (int i = 0; i < 30 /*numLeds*/; i++) { //pēdējā pārbaude, kas nosaka to vai pretim 2d daļai, kuras vērtība ir nulle atrodas 1d šūna, kuras vērtība lielāka par nulli
    if (adrStartEnd[i][0] == 0) {
      for (int j = 0; j < 4 /*colorCount*/; j++) {
        rgb[i][j] = 0;
      }
    }
  }
  /*Serial.println("Colors: ");
    Serial.print('{');
    for (int i = 0; i <= 2 /*numLeds; i++) {
    for (int j = 0; j < 4 /*colorCount; j++) {
      if (j == 0) {
        Serial.print('{');
      }
      Serial.print(rgb[i][j]);

      if (j != 4 /*colorCount - 1) {
        Serial.print(',');
      }
    }
    Serial.print('}');
    }
    Serial.println('}');*/
}

void setValueInArr(uint32_t arr[30 /*numLeds*/], uint32_t valueToPut) {//ievieto ievadīto vērtību atbilstošajā 1d masīvā atkarībā no esošā 2d masīva
  bool breakOut = false;
//  Serial.println("Inside");
  for (int i = 0; i < 30 /*numLeds*/; i++) {
    for (int j = 0; j < 2; j++) {
      for (int x = 0; x < 30 /*numLeds*/; x++) {
        for (int y = 0; y < 2; y++) {
          if (oldAdrStartEnd[i][j] == adrStartEnd[x][y] && adrStartEnd[x][y] != 0) {
            breakOut = true;
            break;
          } else if (x == 30 /*numLeds*/ - 1 || adrStartEnd[x][y] == 0) {
            arr[x] = 0;
            break;
          }
        }
        if (breakOut) {
          break;
        }
      }
      if (breakOut) {
        break;
      }
    }
    breakOut = false;
  }

  for (int i = 30 /*numLeds*/; i > startIn; i--) { //pabīda vērtības uz labo pusi līdz startIn+1, jo startIn vērtību aiztikt nevar tā iemesla dēļ, ka tad var par vienu vienību pabīdīties nepareizā vērtība tā, kas atradās iekš startIn iepriekš
    if (adrStartEnd[i][0] != oldAdrStartEnd[i][0] && adrStartEnd[i][1] != oldAdrStartEnd[i][1]) {
      arr[i] = arr[i - 1];
    }
  }
  arr[startIn] = valueToPut;//ievieto jauno vērtību masīvā

  if (divide) {//ja 2d vērtība, kas ievadīta 2d masīvā atradās pa vidu esošai
    arr[startIn + 1] = arr[startIn - 1];
  }

  bool breakCheck = true;//darbina un izbeidz while ciklu
  int countFreeSpaces = 0;//skaita brīvās vietas starp startIn un visu, kas atrodas masīva labajā pusē
  int startFreeSpace = 1;//skaita pēdējo atskaites punktu, šūnu, kas pēdējo reizi tika aizņemta
  while (breakCheck) {
    for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++) {
      if (arr[i] == 0) {
        countFreeSpaces++;
      } else if (countFreeSpaces > 0) {
        break;
      }
      if (i == 30 /*numLeds*/ - 1) {//ja visas vērības pēc pēdējās aizpildītās šūnas ir nulle tad funkcija beidz savu darbību
        breakCheck = false;
        break;
      }
    }
    if (breakCheck == false) {
      break;
    }
    arr[startIn + startFreeSpace] = arr[countFreeSpaces + startFreeSpace + startIn];
    arr[countFreeSpaces + startFreeSpace + startIn] = 0;

    countFreeSpaces = 0;
    startFreeSpace++;
  }

  for (int i = 0; i < 30 /*numLeds*/; i++) {
    if (adrStartEnd[i][0] == 0) {
      arr[i] = 0;
    }
  }
}

void displayAdrColors(int startEnd[2], byte colorToDisplay[4 /*colorCount*/]) { //iestata krāsas spīdēšanu kādam gabalam adresējamām diodēm
  String sendOut;
  for (int i = startEnd[0]; i <= startEnd[1]; i++) {
    sendOut = "<";
    if (i < 10) {
      sendOut += 0;
      sendOut += i;
    } else {
      sendOut += i;
    }
    for (int j = 0; j < 4 /*colorCount*/; j++) {
      if (colorToDisplay[j] < 10) {
        sendOut += "00";
        sendOut += colorToDisplay[j];
      } else if (colorToDisplay[j] < 100) {
        sendOut += 0;
        sendOut += colorToDisplay[j];
      } else {
        sendOut += colorToDisplay[j];
      }
    }
    sendOut += ">";
    Serial.println(sendOut);
  }
}

void solidFade(byte rgbArr[4 /*colorCount*/], int period, unsigned long time, int part) { //solid fade funkcija
  for (int i = 0; i < 4 /*colorCount*/; i++) { //tiek aprēķinātas 3 krāsu vērtības atbilstoši cos() funkcijai
    rgb[part][i] = (rgbArr[i] / 2) + (rgbArr[i] / 2) * cos(2 * PI / period * time);
  }
  displayAdrColors(adrStartEnd[part], rgb[part]);
}

void recvWithStartEndMarkers(String inputString) { //datu nolasīšanas funkcija
//  Serial.println("In recvWithStartEndMarkers");
  int countDataSwCase;//recvWithStartEndMarkers switch operatora skaitītājs
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char ledPartEndMarker = '#';
  char adrLedNumDivider = '-';

  char rc;//šajā mainīgajā tiek saglabāts katrs ienākošais baits


    for (int x = 0; x < inputString.length(); x++) {
//      Serial.print("LoopVal: ");Serial.println(x);
      rc = inputString[x];
          if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;//no šiem datiem tiek piešķirtas mainīgo vērtības, kas tiek iesūtītas un no saraksta pārveidotas skaitlī
        ndx++;
        switch (countDataSwCase) {
          case 1://tiek noteikts ienākošo datu tips
            dataType = atoi(receivedChars);
            ndx = 0;
            break;
          case 2://tiek noteikts kuriem led pikseļiem ir jāstrādā
            ndx = 0;
            adrStartEndUpdateNum = 0;
            
            do {
              x++;
//              if (Serial.available() > 0) {
                if (isDigit(rc)) { //ja saņemtais baits ir cipars, tad tas tiek ievietots iekš saraksta tālākai apstrādei
                  receivedChars[ndx] = rc;
                  ndx++;
                }
                rc = inputString[x];
                if (rc == adrLedNumDivider) {//ja saņemtais baits ir '-', tad tas nozīmē, ka tiek saņemti adresējamo diožu lentas dati
                  ledPartStartEnd[0] = atoi(receivedChars);
                  ndx = 0;
                } else if (rc == ledPartEndMarker) {
                  ledPartStartEnd[1] = atoi(receivedChars);
                  ndx = 0;
                  for ( int i = 0; i < 3;  ++i ) { //notīra receivedChars masīvu
                    receivedChars[i] = (char)0;
                  }
                }
//                x++;
//              
            } while (rc != ledPartEndMarker);//kamēr nav saņemts # simbols
            ndx = 0;
            break;
          case 4:
            if (dataType == 1) { //funkcijas numura iestatīšana
              funcNum = atoi(receivedChars);
              ndx = 0;
            }
            break;
          case 5:
            if (dataType == 0) { //sarkanās krāsas iestatīšana
              rgbReceive[0] = atoi(receivedChars);
              ndx = 0;
            }
            break;
          case 7:
            if (dataType == 1) { //funkcijas parametru vērtības iestatīšana
              funcPar = atoi(receivedChars);
              ndx = 0;
            }
            break;
          case 8://zaļās krāsas iestatīšana
            if (dataType == 0) { //zaļās krāsas iestatīšana
              rgbReceive[1] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          case 11://zilās krāsas iestatīšana
            if (dataType == 0) { //zaļās krāsas iestatīšana
              rgbReceive[2] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          case 14://baltās krāsas iestatīšana
            if (dataType == 0) { //zaļās krāsas iestatīšana
              rgbReceive[3] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          default:
            break;
        }
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        receivedChars[sizeof(receivedChars)] = '\0'; // terminate the string, svarīga koda rindiņa, kur iepriekš [] iekšā bija ndx. Ndx patstāvīgi mainās, tāpēc bija nepieciešams ievietot citu garuma vērtību
        recvInProgress = false;
//        newData = true;
//        Serial.println("SETNEWDATA");
        setNewData();

      }
      countDataSwCase ++;//datu sadalīšanas daļas skaitītājs
    } else if (rc == startMarker) {
      recvInProgress = true;
      countDataSwCase = 1;//reseto mainīgo no iepriekšējās vērtības
    } 
    }
  
}

void setNewData() { //saņemto datu apstrāde
    for ( int i = 0; i < 3;  ++i ) { //notīra receivedChars masīvu
      receivedChars[i] = (char)0;
    }
    updateAdrLedPart(ledPartStartEnd);//apdeito diožu daļu masīvu
    if (dataType == 0) { //ja ir iestatīta krāsa, tad atbilstošajās vietās funkcijas parametrs un funkcijas numurs tiks mainīts uz nulli
      funcNum = 1;
      funcPar = 1;
    }
//    Serial.println("a");
    setValueInArr((uint32_t*)funcNumArr, (uint32_t)funcNum);
//    Serial.println("b");
    setValueInArr((uint32_t*)oldTimeInt, 1);
//    Serial.println("c");
    setValueInArr((uint32_t*)funcParArr, (uint32_t)funcPar);
//    Serial.println("d");
    isFirstTime[startIn] = 1;//saglabā pirmo reizi, tikai tad, kad ir tas iestatīts
//    Serial.println("e");
    setValueInArr((uint32_t*)blinkOff, 1);

    if (dataType == 0) { //tā pati funkcija, kas setValueInArr, bet paredzēta darbam ar 2d masīvu. Krāsu iestatīšana atbilstošajās šūnās
      setRgbColors(rgb, rgbReceive);
      displayAdrColors(ledPartStartEnd, rgbReceive);
    } else { //ja tika iestatīta funkcijas vērtība, tad jāatbrīvo atbilstošā krāsas vienība
      for (int i = 0; i < 4 /*colorCount*/; i++) { //jo funkcijai setRgbColors nevar padot rgvReceive no iepriekšējās vērtības, vai pointeri uz rgb[startIn]
        rgbReceive[i] = rgb[startIn][i];
      }
      setRgbColors(highVal, rgbReceive);
    }
//  newData = false;
}


void solidRainbow(int part, int firstTime = 0) { //solid rainbow funkcija, part atbild par to, lai katrai daļai atbilstoši saglabātos krāsu un citas vērtības
  for (int i = 0; i < 30 /*numLeds*/; i++) {
  }
  if (firstTime) { //funkcija sākas no sākuma, jeb tiek istatītas default vērtības
    decColor[part] = 0;
    rainbowCounter[part] = 0;
    rgb[part][0] = 0;
    rgb[part][1] = 255;//zaļā krāsa ir iestatīta, jo nākamajā darbībā šī būs tā krāsa, kura būs jāfeido uz leju
    rgb[part][2] = 0;
  }
  if (rainbowCounter[part] == 0) { //ja skaitītājs sāk no sākuma
    //Šī koda daļa ir sarakstīta atbilstoši 3 krāsu feidošanas tabulai. Visu laiku viena krāsa celsies uz augšu, cita ies uz leju, cita stāvēs uz nulles. Šī koda daļa katru reizi maina to krāsu secību, kam jāmainās
    if (decColor[part] < 3) {
      decColor[part]++;
    }
    if (decColor[part] == 3) {
      decColor[part] = 0;
      incColor[part] = 1;
    }
    if (decColor[part] == 2) {
      incColor[part] = 0;
    }
    if (decColor[part] == 1) {
      incColor[part] = 2;
    }
  }

  rainbowCounter[part]++;//cikla skaitīšana

  if (rainbowCounter[part] != 0) {// nultā darbība netiek ieskaitīta lai krāsas "nepārlektu" viena uz otru
    rgb[part][decColor[part]] -= 1;
    rgb[part][incColor[part]] += 1;
  }
  displayAdrColors(adrStartEnd[part], rgb[part]);
}
void solidBlink(byte rgbArr[4 /*colorCount*/], int off, int part) {//blink funkcija
  if (off == 1) {
    for (int i = 0; i < 4 /*colorCount*/; i++) {
      rgb[part][i] = 0;
    }
  } else {
    for (int i = 0; i < 4 /*colorCount*/; i++) {
      rgb[part][i] = rgbArr[i];
    }
  }
  displayAdrColors(adrStartEnd[part], rgb[part]);
}

void funcExecute() { //iet cauri funcNum masīva vērtībām un atbilstoši izpilda katru funkciju, kas der
  for (int i = 0; i < 30 /*numLeds*/; i++) { //nepieciešams, lai dzītu uz priekšu for ciklu un tā vērtību izmantot jau kā parametru izpildāmajai funkcijai
    if (funcNumArr[i] == 0) { //izbeidz funkcijas darbību, ja funcNum masīvā tiek atrasta vērtība 0
//      Serial.println("Found 0");
      break;
    }
    if (funcNumArr[i] != 1) {
      switch (funcNumArr[i]) { //funkciju numuri sākas no 2 ieskaitot
        case 2: //izpildās solid rainbow
          if (isFirstTime[i]) { //ja funkcija notiek pirmo reizi, tad tiek iestatītas sākuma vērtības
            oldTimeInt[i] = millis();
            solidRainbow(i, 1);
            isFirstTime[i] = 0;
          } else if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            oldTimeInt[i] = millis();
            solidRainbow(i);
          }
          break;
        case 3://solid fade
          if (isFirstTime[i]) { //vienu reizi tiek saglabātas augstākās krāsu vērtības, kas arī vēlāk tiek feidotas
            for (int x = 0; x < 4 /*colorCount*/; x++) {
              highVal[i][x] = rgb[i][x];
            }
            isFirstTime[i] = 0;
          }
          if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            oldTimeInt[i] = millis();
            solidFade(highVal[i], funcParArr[i] * 100, millis(), i);
          }
          break;
        case 4://blink
          if (isFirstTime[i]) {
            for (int x = 0; x < 4 /*colorCount*/; x++) {
              highVal[i][x] = rgb[i][x];
            }
          }
          isFirstTime[i] = 0;
          if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            if (blinkOff[i] == true) {//šis globālais būls seko līdzi tam vai gaisma tiek ieslēgta vai izslēgta
              blinkOff[i] = false;
            } else {
              blinkOff[i] = true;
            }
            solidBlink(highVal[i], blinkOff[i], i);
            oldTimeInt[i] = millis();
          }
          break;
        case 5://fire
          if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            fire(i);
            oldTimeInt[i] = millis();
          }
          break;
        case 6://adr rainbow
          if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            rainbow(i);
            oldTimeInt[i] = millis();
          }
          break;
        case 7:
          if (millis() - oldTimeInt[i] >= funcParArr[i] || millis() < oldTimeInt[i]) {
            lightMusic(i);
          }
          break;
      }
    }
  }
}

void lightMusic(int part) {
  //int inRed =
  //int inGreen =
  //int inBlue =
  rgb[part][0] = map(analogRead(redIn), 80, 0, 255, 0);
  rgb[part][1] = map(analogRead(greenIn), 80, 0, 255, 0);
  rgb[part][2] = map(analogRead(blueIn), 80, 0, 255, 0);
  displayAdrColors(adrStartEnd[part], rgb[part]);
}

void rainbow(int part) {
  int startEndRainbow[2] = {adrStartEnd[part][0], adrStartEnd[part][0]};//sagatavo masīvu, ko sūtīs iestatot krāsas

  for (int i = 0; i <= adrStartEnd[part][1] - adrStartEnd[part][0]; i++) {
    rainbowWheel(((i + adrStartEnd[part][0]) * 256 / 30 /*numLeds*/) + rainbowCounter[part], part);

    startEndRainbow[0] = adrStartEnd[part][0] + i;
    startEndRainbow[1] = startEndRainbow[0];
    displayAdrColors(startEndRainbow, rgb[part]);
  }
  rainbowCounter[part] ++;
}

void rainbowWheel(byte WheelPos, int led) {
  if (WheelPos < 85) {
    rgb[led][0] = WheelPos * 3;
    rgb[led][1] = 255 - WheelPos * 3;
    rgb[led][2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    rgb[led][0] = 255 - WheelPos * 3;
    rgb[led][1] = 0;
    rgb[led][2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    rgb[led][0] = 0;
    rgb[led][1] = WheelPos * 3;
    rgb[led][2] = 255 - WheelPos * 3;
  }
}

void fire(int part) {
  int difference = adrStartEnd[part][1] - adrStartEnd[part][0] + 1;

  byte heat[difference];//30 /*numLeds*/ vietā būs starpība starp sākumu un beigām
  int cooldown;
  static int Cooling = 55;//konstantes default fire funkcijai
  static int Sparking = 120;

  // Step 1.  Cool down every cell a little
  for ( int i =  adrStartEnd[part][0]; i <= adrStartEnd[part][1]; i++) {
    cooldown = random(0, ((Cooling * 10) / difference) + 2);
    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] -= cooldown;
    }
  }

  for ( int k = difference - 1; k >= 2; k--) {// Step 2.  Heat from each cell drifts 'up' and diffuses a little
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) * 0.3;
  }

  if ( random(255) < Sparking ) {// Step 3.  Randomly ignite new 'sparks' near the bottom
    int y = random(7);
    heat[y] += random(160, 255);
  }

  for ( int j = 0; j < difference; j++) {// Step 4.  Convert heat to LED colors
    byte t192 = round((heat[j] / 255.0) * 191);// Scale 'heat' down from 0-255 to 0-191

    byte heatramp = t192 & 0x3F; // 0..63 // calculate ramp up from
    heatramp <<= 2; // scale up to 0..252// figure out which third of the spectrum we're in:

    int fireStartEnd[2] = {adrStartEnd[part][0], adrStartEnd[part][0]};
    if ( t192 > 0x80) {                    // hottest
      rgb[part][0] = 255;//saliek rgb vērtības
      rgb[part][1] = 255;
      rgb[part][2] = heatramp;
    } else if ( t192 > 0x40 ) {            // middle
      rgb[part][0] = 255;//saliek rgb vērtības
      rgb[part][1] = heatramp;
      rgb[part][2] = 0;
    } else {                               // coolest
      rgb[part][0] = heatramp;//saliek rgb vērtības
      rgb[part][1] = 0;
      rgb[part][2] = 0;
    }
    fireStartEnd[0] = adrStartEnd[part][0] + j; //saliek sākuma un beigu vērtības
    fireStartEnd[1] = fireStartEnd[0];

    displayAdrColors(fireStartEnd, rgb[part]);
  }
}


void updateAdrLedPart(int startEnd[2]) {//Jāizveido vērtību pastumšana uz kreiso pusi pēc labās masīva puses apstrādes
  divide = false;
  startIn = 0;
  for (int i = 0; i < 30 /*numLeds*/; i++) {
    for (int j = 0; j < 2; j++) {
      oldAdrStartEnd[i][j] = adrStartEnd[i][j];
    }
  }

  for (int i = 0; i < 30 /*numLeds*/; i++) { //atrod startIn vērtību
    if (adrStartEnd[i][0] >= startEnd[0]) {
      startIn = i + 1;
      break;
    } else if (adrStartEnd[i][0] < startEnd[0] && !(adrStartEnd[i + 1][0] > adrStartEnd[i][0])) {
      if (adrStartEnd[i + 1][1] == startEnd[1]) {
        startIn = i + 3;
        break;
      }
      startIn = i + 2;
      break;
    } else if (adrStartEnd[i][0] == 0) {
      startIn = i + 1;
      break;
    }
  }
  startIn--;
  //Serial.println(startIn);////////////////////////////////////////////////////////////////////////START IN///////////////////////////////
  for (int i = 30 /*numLeds*/; i >= startIn; i--) { //"pabīda" vērtības uz labo pusi
    for (int x = 0; x < 2; x++) {
      if (startEnd[0] > adrStartEnd[startIn - 1][0] && startEnd[1] < adrStartEnd[startIn - 1][1] /*&& i - startIn >= 2*/ && adrStartEnd[i - 2][1] > 0) {
        adrStartEnd[i][x] = adrStartEnd[i - 2][x];//novieto vērtību divas vērtības aiz, uz kreiso pusi
        divide = true;
      } else if (adrStartEnd[i - 1][1] > 0) {
        adrStartEnd[i][x] = adrStartEnd[i - 1][x];
      }
    }
  }

  for (int i = 0; i < 2; i++) {//Ievieto vērtības atbilstošajās daļās
    adrStartEnd[startIn][i] = startEnd[i];
  }

  if (startEnd[0] <= adrStartEnd[startIn - 1][1]) { //masīvā pirms ievadītā masīva tiek salīdzinātas vērtības un ja tā ir mazāka par ievadītā masīva sākuma vērtību, tad tā paliek par 1 mazāka
    adrStartEnd[startIn - 1][1] = startEnd[0] - 1;
  }

  if (adrStartEnd[startIn - 1][1] < adrStartEnd[startIn - 1][0]) { //ja izmaiņu rezultātā masīva beigu vērtība ir lielāka par sākuma vērtību, tad masīva vērtība kļūst par 0
    adrStartEnd[startIn - 1][0] = 0;
    adrStartEnd[startIn - 1][1] = 0;
  }

  bool breakCheck = false;//nepieciešams, lai tiktu ārā no galvenā lūpa
  for (int i = startIn + 1; i < 30 /*numLeds*/; i++) { //pārbauda cik tālu sniedzas ievadītā vērtība masīvā pa labi un maina vērtības atbilstoši tam
    for (int x = 0; x < 2; x++) {
      if (adrStartEnd[i][x] == 0) {
        breakCheck = true;
        break;
      }
      if (adrStartEnd[i][x] > startEnd[1]) {

        if (x == 0) {
          //adrStartEnd[i - 1][x + 1] = 0;/////////////////////////////////////////////////////////////////////////////////////////////
        } else {
          adrStartEnd[i][x - 1] = startEnd[1] + 1;
        }
        breakCheck = true;
        break;
      } else if (adrStartEnd[i][0] == startEnd[0] && adrStartEnd[i][1] == startEnd[1]) {
        adrStartEnd[i][x] = 0;
        adrStartEnd[i][x + 1] = 0;

      } else if (adrStartEnd[i][x] == startEnd[1]) {
        if (x == 0) {
          adrStartEnd[i][x] = adrStartEnd[i][x] + 1;
          if (adrStartEnd[i][x] > adrStartEnd[i][x + 1]) {
            adrStartEnd[i][x] = 0;
            adrStartEnd[i][x + 1] = 0;
          }
        } else {
          adrStartEnd[i][x] = 0;
          adrStartEnd[i][x - 1] = 0;
        }
        breakCheck = true;
        break;
      }
      else if (adrStartEnd[i][0] < startEnd[1] && adrStartEnd[i][1] > startEnd[1]) {
        adrStartEnd[i][x] = startEnd[1] + 1;
        breakCheck = true;
        break;
      } else {
        adrStartEnd[i][x] = 0;
      }
    }
    if (breakCheck == true) {
      breakCheck = false;
      break;
    }
  }

  breakCheck = true;//darbina un izbeidz while ciklu
  int countFreeSpaces = 0;//skaita brīvās vietas starp startIn un visu, kas atrodas masīva labajā pusē
  int startFreeSpace = 1;//skaita pēdējo atskaites punktu, šūnu, kas pēdējo reizi tika aizņemta
  while (breakCheck) {
    for (int i = startIn + startFreeSpace; i < 30 /*numLeds*/; i++) {
      if (adrStartEnd[i][0] == 0) {
        countFreeSpaces++;
      } else if (countFreeSpaces > 0) {//ja adrStartEnd[i][0]>0, tad iziet ārā no dotā for cikla
        break;
      }
      if (i == 30 /*numLeds*/ - 1) {//ja visas vērības pēc pēdējās aizpildītās šūnas ir nulle tad funkcija beidz savu darbību
        breakCheck = false;
        break;
      }
    }
    if (breakCheck == false) {
      break;
    }
    for (int i = 0; i < 2; i++) {
      adrStartEnd[startIn + startFreeSpace][i] = adrStartEnd[countFreeSpaces + startFreeSpace + startIn][i];
      adrStartEnd[countFreeSpaces + startFreeSpace + startIn][i] = 0;
    }
    countFreeSpaces = 0;
    startFreeSpace++;
  }

  /*Serial.println("Final: ");
    Serial.print('{');
    for (int i = 0; i <= 2 ; i++) {
    for (int j = 0; j < 2; j++) {
      if (j == 0) {
        Serial.print('{');
        Serial.print(adrStartEnd[i][j]);
        Serial.print(',');
      } else {
        Serial.print(adrStartEnd[i][j]);
        Serial.print('}');
      }

    }
    }
    Serial.println('}');*/
}

/*
  Jāpievieno gaismas mūzika

  Adr funkcijas, kas vēl jāpievieno:
  cylon
*/
