//
//    FILE: LTC2991_read_voltage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LTC2991


#include "Wire.h"
#include "LTC2991.h"


LTC2991 LTC(0x48);  //  all address lines GND


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LTC2991_LIB_VERSION: ");
  Serial.println(LTC2991_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  LTC.begin();
  while (!LTC.isConnected())
  {
    Serial.println("Could not connect to device");
    delay(2000);
  }

  for (uint8_t channel = 1; channel <= 4; channel++)
  {
    //  enable all channels  ==> are enabled in pairs! )
    LTC.enable(channel, true);
    LTC.enable_filter(channel, false);
    LTC.set_mode_voltage_normal(channel);
  }

  //  to get multiple readings in loop()
  LTC.set_acquisition_repeat();
}


void loop()
{
  static uint32_t lastTime = 0;

  if ((millis() - lastTime) >= 2000)
  {
    lastTime = millis();
    Serial.print(lastTime);
    for (uint8_t channel = 1; channel <= 8; channel++)
    {
      Serial.print("\t");
      Serial.print(LTC.get_value(channel));
    }
    Serial.println();
  }
}


//  -- END OF FILE --
