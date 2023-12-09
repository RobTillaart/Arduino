//
//    FILE: SHT31_two_I2C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT31
//
//   NOTE: see issue #22 for details
//         originally written for a ATSAMD21G18A custom board.
//         edited for a board (e.g. ESP32) that has Wire and Wire1 (compiles, not tested)


#include "Wire.h"
#include "SHT31.h"


TwoWire myWire(&sercom5, 0, 1);
//  TwoWire myWire = Wire1;


SHT31 sht[4] = {
  SHT31(0x44, &Wire), 
  SHT31(0x45, &Wire), 
  SHT31(0x44, &myWire), 
  SHT31(0x45, &myWire) 
};

bool b[4];


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  myWire.begin();
  myWire.setClock(100000);

  //  see datasheet for details
  pinPeripheral(0, PIO_SERCOM_ALT);
  pinPeripheral(1, PIO_SERCOM_ALT);

  //  show they are connected
  Serial.print("BEGIN:\t");
  for (uint8_t i = 0; i < 4; i++)
  {
    b[i] = sht[i].begin();
    Serial.print(b[i]);
    Serial.print("\t");
  }
  Serial.println();
}


void loop()
{
  //  read all that are found
  for (uint8_t i = 0; i < 4; i++)
  {
    if (b[i]) sht[i].read();
  }

  for (uint8_t i = 0; i < 4; i++)
  {
    Serial.print(sht[i].getTemperature(), 1);
    Serial.print("\t");
  }
  for (uint8_t i = 0; i < 4; i++)
  {
    Serial.print(sht[i].getHumidity(), 1);
    Serial.print("\t");
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
