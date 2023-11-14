//
//    FILE: moduloMap_rotations.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo math for wirecutter
//     URL: https://github.com/RobTillaart/moduloMap

//  This example shows the basic math to implement a suspencer 
//  for a wire cutter device. The length of the wire is measured
//  by the number of rotations of a steppermotor.
//
//  A real wirecutter application needs length input and 
//  a signal to start rolling and cut (automatically).
//  and probably much more (default lengths, wire detection etc)


#include "Arduino.h"
#include "moduloMap.h"

MODMAP  wireCutter;

//  assume the distance measurement wheel for a wirecutter
//  has a radius of 5 centimeter = about 2 inch
float radius = 5.0;

//  assume we want to cut off 20 centimeter every time.
float wireLength = 50;

//  assume steppermotor has e.g 200 steps per rotation
uint16_t stepsPerRotation = 200;



void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("MODMAP_LIB_VERSION: ");
  Serial.println(MODMAP_LIB_VERSION);
  Serial.println();

  wireCutter.begin(0, 2 * PI * radius);

  //  how many rotations need to be made for given length.
  float rots = wireCutter.rotations(wireLength);

  //  how many steps are this? (note we round up)
  uint16_t steps = ceil(rots * stepsPerRotation);

  Serial.print("Wirelength ");
  Serial.print(wireLength);
  Serial.print(" cm => ");
  Serial.print(rots);
  Serial.print(" rotations => ");
  Serial.print(steps);
  Serial.print(" steps.");
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
