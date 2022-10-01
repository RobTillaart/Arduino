//
//    FILE: PCF8574_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-24
// PUPROSE: test PCF8574 library at different I2C speeds.


#include "PCF8574.h"

PCF8574 PCF(0x38);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  PCF.begin();
  Serial.println(PCF.isConnected());

  for (long clk = 100000; clk < 800000; clk += 100000)
  {
    Serial.println(clk);
    Wire.setClock(clk);
    start = micros();
    int x = PCF.read8();
    stop = micros();
    Serial.print("Read:\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(x);             //  keep build CI compiler happy
    delay(1000);

    start = micros();
    PCF.write8(0xFF);
    stop = micros();
    Serial.print("Write:\t ");
    Serial.println(stop - start);
    delay(1000);
  }
}


void loop()
{
}


// -- END OF FILE --
