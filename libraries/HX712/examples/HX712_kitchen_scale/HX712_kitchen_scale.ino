//
//    FILE: HX712_kitchen_scale.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX712 demo
//     URL: https://github.com/RobTillaart/HX712


#include "HX712.h"

HX712 scale;

//  adjust pins if needed
//  uint8_t dataPin = 6;
//  uint8_t clockPin = 7;
uint8_t dataPin  = 19;  //  for ESP32
uint8_t clockPin = 18;  //  for ESP32

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX712_LIB_VERSION: ");
  Serial.println(HX712_LIB_VERSION);
  Serial.println();

  scale.begin(dataPin, clockPin);

  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  Serial.println("\nEmpty the scale, press a key to continue");
  while(!Serial.available());
  while(Serial.available()) Serial.read();

  scale.tare();
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));


  Serial.println("\nPut 1000 gram in the scale, press a key to continue");
  while(!Serial.available());
  while(Serial.available()) Serial.read();

  scale.calibrate_scale(1000, 5);
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));

  Serial.println("\nScale is calibrated, press a key to continue");
  //  Serial.println(scale.get_scale());
  //  Serial.println(scale.get_offset());
  while(!Serial.available());
  while(Serial.available()) Serial.read();
}


void loop()
{
  Serial.print("UNITS: ");
  Serial.println(scale.get_units(10));
  delay(250);
}


//  -- END OF FILE --
