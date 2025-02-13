//
//    FILE: DAC53001_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DAC53001
//


#include "DAC53001.h"

DAC53001 dac(0x30);  //  default Wire

uint16_t value = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DAC53001_LIB_VERSION: ");
  Serial.println(DAC53001_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = dac.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  Serial.print("ADDRESS:\t");
  Serial.println(dac.getAddress());
  Serial.print("MAXVALUE:\t");
  Serial.println(dac.getMaxValue());
  Serial.print("CHANNELS:\t");
  Serial.println(dac.getChannels());
  
  Serial.print("VREF:\t");
  Serial.println(dac.getReference());
  Serial.print("OUTPUT:\t");
  Serial.println(dac.getOutputMode());
  
  Serial.print("STATUS:\t");
  Serial.println(dac.getStatus());
  Serial.print("DEVID:\t");
  Serial.println(dac.getDeviceID());
  Serial.print("VERSION:\t");
  Serial.println(dac.getVersionID());
  
  Serial.print("GETDAC:\t");
  Serial.println(dac.getDAC());
  
  Serial.print("ERROR:\t");
  Serial.println(dac.lastError());
  
}


void loop()
{

}


//  -- END OF FILE --
