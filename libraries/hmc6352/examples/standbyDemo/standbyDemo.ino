//
//    FILE: standbyDemo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: demo app HMC6352 library - standby mode for Arduino
//
// HISTORY:
// 0.1.00 - 2011-04-12 initial version
// 0.1.1  - 2017-09-13 renamed to .ino;
// 0.2.0    2020-06-13 refactor
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
  
  Serial.print("Output modus");
  Serial.println(Compass.getOutputModus());
}

void loop()
{
  Compass.wakeUp(); // decent wake up from sleep mode

  // Note that reading a heading is requires two steps, ask() & read()
  // this makes the query and continuous mode more efficient
  // without impact on the footprint of the lib.
  // this way one can ask a make a reading and fetch it a bit later.
  // TODO is it fast enough for IRQ ?
  int x = Compass.askHeading();
  //Serial.print("Ask returns: ");
  //Serial.println(x);

  heading = Compass.readHeading();
  Serial.print("ask & read : ");
  Serial.println(heading);

  Compass.sleep();  // low energy mode
  delay(500);

  // this is the simplest mode to use the library
  // suitable for 99.9% of all robots :)
  Compass.wakeUp();
  Serial.print("getHeading : ");
  Serial.println(Compass.getHeading());
  Compass.sleep();
  delay(500);
}

// END OF FILE
