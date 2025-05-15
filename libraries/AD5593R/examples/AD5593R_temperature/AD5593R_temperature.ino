//
//    FILE: AD5593R_temperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test reading temperature
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x10);


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5593R_LIB_VERSION: ");
  Serial.println(AD5593R_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.print("Connect: ");
  Serial.println(AD.isConnected());
  Serial.print("Address: ");
  Serial.println(AD.getAddress(), HEX);

  //  use internal Vref 2.5V
  AD.setExternalReference(false, 5.0);

  Serial.println("TEMPERATURE");
}


void loop()
{
  //  RAW temperature
  //  Serial.print(AD.readADC(8));
  //  Serial.print("\t");
  Serial.println(AD.readTemperature());
  delay(1000);
}


//  -- END OF FILE --
