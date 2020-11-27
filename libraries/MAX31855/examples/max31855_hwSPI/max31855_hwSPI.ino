//
//    FILE: max31855_hw_SPI.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: thermocouple lib demo application
//    DATE: 2020-08-30
//     URL: https://github.com/RobTillaart/MAX31855_RT
//

#include "MAX31855.h"

//
// | HW SPI   |  UNO  |  ESP32  |
// |:---------|:-----:|:-------:|
// | CLOCKPIN |   13  |   18    |
// | MISO     |   12  |   19    |
// | MOSI     |   11  |   23    |

// read()            timing UNO 
// HWSPI  16000000   ~68  us
// HWSPI   4000000   ~72  us
// HWSPI   1000000   ~100 us
// HWSPI    500000   ~128 us
// SWSPI  bitbang    ~500 us

const int csPin = 6;

uint32_t start, stop;

MAX31855 tc(csPin);
// MAX31855 tc(13, 6, 12);  // sw SPI

void setup()
{
  Serial.begin(115200);
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
  Serial.println(raw, BIN);

  float internal = tc.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal);

  float temp = tc.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp);
  delay(1000);
}
