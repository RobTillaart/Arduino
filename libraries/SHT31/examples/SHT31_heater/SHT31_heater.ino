//
//    FILE: SHT31_heater.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo heater functions
//     URL: https://github.com/RobTillaart/SHT31

#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

SHT31 sht;
uint16_t status;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(SHT31_ADDRESS);
  Wire.setClock(100000);

  sht.setHeatTimeout(30);  // heater timeout 30 seconds, just for demo.

  status = sht.readStatus();
  printHeaterStatus(status);

  sht.heatOn();

  while (sht.isHeaterOn())
  {
    status = sht.readStatus();
    printHeaterStatus(status);
    sht.read();
    Serial.println(sht.getTemperature());
    delay(10000);
  }

  Serial.println("switched off");
}

void loop()
{
  // forced switch off
  if (status & SHT31_STATUS_HEATER_ON) sht.heatOff();
}


void printHeaterStatus(uint16_t status)
{
  Serial.print(millis());
  Serial.print("\tHEATER: ");
  if (status & SHT31_STATUS_HEATER_ON)
  {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}

// -- END OF FILE --
