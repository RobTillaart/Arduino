//
//    FILE: AD56X8_wave.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD56X8


#include "AD56X8.h"


AD56X8 AD16_SW(9, 10, 11);  //  SW SPI

uint32_t start, stop;

int value = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD56X8_LIB_VERSION: ");
  Serial.println(AD56X8_LIB_VERSION);

  AD16_SW.begin();

  value = AD16_SW.getValue(0);
}


void loop()
{
  AD16_SW.setValue(0, value);
  value++;
  if (value == 4096) value = 0;
  delay(10);
}


//  -- END OF FILE --
