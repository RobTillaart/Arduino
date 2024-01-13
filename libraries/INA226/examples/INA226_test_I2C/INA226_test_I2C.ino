//
//    FILE: INA226_test_I2C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test I2C speed.
//     URL: https://github.com/RobTillaart/INA219


#include "INA226.h"


INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA226_LIB_VERSION: ");
  Serial.println(INA226_LIB_VERSION);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
  }

  for (uint32_t speed = 50000; speed <= 800000; speed += 50000)
  {
    delay(100);
    Wire.setClock(speed);
    uint32_t start = micros();
    uint8_t mode = INA.getMode();
    uint32_t stop = micros();

    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.println(mode);
  }

  Serial.println("\n...done...");
}


void loop()
{
}


//  -- END OF FILE --
