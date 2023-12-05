//
//    FILE: queryDemo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo HMC6352 library - query mode for Arduino


#include "hmc6352.h"

hmc6352 Compass(0x21);

int heading;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("HMC6352_LIB_VERSION: ");
  Serial.println(HMC6352_LIB_VERSION);

  Wire.begin();
  Compass.begin();

  Serial.print("Output modus: ");
  Serial.println(Compass.getOutputModus());

  heading = Compass.askHeading();
  Serial.print("Ask returns: ");
  Serial.println(heading);
}


void loop()
{
  //  in query mode it is not needed to ask for a new reading every time
  //  as it will do a new reading directly after the chip is read
  //  and waits until it is asked for.
  //  Try making a fast turn and smile ...
  heading = Compass.readHeading();
  Serial.print("Degree : ");
  Serial.println(heading);
  delay(1000);
}


//  -- END OF FILE --

