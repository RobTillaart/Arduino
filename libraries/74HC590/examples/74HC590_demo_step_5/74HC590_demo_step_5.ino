//
//    FILE: 74HC590_demo_step_5.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
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

int n = 0;


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
  n = 0;
  count0.clearCounter();   //  set internal counter to zero
  count0.pulseRegister();  //  copy internal counter
  count0.pulseCounter();   //  increment internal counter.
  delay(2000);
}


void loop()
{
  n++;
  if (n == 5)
  {
    //  copy internal counter every 5th pulse.
    count0.pulseRegister();
    n = 0;
  }

  //  increment internal counter.
  count0.pulseCounter();
  delay(1000);
}


//  -- END OF FILE --
