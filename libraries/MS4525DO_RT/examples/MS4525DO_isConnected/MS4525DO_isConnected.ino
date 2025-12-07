//
//    FILE: MS4525DO_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
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
  if (sensor.begin(100) == false)
  {
    Serial.print("Cannot find sensor:\t");
    Serial.print(sensor.getAddress());
    Serial.print(" - state: ");
    Serial.println(sensor.state());
    Serial.println("Check wires or try another address.");
    while(1);
  }
}


void loop()
{
  if (sensor.isConnected() == false)
  {
    Serial.println("cannot connect to sensor!");
  }
  else
  {
    int state = sensor.read();
    if (state == MS4525DO_OK)
    {
      Serial.print("mBar:\t");
      Serial.println(sensor.getMilliBar());
      Serial.println();
    }
    else 
    {
      Serial.print("error: ");
      Serial.println(state);
    }
  }

  delay(1000);
}


//  -- END OF FILE --
