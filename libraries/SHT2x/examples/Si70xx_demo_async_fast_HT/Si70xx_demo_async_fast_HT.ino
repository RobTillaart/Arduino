//
//    FILE: Si70xx_demo_async_fast_HT.ino
//  AUTHOR: JensB
// PURPOSE: demo asynchronous interface
//     URL: https://github.com/RobTillaart/SHT2x
//
// - needs version 0.4.2 or higher
//
// - saves separate conversion cycle for the temperature
//   by reading back the temperature that was established
//   with the last humidity measurement
//


#include "SHT2x.h"

Si7021 dhtSensor;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  //  connect to sensor
  Wire.begin();
  while (!dhtSensor.isConnected())
  {
    Serial.print("*");
    delay(1);
  }
  Serial.println();

  //  soft reset sensor
  dhtSensor.reset();
  //  ~5 ms for soft reset to complete
  delay(5);
  while (!dhtSensor.isConnected())
  {
    Serial.print("*");
    delay(1);
  }
  Serial.println();

  //  change resolution to 11 bits
  if (!dhtSensor.setResolution(3))  //  3: 11 bits / 0.08 °C / 0.05 % / ~18 ms - see datasheet
  {
    Serial.print("set resolution error:\t");
    Serial.println(dhtSensor.getError());
  }
}


void loop()
{
  uint32_t from = millis();

  if (dhtSensor.isConnected())
  {
    //  async request humidity and wait for completion
    dhtSensor.requestHumidity();
    int available = 20;  //  [ms] choose a value that is at least 10 % higher that the measurement time from the datasheet
    while (!dhtSensor.reqHumReady() && (available-- > 0))
    {
      delay(1);  //  or do something else here
    }

    //  retrieve humidity and temperature values
    if (available)
    {
      if (!dhtSensor.readHumidity())
      {
        Serial.print("read humidity error:\t");
        Serial.println(dhtSensor.getError());
      }
      else
      {
        if (!dhtSensor.readCachedTemperature())
        {
          Serial.print("read temp error:\t");
          Serial.println(dhtSensor.getError());
        }
      }

      Serial.print("TEMP:\t");
      Serial.println(dhtSensor.getTemperature(), 1);
      Serial.print("HUMI:\t");
      Serial.println(dhtSensor.getHumidity(), 1);
    }
    else
    {
      Serial.println("requesting humidity failed");
    }

    uint32_t now = millis();
    Serial.print("TIME:\t");
    Serial.println(now - from);
    Serial.println();
  }
  else
  {
    Serial.println("sensor not connected");
  }

  //  do other things here
  delay(1000);
}


//  -- END OF FILE --
