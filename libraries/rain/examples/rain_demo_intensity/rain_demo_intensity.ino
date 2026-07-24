//
//    FILE: rain_demo_intensity.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo experimental intensity formula
//     URL: https://github.com/RobTillaart/RAIN
//
//  EXPERIMENTAL
//  place the FC-37 under an angle (30° ?) so drop that hit, will roll off.
//  This sketch tries to determine the interval between drops
//


#include "rain.h"

RAIN  RS(A0);
float threshold = 40.0;  //  adjust if needed.
float mlPerDrop = 69.0;  //  adjust if needed


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RAIN_LIB_VERSION: ");
  Serial.println(RAIN_LIB_VERSION);
  Serial.println();

  RS.begin(5.000, 1023);

  //  measured in an earlier run, adjust to your calibration.
  RS.setDryReference(3.5);

  Serial.println(RS.percentage());
}


void loop()
{
  //  determine interval
  //  wait for drop
  while (RS.percentage() < threshold);
  uint32_t start = millis();
  //  delay(1000);  //  optional, prevent "bouncing"

  while (RS.percentage() >= threshold);  //  adjust treshold if needed.
  float interval = (millis() - start) * 0.001;
  //  delay(1000);  //  optional, prevent "bouncing"

  float dropsPerHour = 3600.0 / interval;
  float liter = dropsPerHour * mlPerDrop * 0.001;

  Serial.print(millis());
  Serial.print("\t");
  Serial.print(interval, 3);
  Serial.print("\t");
  Serial.print(liter, 2);
  Serial.print("\t");
  if (liter < 0.25)      Serial.println("trace");
  else if (liter < 1.00) Serial.println("very light");
  else if (liter < 2.50) Serial.println("light");
  else if (liter < 10.0) Serial.println("moderate");
  else if (liter < 50.0) Serial.println("heavy");
  else                   Serial.println("violent");
}


//  -- END OF FILE --
