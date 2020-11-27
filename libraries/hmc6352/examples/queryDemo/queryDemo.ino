//
//    FILE: queryDemo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo HMC6352 library - query mode for Arduino
//
// HISTORY:
// 0.1.00 - 2011-04-12 initial version
// 0.1.1  - 2017-09-13 renamed to .ino
// 0.2.0    2020-06-13 match lib version 0.2.0
//

#include <hmc6352.h>

hmc6352 Compass(0x21);

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
  // in query mode it is not needed to ask for a new reading every time
  // as it will do a new reading directly after the chip is read
  // and waits until it is asked for.
  // Try making a fast turn and smile ...
  heading = Compass.readHeading();
  Serial.print("Degree : ");
  Serial.println(heading);
  delay(1000);
}

// END OF FILE
