//
//    FILE: DAC8552_sw_spi_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DAC8552 performance with software SPI
//     URL: https://github.com/RobTillaart/DAC8552
//
//  measurements full speed sawtooth
//            UNO               ESP32
//            us   KHz          us   KHz
// --------------------------------------------
//   SWSPI    328   3.048       10   100.000
//   HWSPI     22  45.000       11    90.000


#include "DAC8552.h"


DAC8552 mydac(12, 13, 14);   //  SW SPI
//  DAC8552 mydac(10);   //  HW SPI

uint16_t value = 0;
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC8552_LIB_VERSION: ");
  Serial.println(DAC8552_LIB_VERSION);

  SPI.begin();

  mydac.begin();
}


void loop()
{
  //  simulate fast sawtooth;
  start = micros();
  mydac.setValue(0, value);
  stop = micros();
  value++;
  Serial.println(stop - start);
  delay(500);
}


//  -- END OF FILE --

