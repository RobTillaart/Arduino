//
//    FILE: RunningMinMax_two_stage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two stage min max finding
//     URL: https://github.com/RobTillaart/RunningMinMax


#include "RunningMinMax.h"


RunningMinMax stage1 = RunningMinMax(20);  //  5 seconds 4 samples/second
RunningMinMax stage2 = RunningMinMax(24);  //  12x (1 min and 1 max) = 1 minute

uint16_t counter = 0;

void setup()
{
  while (!Serial);  //  Wait for serial port to connect. Needed for Leonardo + MKR1010.
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("RUNNING_MINMAX_LIB_VERSION: "));
  Serial.println(RUNNING_MINMAX_LIB_VERSION);
  Serial.println();

  Serial.println("X\tMIN_1\tMAX_1\tMIN_2\tMAX_2");
}


void loop()
{
  //  new sample
  int x = random(1000);

  //  add to stage1
  stage1.add(x);
  counter++;
  //  every 20 samples add the MIN and MAX from stage1 to stage2
  if (counter >= 20)
  {
    counter = 0;  
    stage2.add(stage1.getMinimum());
    stage2.add(stage1.getMaximum());
  }

  Serial.print(x);
  Serial.print("\t");
  Serial.print(stage1.getMinimum());
  Serial.print("\t");
  Serial.print(stage1.getMaximum());
  Serial.print("\t");
  Serial.print(stage2.getMinimum());
  Serial.print("\t");
  Serial.print(stage2.getMaximum());
  Serial.println();
  delay(25);
}


//  -- END OF FILE --
