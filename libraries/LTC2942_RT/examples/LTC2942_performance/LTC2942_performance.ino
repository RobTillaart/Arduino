//
//    FILE: LTC2942_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic charge reading
//     URL: https://github.com/RobTillaart/LTC2942_RT


#include "LTC2942.h"

LTC2942 LTC;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTC2942_LIB_VERSION: ");
  Serial.println(LTC2942_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = LTC.begin(2000, 0.050);
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("ADDR:\t");
  Serial.println(LTC.getAddress());
  delay(100);

  Serial.println("\nRAW");
  for (uint32_t speed = 100000; speed <= 600000; speed += 100000)
  {
    Wire.setClock(speed);
    uint32_t start = micros();
    uint16_t charge;
    LTC.getRawCharge(charge);
    uint32_t stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(charge);
    Serial.println();
    delay(100);
  }

  Serial.println("\nmAh");
  for (uint32_t speed = 100000; speed <= 600000; speed += 100000)
  {
    Wire.setClock(speed);
    uint32_t start = micros();
    float charge;
    LTC.getCharge(charge);
    uint32_t stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(charge, 3);
    Serial.println();
    delay(100);
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --
