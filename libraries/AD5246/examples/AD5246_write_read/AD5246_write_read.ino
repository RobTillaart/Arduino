//
//    FILE: AD5246_write_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AD5246 demo program
//     URL: https://github.com/RobTillaart/AD5246


#include "AD5246.h"


AD5246 AD;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5246_LIB_VERSION: ");
  Serial.println(AD5246_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

  bool b = AD.begin();
  Serial.println(b ? "true" : "false");
  Serial.println(AD.isConnected());
}


void loop()
{
  Serial.println("\nwrite\tread\treadBack");
  for (int val = 0; val < 128; val++)
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
