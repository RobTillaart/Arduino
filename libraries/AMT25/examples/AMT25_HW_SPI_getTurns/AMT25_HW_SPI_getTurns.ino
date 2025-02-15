//
//    FILE: AMT25_HW_SPI_getTurns.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurements
//     URL: https://github.com/RobTillaart/AMT25
//

#include "AMT25.h"

AMT25 re(9);  //  hardware SPI, CS = 9 adjust if needed.

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
    value = re.getTurns();
  }
  stop = micros();
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  Serial.print("TURNS:\t");
  Serial.println(value);

  Serial.println("\nDone...");
}


void loop()
{

}


//  -- END OF FILE --
