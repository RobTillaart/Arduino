//
//    FILE: ERCFS_HW_SPI_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurements
//     URL: https://github.com/RobTillaart/ERCFS
//

#include "ERCFS.h"

ERCFS re(9);  //  hardware SPI

uint32_t start, stop;
volatile uint16_t value;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ERCFS_LIB_VERSION: ");
  Serial.println(ERCFS_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    value = re.getRawValue();
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);

  Serial.println("\nDone...");
}


void loop()
{

}



//  -- END OF FILE --
