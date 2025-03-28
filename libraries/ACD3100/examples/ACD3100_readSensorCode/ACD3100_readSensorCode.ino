//
//    FILE: ACD3100_readSensorCode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD3100


#include "ACD3100.h"


ACD3100 mySensor;
char FWversion[12];
char sensorCode[12];

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD3100_LIB_VERSION: ");
  Serial.println(ACD3100_LIB_VERSION);

  Wire.begin();
  mySensor.begin();

  mySensor.readFirmwareVersion(&FWversion[0]);
  Serial.print("FIRMWARE: \t");
  Serial.println(FWversion);
  
  mySensor.readSensorCode(&sensorCode[0]);
  Serial.print("SENSORCODE: \t");
  Serial.println(sensorCode);
}


void loop()
{

}


//  -- END OF FILE --
