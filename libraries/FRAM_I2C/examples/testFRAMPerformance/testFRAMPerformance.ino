//
//    FILE: testFRAMPerformance.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: test for FRAM library for Arduino
//     URL: https://github.com/RobTillaart/FRAM_I2C
//

#include "FRAM.h"

FRAM fram;

uint32_t start;
uint32_t stop;

int ar[600];
  
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);
  Serial.println();
  Serial.println();

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.println(rv);
  }
  else
  {
    for (int s = 1; s < 9; s++)  // test up to 800 KB
    {
      uint32_t speed = s * 100000UL;
      Serial.print("CLOCK: ");
      Serial.println(speed);
      Wire.setClock(speed);
      testReadWriteLarge();
    }
    Wire.setClock(100000);
  }
  Serial.println("done...");
}

void loop()
{
}

void testReadWriteLarge()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int i = 0; i < 600; i++) ar[i] = i;

  start = millis();
  fram.write(1000, (uint8_t*)ar, 1200);
  stop = millis();
  Serial.print("WRITE 1200 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");

  for (int i = 0; i < 600; i++) ar[i] = 0;

  start = millis();
  fram.read(1000, (uint8_t*)ar, 1200);
  stop = millis();
  Serial.print("READ 1200 bytes TIME:\t");
  Serial.print(stop - start);
  Serial.println(" ms");

  for (int i = 0; i < 600; i++)
  {
    if (ar[i] != i)
    {
      Serial.print("FAIL: \t");
      Serial.print(ar[i]);
      Serial.print('\t');
      Serial.println(i);
    }
  }
  Serial.println();
}

// END OF FILE