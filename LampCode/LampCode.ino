#define whitePin 3
#define bluePin 9
#define greenPin 5
#define redPin 6
/*
  GREEN PCB LAMPS:
  3 - white
  5 - blue
  6 - green
  9 - red

  WHITE PCB LAMPS:
  3 - white
  6 - red
  9 - blue
  5 - green
*/
//boolean newData = false; //datu saņemšanas funkcijas apstiprinājums par to vai ienāk jauni dati
bool lampCounting;
const byte numChars = 32;

char receivedChars[numChars]; //šajā sarakstā tiek saglabāti ienākošie dati

int currentLamp; //vienas lampas numurs, kas tiek sūtīta tālāk
int numLed;//esošās lampas numurs
int countDataSwCase;//skaitītājs priekš switch operatora iekš recvWitStartEndMarkers funkcijas

byte rgbw[4];

int dataType;

char * sendOut = "";

void setup() {
  Serial.begin(115200);//19200 pagaidām ir augstākais strādājošais baud rate
  pinMode(whitePin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  digitalWrite(whitePin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  Serial.println("Lamp started");
}


void loop() {
  recvWithStartEndMarkers(); //funkcija kas saņem datus no seriāļa
  //  setNewData(); //funkcija kas nolasa datus no seriāļa
  

}

void lightOn() { //iededzina lampu
  analogWrite(whitePin, rgbw[3]);
  analogWrite(bluePin, rgbw[2]);
  analogWrite(greenPin, rgbw[1]);
  analogWrite(redPin, rgbw[0]);
}

int incDataCount = 0;
void recvWithStartEndMarkers() { //datu nolasīšanas funkcija
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;//šajā sarakstā tiek saglabāti ienākošie dati
  char buffer[24];
  while (Serial.available() > 0) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;//no šiem datiem tiek piešķirtas mainīgo vērtības, kas tiek iesūtītas
        ndx++;
        
        if (rc >= 48 && rc <= 57 || rc == 60 || rc == 62) { //so no corrputed chars are sent
          sprintf(buffer, "%s%c", sendOut, rc);
          sendOut = buffer;
          incDataCount++;
        }


        switch (countDataSwCase) {
          case 2:
            if (numLed > 0) {
              currentLamp = atoi(receivedChars);
            } else {
              lampCounting = true;
              numLed = atoi(receivedChars) + 1;
            }
            ndx = 0;
            break;
          case 5:
            if (currentLamp == numLed && currentLamp != 0) {
              rgbw[0] = atoi(receivedChars);

            }
            ndx = 0;
            break;
          case 8:
            if (currentLamp == numLed && currentLamp != 0) {
              rgbw[1] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          case 11:
            if (currentLamp == numLed && currentLamp != 0) {
              rgbw[2] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          case 14:
            if (currentLamp == numLed && currentLamp != 0) {
              rgbw[3] = atoi(receivedChars);
            }
            ndx = 0;
            break;
          default:
            break;
        }
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        setNewData();
        lightOn();
      }
      countDataSwCase ++;//datu sadalīšanas koda skaitītājs
    } else if (rc == startMarker) {
      recvInProgress = true;
      countDataSwCase = 0;//reseto mainīgo no iepriekšējās vērtības
      countDataSwCase++;
    }
  }
}

void setNewData() {
  Serial.print("SerAvAf: ");Serial.println(Serial.available());
  for ( int i = 0; i < 32;  ++i ) { //notīra receivedChars masīvu
    receivedChars[i] = (char)0;
  }
  if (currentLamp != numLed && currentLamp != 0) {
    char buffer[24];
    sprintf(buffer, "%c%s%c", '<', sendOut, '>');
    sendOut = buffer;
    Serial.print("CDSWC: ");Serial.println(incDataCount);
    incDataCount = 0;
    if (strlen(sendOut) == 16) {//so corrput strings won't be sent
      Serial.println(sendOut);
    }
  } else if (currentLamp == 0 && lampCounting) {
    lampCounting = false;
    sendOut = "<";
    if (numLed >= 10) {
      sprintf(sendOut, "%s%d", sendOut, numLed);
    } else if (numLed < 10) {
      sprintf(sendOut, "%s%d", sendOut, 0);
      sprintf(sendOut, "%s%i", sendOut, numLed);
    }
    sprintf(sendOut, "%s%c", sendOut, '>');
    Serial.println(sendOut);


  }
  currentLamp = 0;
  sendOut = "";
  Serial.print("SerAvBef: ");Serial.println(Serial.available());
  //    newData = false;//šim jāatrodās pašās beigās

}
