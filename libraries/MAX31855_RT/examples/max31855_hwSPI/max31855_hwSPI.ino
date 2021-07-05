//
//    FILE: max31855_hw_SPI.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: thermocouple lib demo application
//    DATE: 2020-08-30
//     URL: https://github.com/RobTillaart/MAX31855_RT
//


#include "MAX31855.h"


// read()            timing UNO   timing ESP32 |
// HWSPI  16000000   ~68  us      ~16 us
// HWSPI   4000000   ~72  us      ~23 us
// HWSPI   1000000   ~100 us      ~51 us
// HWSPI    500000   ~128 us      ~89 us
// SWSPI  bitbang    ~500 us      ~


//
// | HW SPI   |  UNO  |  ESP32  |
// |:---------|:-----:|:-------:|
// | CLOCKPIN |   13  |   18    |
// | MISO     |   12  |   19    |
// | MOSI     |   11  |   23    |  * not used...


const int csPin   = 25;
const int clkPin  = 18;
const int dataPin = 19;

uint32_t start, stop;


MAX31855 tc(csPin);
// MAX31855 tc(clkPin, csPin, dataPin);  // sw SPI


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("Start max31855_demo0: ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  tc.begin();
}


void loop()
{
  start = micros();
  int status = tc.read();
  stop = micros();

  Serial.println();
  Serial.print("time:\t\t");
  Serial.println(stop - start);

  Serial.print("stat:\t\t");
  Serial.println(status);

  uint32_t raw = tc.getRawData();
  Serial.print("raw:\t\t");
  uint32_t mask = 0x80000000;
  for (int i = 0; i < 32; i++)
  {
    if ((i > 0)  && (i % 4 == 0)) Serial.print(" ");
    Serial.print((raw & mask) ? 1 : 0);
    mask >>= 1;
  }
  Serial.println();

  float internal = tc.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = tc.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 3);
  delay(1000);
}


// -- END OF FILE --
