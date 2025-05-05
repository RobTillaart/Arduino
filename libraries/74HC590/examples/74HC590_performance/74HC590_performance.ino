//
//    FILE: 74HC590_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/74HC590
//
//  e.g. add an array of LED's to the outputs.


#include "74HC590.h"

#define OE        4
#define CCLR      5
#define CCKEN     6
#define CCLK      7
#define RCLK      8
#define RCO       9


DEV_74HC590 count0(OE, CCLR, CCKEN, CCLK, RCLK, RCO);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LIB_74HC590_VERSION: ");
  Serial.println(LIB_74HC590_VERSION);
  Serial.println();

  //  explicit configuration
  count0.enableOutput();
  count0.enableCounter();

  //  set output to zero
  count0.clearCounter();   //  set internal counter to zero
  count0.pulseRegister();  //  copy internal counter
  count0.pulseCounter();   //  increment internal counter.
  delay(2000);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    count0.pulseRegister();  //  copy internal counter
  }
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  delay(1000);


  start = micros();
  //  note the loop overhead...
  for (int i = 0; i < 1000; i++)
  {
    count0.pulseRegister();  //  copy internal counter
    count0.pulseCounter();   //  increment internal counter.
  }
  stop = micros();
  Serial.print("TIME: \t");
  Serial.println(stop - start);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
