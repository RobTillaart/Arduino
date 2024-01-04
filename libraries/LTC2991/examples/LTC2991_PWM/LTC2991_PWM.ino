//
//    FILE: LTC2991_PWM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LTC2991


#include "Wire.h"
#include "LTC2991.h"


LTC2991 LTC(0x48);  //  all address lines GND


int speed = 10;
int incr = 1;


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

  LTC.enable_PWM(true);
}


void loop()
{
  static uint32_t lastTime = 0;

  if ((millis() - lastTime) >= 100)
  {
    lastTime = millis();

    LTC.set_PWM(speed);
    if (speed == 511) incr = -1;   //  reverse speed
    if (speed == 0)   incr = 1;    //  reverse speed
    speed += incr;

    Serial.print(lastTime);
    Serial.print("\t");
    Serial.print(LTC.get_PWM());
    Serial.println();
  }

}


//  -- END OF FILE --
