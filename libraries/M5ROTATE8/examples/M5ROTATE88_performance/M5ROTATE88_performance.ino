//
//    FILE: M5ROTATE8_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: meansurement performance
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;

uint32_t start, stop;
uint16_t x;

void setup()
{
  Serial.begin(115200);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
 
  start = micros();
  for (int ch = 0; ch < 8; ch++)
  {
    MM.writeRGB(ch, 128, 128, 128);
  }
  stop = micros();
  Serial.print("writeRGB:\t");
  Serial.println((stop - start) / 8.0);
  delay(100);

  start = micros();
  MM.allOff();
  stop = micros();
  Serial.print("allOff:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = MM.inputSwitch();
  stop = micros();
  Serial.print("inputSwitch:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = MM.getAbsCounter(3);
  stop = micros();
  Serial.print("getAbsCounter:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = MM.getRelCounter(5);
  stop = micros();
  Serial.print("getRelCounter:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = MM.getKeyPressed(7);
  stop = micros();
  Serial.print("getKeyPressed:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  MM.setAbsCounter(1, 1000);
  stop = micros();
  Serial.print("setAbsCounter:\t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  x = MM.resetCounter(1);
  stop = micros();
  Serial.print("resetCounter:\t");
  Serial.println(stop - start);
  delay(100);
  
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
