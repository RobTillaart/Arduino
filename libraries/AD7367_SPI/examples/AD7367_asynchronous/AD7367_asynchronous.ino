//
//    FILE: AD7367_asynchronous.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test asynchronous behaviour
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367_SPI.h"

//  select, convert, busy, SPI (optional)
//  adjust pins if needed
AD7367_SPI AD(5, 6, 7);

uint32_t count = 0;  //  simulate other task.


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7367_SPI_LIB_VERSION: ");
  Serial.println(AD7367_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  AD.begin();

  delay(100);
}


void loop()
{
  AD.triggerConversion();
  if (AD.conversionReady())
  {
    AD.readAsync();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(AD.getLastADCA());
    Serial.print("\t");
    Serial.print(AD.getLastADCB());
    Serial.print("\t");
    Serial.println(count);
    count = 0;
  }

  //  other async tasks here
  count = count + 1;
}


//  -- END OF FILE --
