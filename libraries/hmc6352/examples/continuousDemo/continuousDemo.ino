//
//    FILE: continuousDemo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo app HMC6352 library - continuous mode for Arduino


#include "hmc6352.h"

hmc6352 Compass(0x21);  //  0x21 <==> 33  <==> 66 >> 1

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
  //  in continuous mode it is not needed to ask for a new reading every time
  //  as it will do a new reading continuously even when not asked for
  //  Try making a fast turn and see the difference with the query mode
  heading = Compass.readHeading();
  Serial.print("Degree : ");
  Serial.println(heading);
  delay(1000);
}


//  -- END OF FILE --

