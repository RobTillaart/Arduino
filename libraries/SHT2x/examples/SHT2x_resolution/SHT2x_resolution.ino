//
//    FILE: SHT2x_resolution.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo resolution and battery
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

uint32_t start, stop;

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  uint8_t stat = sht.getStatus();
  Serial.print("STAT:\t");
  Serial.print(stat, HEX);
  Serial.println();

  Serial.print("BATT:\t");
  Serial.print(sht.batteryOK() ? "OK" : "FAIL");
  Serial.println();

  for (uint8_t res = 0; res < 4; res++)
  {
    for (uint8_t times = 0; times < 5; times++)
    {
      sht.setResolution(res);
      Serial.print("RES:\t");
      Serial.print(sht.getResolution());
      delay(100);

      start = micros();
      sht.read();
      stop = micros();

      Serial.print("\t");
      Serial.print(stop - start);
      Serial.print("\t");
      Serial.print(sht.getTemperature(), 3);
      Serial.print("\t");
      Serial.println(sht.getHumidity(), 3);
      delay(3000);
    }
  }
  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
