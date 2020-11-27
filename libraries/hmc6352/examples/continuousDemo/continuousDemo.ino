//
//    FILE: continuousDemo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo app HMC6352 library - continuous mode for Arduino
//
// HISTORY:
// 0.1.0  - 2011-04-12 initial version
// 0.1.1  - 2017-09-13 renamed to .ino
// 0.2.0    2020-06-13 match 0.2.0 version of lib
//

#include <hmc6352.h>

hmc6352 Compass(0x21);  // 0x21 <==> 33  <==> 66 >> 1

int heading;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("LIB: ");
  Serial.println(HMC6352_LIB_VERSION);

  Compass.begin();
  
  Serial.print("Output modus: ");
  Serial.println(Compass.getOutputModus());

  heading = Compass.askHeading();
  Serial.print("Ask returns: ");
  Serial.println(heading);
}

void loop()
{
  // in continuous mode it is not needed to ask for a new reading every time
  // as it will do a new reading continuously even when not asked for
  // Try making a fast turn and see the difference with the query mode
  heading = Compass.readHeading();
  Serial.print("Degree : ");
  Serial.println(heading);
  delay(1000);
}

// END OF FILE
