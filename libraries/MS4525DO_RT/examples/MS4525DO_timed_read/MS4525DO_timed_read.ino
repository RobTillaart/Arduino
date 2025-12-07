//
//    FILE: MS4525DO_timed_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MS4525DO_RT


#include "MS4525DO.h"


MS4525DO sensor(0x28);

const uint32_t interval = 1000;


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
  uint32_t now = millis();

  if (now - sensor.lastRead() >= interval)
  {
    Serial.print(now);
    Serial.print("\t");
    int state = sensor.read();
    switch (state)
    {
      case MS4525DO_OK:
        Serial.print("mBar:\t");
        Serial.println(sensor.getMilliBar());
        break;
      case MS4525DO_INIT:
        Serial.println("S:\tINIT");
        break;
      case MS4525DO_READ_ERROR:
        Serial.print("E:\tread error\t");
        Serial.println(sensor.errorCount());
        break;
      case MS4525DO_OVF_ERROR:
        Serial.print("E:\tOVF error\t");
        Serial.println(sensor.errorCount());
        break;
      default:        //  catch all other...
        Serial.print("E:\t");
        Serial.println(state);
        break;
    }
  }
}


//  -- END OF FILE --
