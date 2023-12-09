//
//    FILE: SHT31_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo  (needs 0.2.4 or up)
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT31 sht;  //  use default address and Wire

uint32_t connectionFails = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
}


void loop()
{
  if ( sht.isConnected()  )
  {
    start = micros();
    bool b = sht.read();         //  default = true/fast       slow = false
    stop = micros();

    int error = sht.getError();
    uint16_t stat = sht.readStatus();

    Serial.print(millis());
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(b, HEX);
    Serial.print("\t");
    Serial.print(error, HEX);
    Serial.print("\t");
    Serial.print(stat, HEX);
    Serial.print("\t");
    Serial.print(sht.getTemperature(), 1);
    Serial.print("\t");
    Serial.print(sht.getHumidity(), 1);
  }
  else
  {
    connectionFails++;
    Serial.print(millis());
    Serial.print("\tNot connected:\t");
    Serial.print(connectionFails);
    // sht.reset();
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --

