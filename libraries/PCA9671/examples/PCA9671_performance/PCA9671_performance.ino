//
//    FILE: PCA9671_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9671 library
//     URL: https://github.com/RobTillaart/PCA9671


#include "PCA9671.h"

PCA9671 PCA(0x20);

uint32_t start, stop;

volatile uint16_t x;


void setup()
{
  //  while(!Serial);  //  uncomment when needed
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9671_LIB_VERSION:\t");
  Serial.println(PCA9671_LIB_VERSION);
  Serial.println();

  Wire.begin();

  PCA.begin();
  Serial.println(PCA.isConnected());
  delay(100);  //  time to flush Serial


  for (long clk = 100000; clk < 600000; clk += 50000)
  {
    //  setup and measure
    Wire.setClock(clk);
    start = micros();
    x = PCA.read16();
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
    PCA.write16(0xFFFF);
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

