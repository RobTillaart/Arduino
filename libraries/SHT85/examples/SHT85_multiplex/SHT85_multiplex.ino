//
//    FILE: SHT85_multiplex.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT85
//
// TOPVIEW SHT85  (check datasheet)
//            +-------+
// +-----\    | SDA 4 -----
// | +-+  ----+ GND 3 -----
// | +-+  ----+ +5V 2 -----
// +-----/    | SCL 1 -----
//            +-------+

//  TODO: test with hardware

#include "SHT85.h"
#include "TCA9548.h"

TCA9548 MP(0x70);

#define SHT85_ADDRESS   0x44

SHT85 sht(SHT85_ADDRESS);  //  the object is reused in the multiplexing.

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9548_LIB_VERSION: \t");
  Serial.println(TCA9548_LIB_VERSION);
  Serial.print("SHT_LIB_VERSION: \t");
  Serial.println(SHT_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);

  if (MP.begin() == false)
  {
    Serial.println("Error: Could not connect to the multiplexer.");
    while (1);
  }

  //  initialize 4 SHT85's
  for (int channel = 0; channel < 4; channel++)
  {
    Serial.print(channel);
    MP.selectChannel(channel);  //  rotate over all SHT85's
    if (sht.begin() == false)
    {
      Serial.println("\tconnect error.");;
    }
    else 
    {
      Serial.println("\tOK!.");;
    }
    delay(10);
  }

  Serial.println();
}


void loop()
{
  Serial.print(millis());
  Serial.print("\t");
  for (int channel = 0; channel < 4; channel++)
  {
    sht.read();         //  default = true/fast       slow = false
    Serial.print(sht.getTemperature(), 1);
    Serial.print("\t");
    Serial.print(sht.getHumidity(), 1);
    delay(100);
  }
}


//  -- END OF FILE --
