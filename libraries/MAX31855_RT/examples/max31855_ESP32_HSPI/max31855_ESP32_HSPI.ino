//
//    FILE: max31855_ESP32_HSPI.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: thermocouple lib demo application
//    DATE: 2021-08-11
//     URL: https://github.com/RobTillaart/MAX31855_RT
//

// NOTE:
// one might to need to disconnect pin 12 during upload of the code
// when HSPI is used.


#include "MAX31855.h"


// read()            timing UNO   timing ESP32 |
//---------------------------------------------
// HWSPI  16000000   ~68  us      ~16 us
// HWSPI   4000000   ~72  us      ~23 us
// HWSPI   1000000   ~100 us      ~51 us
// HWSPI    500000   ~128 us      ~89 us
// SWSPI  bitbang    ~500 us      ~17 us


// | HW SPI   |  UNO  |  ESP32  |  ESP32  |
// |          |       |  VSPI   |  HSPI   |
// |:---------|:-----:|:-------:|:-------:|
// | CLOCKPIN |   13  |   18    |   14    |
// | MISO     |   12  |   19    |   12    |
// | MOSI     |   11  |   23    |   13    |  * not used...
// | SELECT   | eg. 4 |    5    |   15    |  * can be others too.

const int selectPin = 15;
const int dataPin   = 12;
const int clockPin  = 14;

SPIClass * myspi = new SPIClass(HSPI);
MAX31855 thermoCouple(selectPin, myspi);
//  MAX31855 thermoCouple(selectPin, dataPin, clockPin);  //  SW SPI to test

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX31855_VERSION : ");
  Serial.println(MAX31855_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();

  thermoCouple.begin();
  thermoCouple.setSPIspeed(1000000);
}


void loop()
{
  start = micros();
  int status = thermoCouple.read();
  stop = micros();

  Serial.println();
  Serial.print("time:\t\t");
  Serial.println(stop - start);

  Serial.print("stat:\t\t");
  Serial.println(status);

  uint32_t raw = thermoCouple.getRawData();
  Serial.print("raw:\t\t");
  uint32_t mask = 0x80000000;
  for (int i = 0; i < 32; i++)
  {
    if ((i > 0)  && (i % 4 == 0)) Serial.print(" ");
    Serial.print((raw & mask) ? 1 : 0);
    mask >>= 1;
  }
  Serial.println();

  float internal = thermoCouple.getInternal();
  Serial.print("internal:\t");
  Serial.println(internal, 3);

  float temp = thermoCouple.getTemperature();
  Serial.print("temperature:\t");
  Serial.println(temp, 3);
  delay(1000);
}


//  -- END OF FILE --
