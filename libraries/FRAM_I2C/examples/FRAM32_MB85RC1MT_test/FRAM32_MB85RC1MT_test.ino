//
//    FILE: FRAM32_MB85RC1MT_test.ino
//  AUTHOR: mbmorrissey
// PURPOSE: test MB85RC1MT FRAM (32 bits addressing)
//     URL: https://github.com/RobTillaart/FRAM_I2C


#include "FRAM.h"

FRAM32 fram;


uint32_t sizeInBytes = 0;
byte testval = 0;

void setup()
{

  Serial.begin(9600);
  Wire.begin();
  delay(400);

  int rv = fram.begin(0x50);
  if (rv != 0)
  {
    Serial.print("INIT ERROR: ");
    Serial.println(rv);
  }

  Serial.println();
  Serial.println(__FUNCTION__);

  Serial.print("ManufacturerID: ");
  Serial.println(fram.getManufacturerID());
  Serial.print("     ProductID: ");
  Serial.println(fram.getProductID());
  Serial.print("    memory size: ");
  Serial.println(fram.getSize());

  Serial.println("***************");

  byte test;

  delay(50);
  Serial.println("writing 1 to memory location 1");
  fram.write8(1, 1);

  delay(50);
  Serial.println("reading from memory location 1");
  test =  fram.read8(1);
  Serial.println(test);

  delay(50);
  Serial.println("writing 2 to memory location 65537");
  fram.write8(65537, 2);

  delay(50);
  Serial.println("reading from memory location 65537");
  test =  fram.read8(65537);
  Serial.println(test);

  delay(50);
  Serial.println("reading from memory location 1");
  test =  fram.read8(1);
  Serial.println(test);

}

void loop() 
{
}


//  -- END OF FILE --

