//
//    FILE: HX710B_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

//  adjust pins to your setup
uint8_t dataPin = 6;
uint8_t clockPin = 7;

HX710B HX(dataPin, clockPin);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();

  HX.begin();

  //  adjust to your raw measurements.
  HX.calibrate(50, 0, 100, 80);
}


void loop()
{
  Serial.println(HX.read(1), 1);
}


//  -- END OF FILE --
