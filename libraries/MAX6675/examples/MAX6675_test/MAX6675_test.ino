//
//    FILE: MAX6675_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-01-12
//     URL: https://github.com/RobTillaart/MAX6675


#include "MAX6675.h"

// note: pins are slightly different than other examples!
const int dataPin   = 7;
const int clockPin  = 6;
const int selectPin = 5;


MAX6675 thermoCouple;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(MAX6675_LIB_VERSION);
  Serial.println();

  thermoCouple.begin(clockPin, selectPin, dataPin);
  // thermoCouple.begin(selectPin);  // HW SPI

  thermoCouple.setSPIspeed(4000000);
}


void loop()
{
  delay(100);
  start = micros();
  int status = thermoCouple.read();
  stop = micros();
  float temp = thermoCouple.getTemperature();

  Serial.print(millis());
  Serial.print("\tstatus: ");
  Serial.print(status);
  Serial.print("\ttemp: ");
  Serial.print(temp);
  Serial.print("\tus: ");
  Serial.println(stop - start);

  delay(1000);
}


// -- END OF FILE --
