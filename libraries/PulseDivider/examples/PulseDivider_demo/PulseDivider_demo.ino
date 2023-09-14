//
//    FILE: PulseDivider_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Minimal sketch
//    DATE: 2023-09-13
//     URL: https://github.com/RobTillaart/PulseDivider


#include "PulseDivider.h"

//  all parameters set explicit.

PulseDivider PD(6, 7, 17, 5, 1, RISING, false);
uint32_t count = 0;

void setup()
{
  Serial.begin(115200);

  Serial.print("PULSEDIVIDER_LIB_VERSION: ");
  Serial.println(PULSEDIVIDER_LIB_VERSION);

  Serial.println(PD.getInPin());
  Serial.println(PD.getOutPin());
  Serial.println(PD.getRatio());
  Serial.println(PD.getDuration());
  Serial.println(PD.getEdge());
  Serial.println(PD.getInvert());

  PD.start();
}


void loop()
{
  PD.check(); //  as much as possible

  count++;
  if (count == 1000000)
  {
    Serial.println("CNT");
    count = 0;
  }
  // delay(500);
}


//  -- END OF FILE --
