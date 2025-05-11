//
//    FILE: SHT31_demo_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo for plotter
//     URL: https://github.com/RobTillaart/SHT31


#include "Wire.h"
#include "SHT31.h"

#define SHT31_ADDRESS   0x44

uint32_t start;
uint32_t stop;

SHT31 sht;


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  //  Serial.println();
  //  Serial.println(__FILE__);
  //  Serial.print("SHT31_LIB_VERSION: \t");
  //  Serial.println(SHT31_LIB_VERSION);
  //  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  sht.begin();

  Serial.println("temperature, humidity");
}


void loop()
{
  sht.read(false);         //  default = true/fast       slow = false

  Serial.println(sht.getTemperature(), 2);
//  Serial.print("\t");
//  Serial.println(sht.getHumidity(), 1);
  delay(100);
}


//  -- END OF FILE --
