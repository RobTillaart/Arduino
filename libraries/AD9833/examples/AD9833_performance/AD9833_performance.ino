//
//    FILE: AD9833_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AD9833 wave form generator
//     URL: https://github.com/RobTillaart/AD9833


#include "AD9833.h"


//  ESP32
//  SPIClass * myspi = new SPIClass(VSPI);
//  AD9833 AD(5, myspi);
//  AD9833 AD(15, 13, 14);  //  SW SPI

//  UNO
AD9833 AD(10, 11, 13);  //  software SPI
//  AD9833 AD(10);       //  hardware SPI


uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("AD9833_LIB_VERSION: ");
  Serial.println(AD9833_LIB_VERSION);
  Serial.println();
  delay(10);

  // SPI.begin();

  AD.begin();

  Serial.print("hardware:\t");
  Serial.println(AD.usesHWSPI());
  delay(10);

  start = micros();
  AD.setFrequency(2000, 0);
  stop = micros();
  Serial.print("setFrequency:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setPhase(45, 0);
  stop = micros();
  Serial.print("setPhase:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setWave(AD9833_SQUARE1);
  stop = micros();
  Serial.print("setWave:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.writeFrequencyRegisterLSB(0, 10000);
  stop = micros();
  Serial.print("writeFrequencyRegisterLSB:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.writeFrequencyRegisterMSB(0, 10000);
  stop = micros();
  Serial.print("writeFrequencyRegisterMSB:\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setFrequencyChannel(0);
  stop = micros();
  Serial.print("setFrequencyChannel(0):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  AD.setPhaseChannel(0);
  stop = micros();
  Serial.print("setPhaseChannel(0):\t");
  Serial.println(stop - start);
  delay(10);
}


void loop()
{
}


//  -- END OF FILE --
