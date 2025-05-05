//
//    FILE: 74HC590_demo.ino
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
//  test other constructors.
DEV_74HC590 count1(OE, CCLR, CCKEN, CCLK, RCLK);
DEV_74HC590 count2(OE, CCLR, CCKEN, CCLK);


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


}


void loop()
{
  //  will effectively count from 0 to 255
  //  and wrap around / start over again.
  count0.pulseRegister();  //  copy internal counter
  count0.pulseCounter();   //  increment internal counter.
  delay(1000);
}


//  -- END OF FILE --
