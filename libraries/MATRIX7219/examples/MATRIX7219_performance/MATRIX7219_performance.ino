//
//    FILE: MATRIX7219_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of MATRIX7219 8x8 LED MATRIX MAX7219
//     URL: https://github.com/RobTillaart/MATRIX7219


#include "MATRIX7219.h"

//uint8_t dataPin   = 2;
//uint8_t selectPin = 3;
//uint8_t clockPin  = 4;
//uint8_t count     = 1;

//  ESP32
uint8_t dataPin   = 21;
uint8_t selectPin = 22;
uint8_t clockPin  = 23;
uint8_t count     = 1;

MATRIX7219 mx(dataPin, selectPin, clockPin, count);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();
  delay(1000);

  start = micros();
  mx.begin();
  stop = micros();
  Serial.print("BEGIN:\t");
  Serial.println(stop - start);
  delay(1000);

  start = micros();
  mx.clear();
  stop = micros();
  Serial.print("CLEAR:\t");
  Serial.println(stop - start);
  delay(1000);

  start = micros();
  uint8_t n = mx.getMatrixCount();
  stop = micros();
  Serial.print("COUNT:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(n);
  delay(1000);

  start = micros();
  mx.setRow(1, 255, 1);
  stop = micros();
  Serial.print("  255:\t");
  Serial.println(stop - start);
  delay(1000);

  start = micros();
  mx.setRow(1, 0, 1);
  stop = micros();
  Serial.print("  000:\t");
  Serial.println(stop - start);
  delay(1000);

  start = micros();
  mx.setBrightness(3);
  stop = micros();
  Serial.print("BRIGHT:\t");
  Serial.println(stop - start);
  delay(1000);
}


void loop()
{
  for (int n = 1; n < 9; n++)
  {
    mx.setRow(n, 1 << random(8), 1);
    delay(10);
  }
}


//  -- END OF FILE --