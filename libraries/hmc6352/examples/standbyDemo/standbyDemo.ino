//
//    FILE: standbyDemo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo app HMC6352 library - standby mode for Arduino


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

  Serial.print("Output modus");
  Serial.println(Compass.getOutputModus());
}


void loop()
{
  Compass.wakeUp();  //  decent wake up from sleep mode

  //  Note that reading a heading is requires two steps, ask() & read()
  //  this makes the query and continuous mode more efficient
  //  without impact on the footprint of the lib.
  //  this way one can ask a make a reading and fetch it a bit later.
  //  TODO is it fast enough for IRQ ?
  int x = Compass.askHeading();
  Serial.print("Ask returns: ");
  Serial.print(x);

  heading = Compass.readHeading();
  Serial.print("\task & read : ");
  Serial.println(heading);

  //  go to low energy mode
  Compass.sleep();
  delay(500);

  //  this is the simplest mode to use the library
  //  suitable for 99.9% of all robots :)
  Compass.wakeUp();
  Serial.print("getHeading : ");
  Serial.println(Compass.getHeading());
  Compass.sleep();

  delay(500);
}


//  -- END OF FILE --

