//
//    FILE: set2continuous.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: Reset HMC6352 to continuous mode
//
// HISTORY:
// 0.1.0  - 2011-04-12 initial version
// 0.1.1  - 2017-09-13 renamed to .ino; fix wire.receive
//
// Released to the public domain
//
// All disclaimers apply use at own risk
//

#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define WIRE_WRITE Wire.write
#define WIRE_READ  Wire.read
#else
#define WIRE_WRITE Wire.send
#define WIRE_READ  Wire.receive
#endif

int HMC = 0x21;
int ledPin = 13;
boolean ledState = LOW;
byte value;
int x;

void setup()
{
  Serial.begin(9600);
  Serial.print("HMC6352 : start - ");
  Serial.println(HMC, HEX);

  pinMode(ledPin, OUTPUT);

  Wire.begin();
  delay(1000); // give all things time to start
}

void loop()
{
  // flashing means not blocking
  ledState = !ledState;
  digitalWrite(ledPin, ledState);

  // write continuous mode to RAM 0x74 and do an L command immediately after it
  // pull out 5 volt if it reads back 0x72
  Wire.beginTransmission(HMC);
  WIRE_WRITE('G');
  WIRE_WRITE(0x74);
  WIRE_WRITE(0x72);   // 20 Hz | Reset = True | CONT
  WIRE_WRITE('L');
  // WIRE_WRITE('O');  optional reset
  x = Wire.endTransmission();
  delay(10);

  // Read the EEPROM value for feedback as this is the next startup value
  Wire.beginTransmission(HMC);
  WIRE_WRITE('r');
  WIRE_WRITE(0x07);
  x = Wire.endTransmission();
  delay(10);

  int cnt = Wire.requestFrom(HMC, 1);
  if (cnt == 1)
  {
    value = WIRE_READ();
    Serial.print("Current Mode: ");
    Serial.println((int)value, BIN);
  }
  else
  {
    Serial.println("Error...");
  }
}

// END OF FILE
