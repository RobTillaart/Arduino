// 
//    FILE: set2continuous.pde
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: Reset HMC6352 to continuous mode 
//
// HISTORY: 
// 0.1.00 - 2011-04-12 initial version
// 
// Released to the public domain
//
// All disclaimers apply use at own risk
//

#include <Wire.h>

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
  Wire.send('G');
  Wire.send(0x74);
  Wire.send(0x72);   // 20 Hz | Reset = True | CONT
  Wire.send('L');
  // Wire.send('O');  optional reset  
  x = Wire.endTransmission();
  delay(10);
  
  // Read the EEPROM value for feedback as this is the next startup value
  Wire.beginTransmission(HMC);
  Wire.send('r');
  Wire.send(0x07);
  x = Wire.endTransmission();
  delay(10);
  
  Wire.requestFrom(HMC, 1);      
  while(Wire.available()  < 1);
  value = Wire.receive();
  Serial.print("Current Mode: ");
  Serial.println((int)value, BIN);     
} 



