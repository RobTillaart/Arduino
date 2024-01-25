//
//    FILE: ACD10_readSensorCode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor;
char FWversion[12];
char sensorCode[12];

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

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
