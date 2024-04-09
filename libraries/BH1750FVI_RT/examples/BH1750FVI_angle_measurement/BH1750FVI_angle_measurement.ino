//
//    FILE: BH1750FVI_angle_measurement.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of BH1750FVI lux scanner library
//     URL: https://github.com/RobTillaart/BH1750FVI_RT
//

/*
   BH1750FVI_angle_measurement

   Experimental application

   first take a reference measurement for 5 seconds
   holding the sensor flat under a light source.

   Then take a second reference for 5 seconds
   holding the sensor at 90 degrees.

   Thereafter hold the sensor at any angle and the
   Arduino will estimate the angle based upon the
   Lux level compared to the references.

   First trials are not not too bad, roughly within 15° accuracy
*/


#include "BH1750FVI.h"

BH1750FVI myLux(0x23);

float ref1 = 0;
float ref2 = 0;


float measure(int seconds, bool minimum = false)
{
  float mn = 1e8;
  float mx = 0;
  uint32_t start = millis();
  while (millis() - start < (seconds * 1000UL))
  {
    float val = myLux.getLux();
    if (val > mx) mx = val;
    if (val < mn) mn = val;
    delay(200);
  }
  if (minimum) return mn;
  return mx;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print(__FILE__);
  Serial.println();

  Wire.begin();

  myLux.powerOn();
  myLux.setContHighRes();

  Serial.println("Reference 1");
  ref1 = measure(5, false);

  Serial.println("Reference 2");
  ref2 = measure(5, true);
  Serial.println("Start");
  Serial.println(ref1);
  Serial.println(ref2);
}


void loop()
{
  float val = measure(1, false);

  val = map(val, ref2, ref1, 0, ref1);    //  does not constrain...

  //  prevent NAN
  float f = val / ref1;    //  map to 0..1 
  if (f > 1) f = 1;        //  constrain upper
  if (f < -1) f = -1;      //  constrain lower

  Serial.print(val, 1);
  Serial.print("\t");
  Serial.print(f);
  Serial.print("\t");
  Serial.print(acos(f) * 180 / PI);
  Serial.print("\t");
  Serial.println();
}


//  -- END OF FILE --
