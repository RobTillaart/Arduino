//
//    FILE: set2continuous.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Reset HMC6352 to continuous mode without library
//     URL: https://github.com/RobTillaart/HMC6352


#include "hmc6352.h"

int HMC = 0x21;
int ledPin = 13;
boolean ledState = LOW;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HMC6352_LIB_VERSION: ");
  Serial.println(HMC6352_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.print("HMC6352 : start - ");
  Serial.println(HMC, HEX);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  delay(1000);  //  give all things time to start
}


void loop()
{
  //  flashing means not blocking
  ledState = !ledState;
  digitalWrite(ledPin, ledState);

  //  write continuous mode to RAM 0x74 and do an L command immediately after it
  //  pull out 5 volt if it reads back 0x72
  Wire.beginTransmission(HMC);
  Wire.write('G');
  Wire.write(0x74);
  Wire.write(0x72);   //  20 Hz | Reset = True | CONT
  Wire.write('L');
  //  Wire.write('O');  optional reset
  Wire.endTransmission();
  delay(10);

  //  Read the EEPROM value for feedback as this is the next startup value
  Wire.beginTransmission(HMC);
  Wire.write('r');
  Wire.write(0x07);
  Wire.endTransmission();
  delay(10);

  int cnt = Wire.requestFrom(HMC, 1);
  if (cnt == 1)
  {
    Serial.print("Current Mode: ");
    Serial.println((int)Wire.read(), BIN);
  }
  else
  {
    Serial.print("Error... : ");
    Serial.println(cnt);
  }
}


//  -- END OF FILE --

