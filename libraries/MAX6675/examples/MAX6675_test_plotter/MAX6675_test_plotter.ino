//
//    FILE: MAX6675_test_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-04-20
//     URL: https://github.com/RobTillaart/MAX6675


#include "MAX6675.h"

// note: pins are slightly different than other examples!
const int dataPin   = 7;
const int clockPin  = 6;
const int selectPin = 5;


MAX6675 thermoCouple;

uint32_t start, stop;

float temp = 0;

void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.println(MAX6675_LIB_VERSION);
  //  Serial.println();

  // thermoCouple.begin(clockPin, selectPin, dataPin);
  thermoCouple.begin(selectPin);  // HW SPI

  thermoCouple.setSPIspeed(4000000);
  thermoCouple.setOffset(273);

  int status = thermoCouple.read();
  if (status != 0) Serial.println(status);
  temp = thermoCouple.getTemperature();
}


void loop()
{
  delay(100);
  start = micros();
  int status = thermoCouple.read();
  stop = micros();

  float newValue = thermoCouple.getTemperature();
  //  0.2 is low pass filter
  temp += 0.2 * (newValue - temp);
  // temp = newValue;

  Serial.print(status);
  Serial.print("\t");
  Serial.print(temp);
  //  Serial.print("\t");
  //  Serial.print(stop - start);
  Serial.println();

  delay(100);
}


// -- END OF FILE --
