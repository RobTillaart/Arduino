//
//    FILE: AD7367_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367_SPI.h"

//  select, convert, busy, SPI (optional)
//  adjust pins if needed
AD7367_SPI AD(5, 6, 7);

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
  Serial.print("TYPE:\t");
  Serial.println(AD.getType());
  Serial.print("BITS:\t");
  Serial.println(AD.getBits());

  delay(100);
}


void loop()
{
  uint32_t start = micros();
  for (int i = 0; i < 1000; i++) AD.read();
  uint32_t duration = micros() - start;
  Serial.print(duration);
  Serial.print("\t");
  Serial.println(1e9 / duration);
  Serial.println(AD.getLastADCA());
  Serial.println(AD.getLastADCB());
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
