//
//    FILE: LTC2991_internal_temp_volt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo monitoring Tinternal and VCC
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

  LTC.enable_Tintern_Vcc(true);
  LTC.set_Kelvin_Tintern();

  //  to get multiple readings in loop()
  LTC.set_acquisition_repeat();
}


void loop()
{
  static uint32_t lastTime = 0;

  if ((millis() - lastTime) >= 2000)
  {
    lastTime = millis();
    if (LTC.new_temperature())
    {
      float temp = LTC.get_Tintern();
      Serial.print(lastTime);
      Serial.print("\tTinternal: \t");
      Serial.println(temp);
    }

    if (LTC.new_voltage())
    {
      float vcc = LTC.get_VCC();
      Serial.print(lastTime);
      Serial.print("\tVCC: \t");
      Serial.println(vcc);
    }
  }

}


//  -- END OF FILE --
