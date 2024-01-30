//
//    FILE: MAX471_plotter
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MAX471 for plotter
//     URL: https://github.com/RobTillaart/MAX471_RT


#include "MAX471.h"

MAX471 mx(A0, A1);

void setup()
{
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("MAX471_LIB_VERSION: ");
  //  Serial.println(MAX471_LIB_VERSION);

  mx.begin(5.0, 1023);

  //  print header
  Serial.println("mA\tmV\tmW");
}


void loop()
{
  Serial.print(mx.readCurrentMilliAmpere());
  Serial.print("\t");
  Serial.print(mx.readVoltageMilliVolts());
  Serial.print("\t");
  Serial.print(mx.calcPowerMilliWatt());
  Serial.print("\n");
  delay(10);
}


//  -- END OF FILE --
