//
//    FILE: AMT25_SW_SPI_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurements
//     URL: https://github.com/RobTillaart/AMT25
//

#include "AMT25.h"

//  adjust pins if needed
//  select, dataIn, dataOut, clock
AMT25 re(4, 5, 6, 7);  //  software SPI, bit bang.

uint32_t start, stop;
volatile uint16_t value;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AMT25_LIB_VERSION: ");
  Serial.println(AMT25_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin(14);
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
