//
//    FILE: AD5245_write_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5245 demo program
//     URL: https://github.com/RobTillaart/AD5245


#include "AD5245.h"


AD5245 AD(0x2C);     //  AD0 == GND


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5245_LIB_VERSION: ");
  Serial.println(AD5245_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);
  
  bool b = AD.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD.isConnected());
}


void loop()
{
  Serial.println("\nwrite\tread\treadBack");
  for (int val = 0; val < 255; val++)
  {
    Serial.print(val);
    AD.write(val);
    delay(100);

    Serial.print('\t');
    Serial.print(AD.read());
    delay(100);

    Serial.print('\t');
    Serial.println(AD.readDevice());
    delay(100);
  }
  delay(1000);
}


//  -- END OF FILE --

