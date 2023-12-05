//
//    FILE: M5ROTATE8_led_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/M5ROTATE8


#include "m5rotate8.h"


M5ROTATE8 MM;

uint8_t R = 0, G = 0, B = 0;  //  colors
uint16_t D = 0;               //  delay


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("M5ROTATE8_LIB_VERSION: ");
  Serial.println(M5ROTATE8_LIB_VERSION);
  delay(100);

  Wire.begin();
  MM.begin();
}


void loop()
{
  for (int ch = 0; ch < 9; ch++)
  {
    D = 1 + (abs(MM.getAbsCounter(0)) & 0xFF);
    R = MM.getAbsCounter(1) & 0x7F;
    G = MM.getAbsCounter(2) & 0x7F;
    B = MM.getAbsCounter(3) & 0x7F;

    Serial.print(ch);
    Serial.print('\t');
    Serial.print(R);
    Serial.print('\t');
    Serial.print(G);
    Serial.print('\t');
    Serial.print(B);
    Serial.print('\t');
    Serial.println(D);

    MM.writeRGB(ch, R, G, B);
    delay(D);
    MM.writeRGB(ch, 0, 0, 0);
    delay(D);
  }
}


//  -- END OF FILE --
