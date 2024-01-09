//
//    FILE: FRAM_readObject.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading objects
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"


FRAM fram;

uint32_t start;
uint32_t stop;

uint32_t sizeInBytes = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Serial.println("\n run writeObject Demo first!\n");

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  test_float();
  test_struct();
}


void loop()
{
}


void test_float()
{
  float x = 0;
  Serial.println(x, 6);

  fram.readObject(100, x);
  Serial.println(x, 6);
}

struct point
{
  float x;
  float y;
  float z;
} Q;

void test_struct()
{
  fram.readObject(50, Q);
  Serial.println(Q.x);
  Serial.println(Q.y);
  Serial.println(Q.z);
}


//  -- END OF FILE --
