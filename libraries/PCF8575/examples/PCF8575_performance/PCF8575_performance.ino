//
//    FILE: PCF8575_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCF8575 library
//     URL: https://github.com/RobTillaart/PCF8575


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
  delay(100);  //  time to flush Serial 


  for (long clk = 100000; clk < 600000; clk += 50000)
  {
    //  setup and measure
    Wire.setClock(clk);
    start = micros();
    x = PCF.read16();
    stop = micros();

    //  output results
    Serial.println(clk);
    Serial.print("Read:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(x);             //  keep build CI compiler happy
    delay(1000);

    //  measure
    start = micros();
    PCF.write16(0xFFFF);
    stop = micros();

    //  output results
    Serial.print("Write:\t ");
    Serial.println(stop - start);
    delay(1000);
  }
}


void loop()
{
}


//  -- END OF FILE --

