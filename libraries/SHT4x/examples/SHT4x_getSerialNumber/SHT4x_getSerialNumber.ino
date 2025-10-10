//
//    FILE: SHT4x_getSerialNumber.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Serial Number
//     URL: https://github.com/RobTillaart/SHT4x


#include "Wire.h"
#include "SHT4x.h"

#define SHT_DEFAULT_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT4x sht;  //  uses explicit address


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT4x_LIB_VERSION: \t");
  Serial.println(SHT4x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  delay(100);

  uint32_t sn = 0;
  bool b;

  start = micros();
  b = sht.getSerialNumber(sn, true);
  stop = micros();
  Serial.println("CRC Check:\ttrue");
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  if (b)
  {
    Serial.print("SN:\t");
    Serial.println(sn);
  }
  else
  {
    Serial.print("ERROR:\t");
    Serial.println(sht.getError(), HEX);
  }
  delay(100);

  start = micros();
  b = sht.getSerialNumber(sn, false);
  stop = micros();
  Serial.println("CRC Check:\tfalse");
  Serial.print("TIME:\t");
  Serial.println(stop - start);
  if (b)
  {
    Serial.print("SN:\t");
    Serial.println(sn);
  }
  else
  {
    Serial.print("ERROR:\t");
    Serial.println(sht.getError(), HEX);
  }

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
