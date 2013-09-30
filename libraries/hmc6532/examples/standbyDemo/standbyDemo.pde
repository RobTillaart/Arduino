// 
//    FILE: standbyDemo.pde
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo app HMC6352 library - standby mode for Arduino
//
// HISTORY: 
// 0.1.00 - 2011-04-12 initial version
//
// Released to the public domain
//
// All disclaimers apply use at own risk
//

#include <Wire.h>
#include <hmc6352.h>

hmc6352 Compass(0x21);  // 0x21 <==> 33  <==> 66 >> 1

void setup()
{
  Serial.begin(19200);
  Serial.println("HMC6352: Version ");
  Serial.println(HMC_LIB_VERSION);
  Serial.print("current output modus");
  Serial.println(Compass.getOutputModus());
}
int x;

void loop()
{
  Compass.wakeUp(); // decent wake up from sleep mode
  
  // Note that reading a heading is requires two steps, ask() & read()
  // this makes the query and continuous mode more efficient
  // without impact on the footprint of the lib.
  // this way one can ask a make a reading and fetch it a bit later.
  // TODO is it fast enough for IRQ ?
  x = Compass.askHeading();
  //Serial.print("Ask returns: ");
  //Serial.println(x);  
  
  x = Compass.readHeading();
  Serial.print("ask & read : Degree : ");
  Serial.println(x);
  
  Compass.sleep();  // low energy mode
  delay(500);
  
  // this is the simplest mode to use the library
  // suitable for 99.9% of all robots :)
  Compass.wakeUp();
  Serial.print("getHeading : Degree : ");
  Serial.println(Compass.getHeading());
  Compass.sleep();
  delay(500);
}
// END OF FILE









