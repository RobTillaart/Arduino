//
//    FILE: SHT31_heater.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.1
// PURPOSE: demo heater functions
//     URL: https://github.com/RobTillaart/SHT31

#include "Wire.h"
#include "SHT31.h"

SHT31 sht;
uint16_t stat;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(0x44);
  Wire.setClock(100000);

  sht.setHeatTimeout(30);  // heater timeout 30 seconds, just for demo.

  stat = sht.readStatus();
  printHeaterStatus(stat);

  sht.heatOn();

  while (sht.heatUp())
  {
    stat = sht.readStatus();
    printHeaterStatus(stat);
    sht.read();
    Serial.println(sht.getTemperature());
    delay(10000);
  }

  Serial.println("switched off");
}

void loop()
{
  // forced switch off
  if (stat & SHT31_STATUS_HEATER_ON) sht.heatOff();
}


void printHeaterStatus(uint16_t stat)
{
  Serial.print(millis());
  Serial.print("\tHEATER: ");
  if (stat & SHT31_STATUS_HEATER_ON)
  {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}

// -- END OF FILE --
