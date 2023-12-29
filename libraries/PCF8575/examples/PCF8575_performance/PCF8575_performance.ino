//
//    FILE: PCF8575_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-24
// PURPOSE: test PCF8575 library


#include "PCF8575.h"

PCF8575 PCF(0x20);

uint32_t start, stop;

volatile uint16_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  PCF.begin();
  Serial.println(PCF.isConnected());

  for (long clk = 100000; clk < 500000; clk += 50000)
  {
    Serial.println(clk);
    Wire.setClock(clk);
    start = micros();
    x = PCF.read16();
    stop = micros();
    Serial.print("Read:\t");
    Serial.println(stop - start);
    delay(1000);

    start = micros();
    PCF.write16(0xFFFF);
    stop = micros();
    Serial.print("Write:\t ");
    Serial.println(stop - start);
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --

