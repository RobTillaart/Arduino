//
//    FILE: MS4525DO_raw_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo raw counters
//     URL: https://github.com/RobTillaart/MS4525DO_RT


#include "MS4525DO.h"


MS4525DO sensor(0x28);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS4525DO_LIB_VERSION: ");
  Serial.println(MS4525DO_LIB_VERSION);
  Serial.println();

  Wire.begin();
  sensor.begin(100);

  Serial.println("Pres \tTemp");
}


void loop()
{
  int state = sensor.read();
  if (state == MS4525DO_OK)
  {
    Serial.print(sensor.rawPressureCount());
    Serial.print("\t");
    Serial.println(sensor.rawTemperatureCount());
  }
  else
  {
    Serial.print("error: ");
    Serial.println(state);
  }

  delay(1000);
}


//  -- END OF FILE --
