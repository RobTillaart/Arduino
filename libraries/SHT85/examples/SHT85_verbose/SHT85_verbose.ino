//
//    FILE: SHT85_verbose.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verbose example for debugging
//     URL: https://github.com/RobTillaart/SHT85
//
// TOPVIEW SHT85  (check datasheet)
//            +-------+
// +-----\    | SDA 4 -----
// | +-+  ----+ GND 3 -----
// | +-+  ----+ +5V 2 -----
// +-----/    | SCL 1 -----
//            +-------+


#include "SHT85.h"

#define SHT85_ADDRESS         0x44

uint32_t start;
uint32_t stop;
bool b;

SHT85 sht(SHT85_ADDRESS);


void setup()
{
  delay(1000);
  while (!Serial); //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  b = sht.isConnected();
  Serial.print("connect:\t");
  Serial.println(b);
  Serial.print("Error: ");
  Serial.println(sht.getError(), HEX);
  Serial.println();

  int addr = sht.getAddress();
  Serial.print("addr:\t");
  Serial.println(addr);
  Serial.print("Error: ");
  Serial.println(sht.getError(), HEX);
  Serial.println();

  b = sht.begin();
  Serial.print("begin:\t");
  Serial.println(b);
  Serial.print("Error: ");
  Serial.println(sht.getError(), HEX);
  Serial.println();

  uint16_t stat = sht.readStatus();
  Serial.print("Stat:\t");
  Serial.println(stat, HEX);
  Serial.print("Error: ");
  Serial.println(sht.getError(), HEX);
  Serial.println();

  uint32_t ser = 0xFFFFFFFF;
  b = sht.getSerialNumber(ser, true);
  if (b)
  {
    Serial.print("Serial:\t");
    Serial.println(ser, HEX);
    Serial.print("Error: ");
    Serial.println(sht.getError(), HEX);
    Serial.println();
  }
  else
  {
    Serial.println("Error: could not get serial number.");
    Serial.print("Error: ");
    Serial.println(sht.getError(), HEX);
    Serial.println();
  }
  delay(1000);
}


void loop()
{
  start = micros();
  bool b = sht.read();         //  default = fast = true;   slow = false
  stop = micros();
  Serial.print("read:\t");
  Serial.println(b);
  Serial.print("Error: ");
  Serial.println(sht.getError(), HEX);
  Serial.println();

  Serial.print("\t");
  Serial.print((stop - start) * 0.001);
  Serial.print("\t");
  Serial.print(sht.getTemperature(), 1);
  Serial.print("\t");
  Serial.println(sht.getHumidity(), 1);
  delay(1000);
}


//  -- END OF FILE --
