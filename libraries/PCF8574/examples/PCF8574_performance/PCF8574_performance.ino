//
//    FILE: PCF8574_performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-24
// PURPOSE: test PCF8574 library at different I2C speeds.
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

PCF8574 PCF(0x38);

uint32_t start, stop;

volatile uint8_t x;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();

  PCF.begin();
  Serial.println(PCF.isConnected());
  delay(100);  //  time to flush Serial 


  for (long clk = 100000; clk < 800000; clk += 50000)
  {
    //  setup and measure
    Wire.setClock(clk);
    start = micros();
    x = PCF.read8();
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
    PCF.write8(0xFF);
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

