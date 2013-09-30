// 
//    FILE: queryDemo.pde
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo app HMC6352 library - query mode for Arduino
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
  
  int x = Compass.askHeading();
  //Serial.print("Ask returns: ");
  //Serial.println(x);  
}
int x;

void loop()
{
  // in query mode it is not needed to ask for a new reading every time
  // as it will do a new reading directly after the chip is read
  // and waits until it is asked for.
  // Try making a fast turn and smile ...
  x = Compass.readHeading();
  Serial.print("Degree : ");
  Serial.println(x);
  delay(1000);
}
// END OF FILE









