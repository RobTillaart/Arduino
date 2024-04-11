//
//    FILE: MAX6675_test_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MAX6675


#include "MAX6675.h"


const int dataPin   = 7;
const int clockPin  = 6;
const int selectPin = 5;


MAX6675 thermoCouple(selectPin, dataPin, clockPin);

uint32_t start, stop;

float temp = 0;


void setup()
{
  Serial.begin(115200);
  //  Serial.println(__FILE__);
  //  Serial.print("MAX6675_LIB_VERSION: ");
  //  Serial.println(MAX6675_LIB_VERSION);
  //  Serial.println();
  delay(250);

  SPI.begin();

  thermoCouple.begin();

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
  //  temp = newValue;

  Serial.print(status);
  Serial.print("\t");
  Serial.print(temp);
  //  Serial.print("\t");
  //  Serial.print(stop - start);
  Serial.println();

  delay(100);
}


//  -- END OF FILE --
