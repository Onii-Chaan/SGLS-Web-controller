#include "funcHeader.h"

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
  int startEndRainbow[2] = {adrStartEnd[part][0], adrStartEnd[part][0]};//sagatavo masivu, ko sutis iestatot krasas

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

  byte heat[difference];//30 /*numLeds*/ vieta bus starpiba starp sakumu un beigam
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
      rgb[part][0] = 255;//saliek rgb vertibas
      rgb[part][1] = 255;
      rgb[part][2] = heatramp;
    } else if ( t192 > 0x40 ) {            // middle
      rgb[part][0] = 255;//saliek rgb vertibas
      rgb[part][1] = heatramp;
      rgb[part][2] = 0;
    } else {                               // coolest
      rgb[part][0] = heatramp;//saliek rgb vertibas
      rgb[part][1] = 0;
      rgb[part][2] = 0;
    }
    fireStartEnd[0] = adrStartEnd[part][0] + j; //saliek sakuma un beigu vertibas
    fireStartEnd[1] = fireStartEnd[0];

    displayAdrColors(fireStartEnd, rgb[part]);
  }
}

void solidRainbow(int part, int firstTime) { //solid rainbow funkcija, part atbild par to, lai katrai dalai atbilstosi saglabatos krasu un citas vertibas
  // for (int i = 0; i < 30 /*numLeds*/; i++) {
  // }
  if (firstTime) { //funkcija sakas no sakuma, jeb tiek istatitas default vertibas
    decColor[part] = 0;
    rainbowCounter[part] = 0;
    rgb[part][0] = 0;
    rgb[part][1] = 255;//zala krasa ir iestatita, jo nakamaja darbiba si bus ta krasa, kura bus jafeido uz leju
    rgb[part][2] = 0;
  }
  if (rainbowCounter[part] == 0) { //ja skaititajs sak no sakuma
    //si koda dala ir sarakstita atbilstosi 3 krasu feidosanas tabulai. Visu laiku viena krasa celsies uz augsu, cita ies uz leju, cita staves uz nulles. si koda dala katru reizi maina to krasu secibu, kam jamainas
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

  rainbowCounter[part]++;//cikla skaitisana

  if (rainbowCounter[part] != 0) {// nulta darbiba netiek ieskaitita lai krasas "neparlektu" viena uz otru
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

void solidFade(byte rgbArr[4 /*colorCount*/], int period, unsigned long time, int part) { //solid fade funkcija
  for (int i = 0; i < 4 /*colorCount*/; i++) { //tiek aprekinatas 3 krasu vertibas atbilstosi cos() funkcijai
    rgb[part][i] = (rgbArr[i] / 2) + (rgbArr[i] / 2) * cos(2 * PI / period * time);
  }
  displayAdrColors(adrStartEnd[part], rgb[part]);
}




