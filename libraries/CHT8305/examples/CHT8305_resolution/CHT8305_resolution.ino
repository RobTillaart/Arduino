//
//    FILE: CHT8305_resolution.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8305 I2C humidity & temperature sensor
//

//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8305  |   CHECK DATASHEET.
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |   ? depends on address to select
//          |               |
//  IRQ ----| ALERT         |   only if enabled.
//          +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE


#include "CHT8305.h"

CHT8305 CHT;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);

  CHT.begin(0x40);   //  CHT8305_DEFAULT_ADDRESS = 0x40
  Wire.setClock(400000);

  delay(1000);

  CHT.setConversionDelay(10);  //  
  
  CHT.setTemperatureResolution(0);  //  14 bit
  CHT.setHumidityResolution(0);     //  14 bit
  CHT.read();
  Serial.print("T11 H14");
  Serial.print('\t');
  Serial.print(CHT.getHumidity());
  Serial.print('\t');
  Serial.println(CHT.getTemperature());
  delay(1000);


  CHT.setTemperatureResolution(1);  //  11 bit
  CHT.setHumidityResolution(0);     //  14 bit
  CHT.read();
  Serial.print("T11 H14");
  Serial.print('\t');
  Serial.print(CHT.getHumidity());
  Serial.print('\t');
  Serial.println(CHT.getTemperature());
  delay(1000);


  CHT.setTemperatureResolution(0);  //  14 bit
  CHT.setHumidityResolution(1);     //  11 bit
  CHT.read();
  Serial.print("T14 H11");
  Serial.print('\t');
  Serial.print(CHT.getHumidity());
  Serial.print('\t');
  Serial.println(CHT.getTemperature());
  delay(1000);


  CHT.setTemperatureResolution(0);  //  14 bit
  CHT.setHumidityResolution(2);     //  08 bit
  CHT.read();
  Serial.print("T14 H08");
  Serial.print('\t');
  Serial.print(CHT.getHumidity());
  Serial.print('\t');
  Serial.println(CHT.getTemperature());
  delay(1000);


  CHT.setTemperatureResolution(1);  //  11 bit
  CHT.setHumidityResolution(2);     //  08 bit
  CHT.read();
  Serial.print("T11 H08");
  Serial.print('\t');
  Serial.print(CHT.getHumidity());
  Serial.print('\t');
  Serial.println(CHT.getTemperature());

}


void loop()
{

}


// -- END OF FILE --
