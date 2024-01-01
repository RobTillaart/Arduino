//
//    FILE: TCA9548_demo_SGP30.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548
//     URL: https://github.com/RobTillaart/SGP30


#include "SGP30.h"
#include "TCA9548.h"

PCA9546 MP(0x70);
uint8_t channels = 0;

SGP30 living;    //  channel 0
SGP30 kitchen;   //  channel 1
SGP30 outside;   //  channel 2

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9548_LIB_VERSION: ");
  Serial.println(TCA9548_LIB_VERSION);
  Serial.print("SGP30_LIB_VERSION: ");
  Serial.println(SGP30_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  initialize multiplexer
  if (MP.begin() == false)
  {
    Serial.println("Multiplexer error");
  }
  channels = MP.channelCount();

  //  initialize the temperature sensors
  MP.selectChannel(0);
  if (living.begin() == false)
  {
    Serial.println("living error");
  }
  MP.selectChannel(1);
  if (kitchen.begin() == false )
  {
    Serial.println("kitchen error");
  }
  MP.selectChannel(2);
  if (outside.begin() == false )
  {
    Serial.println("outside error");
  }
}


void loop()
{
  if ((millis() - lastTime) > 5000)
  {
    lastTime = millis();
   
    MP.selectChannel(0);
    living.read();
    Serial.print(living.getCO2(), 1);
    Serial.print("\t");
    
    MP.selectChannel(1);
    kitchen.read();
    Serial.print(kitchen.getCO2(), 1);
    Serial.print("\t");
  
    MP.selectChannel(2);
    outside.read();
    Serial.print(outside.getCO2(), 1);
    Serial.print("\n");
  }
}


//  -- END OF FILE --
