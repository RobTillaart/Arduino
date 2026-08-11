//
//    FILE: DS3502_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure setValue() at various I2C speeds.
//     URL: https://github.com/RobTillaart/DS3502


#include "DS3502.h"


DS3502 pot(0x28);


long value = 0;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS3502_LIB_VERSION: ");
  Serial.println(DS3502_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  pot.begin();


  Serial.println("\nNO NVRAM\n");
  pot.enableNVRAM(false);
  delay(100);
  for (uint32_t speed = 100000; speed <= 500000; speed += 100000)
  {
    Wire.setClock(speed);
    start = micros();
    for (int i = 0; i < 100; i++)
    {
      pot.setValue(i);
    }
    stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print((stop - start) * 0.01f, 2);
    Serial.println(" us");
    delay(100);
  }


  Serial.println("\nWITH NVRAM\n");
  pot.enableNVRAM(true);
  delay(100);
  for (uint32_t speed = 100000; speed <= 500000; speed += 100000)
  {
    Wire.setClock(speed);
    start = micros();
    for (int i = 0; i < 100; i++)
    {
      pot.setValue(i);
    }
    stop = micros();
    pot.enableNVRAM(false);
    Serial.print(speed);
    Serial.print("\t");
    Serial.print((stop - start) * 0.01f, 2);
    Serial.println(" us");
    delay(100);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --
