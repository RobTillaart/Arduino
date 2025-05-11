//
//    FILE: SHT31_getSerialNumber.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Serial Number
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT31 sht(SHT31_ADDRESS);  //  uses explicit address


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  uint16_t stat = sht.readStatus();
  Serial.print("STATUS:\t");
  Serial.print(stat, HEX);
  Serial.println();

  delay(100);

  uint32_t sn = 0;
  bool b;

  start = micros();
  b = sht.getSerialNumber(sn, true);
  stop = micros();
  Serial.println("FAST:\ttrue");
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
  Serial.println("FAST:\tfalse");
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
