//
//    FILE: MATRIX7219_clock.ino
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

uint8_t hr = 9;
uint8_t mi = 58;
uint8_t sc = 00;

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MATRIX7219_LIB_VERSION: ");
  Serial.println(MATRIX7219_LIB_VERSION);
  Serial.println();

  mx.begin();
  mx.clear();
  mx.setBrightness(3);
  mx.setSwap(true);
}


void loop()
{
  //  "simple" binary clock
  if (millis() - lastTime >= 1000)
  {
    lastTime = millis();
    sc++;
    if (sc == 60)
    {
      sc = 0;
      mi++;
    }
    if (mi == 60)
    {
      mi = 0;
      hr++;
    }
    if (hr == 24)
    {
      hr = 0;
    }

    mx.setRow(1, hr  / 10, 1);
    mx.setRow(2, hr  % 10, 1);
    mx.setRow(4, mi  / 10, 1);
    mx.setRow(5, mi  % 10, 1);
    mx.setRow(7, sc  / 10, 1);
    mx.setRow(8, sc  % 10, 1);

    Serial.print(hr / 10);
    Serial.print(hr % 10);
    Serial.print(":");
    Serial.print(mi / 10);
    Serial.print(mi % 10);
    Serial.print(":");
    Serial.print(sc / 10);
    Serial.print(sc % 10);
    Serial.println();
  }
}


//  -- END OF FILE --
