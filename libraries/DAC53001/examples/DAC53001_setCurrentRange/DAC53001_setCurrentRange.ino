//
//    FILE: DAC53001_setCurrentRange.ino
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

  //  setVoltageReference
  dac.setReference(VDD, 0);   //  explicit channel
  dac.setCurrentRange(4, 0);  //  explicit channel

}


void loop()
{
  dac.setDAC(value);
  value++;
  Serial.println(value);
  if (value == 1024) value = 0;
  delay(1000);
}


//  -- END OF FILE --
