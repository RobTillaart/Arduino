//
//    FILE: AD5144A_low_level.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test low level IO
//     URL: https://github.com/RobTillaart/AD5144A

//  THIS IS A LOW LEVEL WRITE TEST FOR AD5144A
//  IT DOES NOT USE THE LIBRARY
//  IT USES Wire I2C bus


#include "Arduino.h"
#include "Wire.h"

#define ADDRESS    0x77


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  Serial.print("CONNECT:\t");
  Wire.beginTransmission(ADDRESS);
  int rv = Wire.endTransmission();
  Serial.println(rv);

  Serial.println("LOOP 0..255 POTMETER 0");
  for (int val = 0; val < 256; val++)
  {
    Wire.beginTransmission(ADDRESS);
    Wire.write(0x11);
    Wire.write(val);
    int x = Wire.endTransmission();
    Serial.print(val);
    Serial.print("\t");
    Serial.println(x);
    delay(10);
  }

  Serial.println("LOOP 0..255 POTMETER 1");
  for (int val = 0; val < 256; val++)
  {
    Wire.beginTransmission(ADDRESS);
    Wire.write(0x12);
    Wire.write(val);
    int x = Wire.endTransmission();
    Serial.print(val);
    Serial.print("\t");
    Serial.println(x);
    delay(10);
  }

  Serial.println("LOOP 0..255 POTMETER 2");
  for (int val = 0; val < 256; val++)
  {
    Wire.beginTransmission(ADDRESS);
    Wire.write(0x14);
    Wire.write(val);
    int x = Wire.endTransmission();
    Serial.print(val);
    Serial.print("\t");
    Serial.println(x);
    delay(10);
  }

  Serial.println("LOOP 0..255 POTMETER 3");
  for (int val = 0; val < 256; val++)
  {
    Wire.beginTransmission(ADDRESS);
    Wire.write(0x18);
    Wire.write(val);
    int x = Wire.endTransmission();
    Serial.print(val);
    Serial.print("\t");
    Serial.println(x);
    delay(10);
  }

  Serial.println();
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
