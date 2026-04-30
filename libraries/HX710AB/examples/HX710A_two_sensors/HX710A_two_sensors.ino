//    FILE: HX710A_two_sensors.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

uint8_t dataPin1  = 6;
uint8_t clockPin1 = 7;
uint8_t dataPin2  = 8;
uint8_t clockPin2 = 9;


HX710A HX1(dataPin1, clockPin1);
HX710A HX2(dataPin2, clockPin2);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();

  HX1.begin();
  HX2.begin();

  Serial.println("End setup()");
  delay(100);
}

void loop()
{
  int32_t value1 = HX1.read(false);
  int32_t value2 = HX2.read(false);
  Serial.print(value1);
  Serial.print("\t");
  Serial.print(value2);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
