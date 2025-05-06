//
//    FILE: TCA9555_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"

//  adjust address if needed
TCA9555 TCA(0x20);

int val = 0;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();
  TCA.begin();

  Serial.println("CLOCK\tread1\tread8\tread16\twrite1\twrite8\twrite16");
  delay(100);

  for (uint32_t speed = 50; speed <= 1000; speed += 50)
  {
    Wire.setClock(speed * 1000);

    TCA.pinMode16(0xFFFF);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.read1(0);
    }
    stop = micros();
    Serial.print(speed);
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    delay(100);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.read8(0);
    }
    stop = micros();
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    delay(100);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.read16();
    }
    stop = micros();
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    delay(100);

    ///////////////////////

    TCA.pinMode16(0x0000);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.write1(1, 0);
    }
    stop = micros();
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    delay(100);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.write8(1, 55);
    }
    stop = micros();
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    delay(100);

    start = micros();
    for (int i = 0; i < 1000; i++)
    {
      val = TCA.write16(0xABCD);
    }
    stop = micros();
    Serial.print("\t");
    Serial.print((stop - start) * 0.001);
    Serial.println();
    delay(100);
  }

  Serial.println();
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
