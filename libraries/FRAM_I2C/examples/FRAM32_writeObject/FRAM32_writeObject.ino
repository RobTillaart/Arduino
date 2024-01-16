//
//    FILE: FRAM32_writeObject.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo writing reading objects
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"


FRAM32 fram;

uint32_t start;
uint32_t stop;

uint32_t sizeInBytes = 0;



void test_float()
{
  float x = 3.14159265;
  Serial.println(x, 6);
  fram.writeObject(100, x);

  x = 1.0/x;
  Serial.println(x, 6);

  fram.readObject(100, x);
  Serial.println(x, 6);
}


struct point
{
  float x;
  float y;
  float z;
} P = {3.91, 5.24, 7.58};


void test_struct_low_address_range()
{
  Serial.println(P.x);
  Serial.println(P.y);
  Serial.println(P.z);
  fram.writeObject(50, P);

  struct point Q;
  fram.readObject(50, Q);
  Serial.println(Q.x);
  Serial.println(Q.y);
  Serial.println(Q.z);

  if ((P.x != Q.x) || (P.y != Q.y) || (P.z != Q.z))
  {
    Serial.println("ERROR!");
  }
}


void test_struct_high_address_range()
{
  Serial.println(P.x);
  Serial.println(P.y);
  Serial.println(P.z);
  fram.writeObject(70000, P);

  struct point Q;
  fram.readObject(70000, Q);
  Serial.println(Q.x);
  Serial.println(Q.y);
  Serial.println(Q.z);

  if ((P.x != Q.x) || (P.y != Q.y) || (P.z != Q.z))
  {
    Serial.println("ERROR!");
  }
}



void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRAM_LIB_VERSION: ");
  Serial.println(FRAM_LIB_VERSION);

  Wire.begin();

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  //  get size in bytes
  sizeInBytes = fram.getSize() * 1024;
  //  clear FRAM
  for (uint32_t addr = 0; addr < sizeInBytes; addr++)
  {
    fram.write8(addr, 0x00);
  }

  test_float();
  test_struct_low_address_range();
  test_struct_high_address_range();
}


void loop()
{
}


//  -- END OF FILE --
