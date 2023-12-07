//
//    FILE: SHT2x_heater.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo heater functions
//     URL: https://github.com/RobTillaart/SHT2x


// WARNING: NOT TESTED FOR SHT2x - UNDER DEVELOPMENT


#include "Wire.h"
#include "SHT2x.h"

SHT2x sht;
uint8_t status;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  //  heater timeout 30 seconds, just for demo.
  sht.setHeatTimeout(30);

  status = sht.getStatus();
  printHeaterStatus(status);

  sht.heatOn();

  while (sht.isHeaterOn())
  {
    status = sht.getStatus();
    printHeaterStatus(status);
    sht.read();
    Serial.println(sht.getTemperature());
    delay(10000);
  }

  Serial.println("switched off");
}


void loop()
{
  //  forced switch off
  sht.heatOff();
  delay(1000);
}


void printHeaterStatus(uint8_t status)
{
  Serial.print(millis());
  Serial.print("\tHEATER: ");
  if (status == 0x00)          //  TODO - elaborate
  {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}


//  -- END OF FILE --
