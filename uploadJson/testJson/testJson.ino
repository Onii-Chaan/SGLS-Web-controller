#include <Arduino.h>
#include <Formicarium.h>
#include <ButtonInput.h>
#include <Animations.h>

const byte redPin = 3;
const byte greenPin = 5;
const byte bluePin = 6;

const int outLedPin = 9;
const int ventPin = 10;

const byte topButtonPin = 7;
const byte botButtonPin = 8;
const byte potPin = 19;
const byte switchPin = 2;

byte rgb[5];

// AntVent antVent(ventPin, "Ant Vent", 0);
// AntLed antLed(outLedPin, "Ant LED", 1);

// Input input(topButtonPin, botButtonPin, potPin, switchPin, 150);
Animation * animation[2];

// SolidRainbow solidRainbow(3);

void setup()
{
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  animation[0] = new SolidFade(3);
  animation[0]->firstTime(rgb);
}

void loop()
{
  animation[0]->execute(rgb);
  analogWrite(3, rgb[0]);
  analogWrite(5, rgb[1]);
  analogWrite(6, rgb[2]);
}
