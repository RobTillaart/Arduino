//    FILE: LTC2485_nolib.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: raw read the device
//     URL: https://github.com/RobTillaart/LTC2485


#include "Arduino.h"
#include "Wire.h"


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  Wire.begin();
  delay(200);  //  for first conversion

  for (int del = 200; del > 150; del -= 5)
  {
    Serial.print(del);
    Serial.print("\t");
    Wire.beginTransmission(0x16);    //  address
    Wire.write(0x00);                //  default configuration
    int n = Wire.endTransmission();  //  send configuration over I2C to address
    Serial.print(n);

    delay(del);

    Serial.print("\t");
    n = Wire.requestFrom(0x16, 4);
    Serial.print(n);
    Serial.print("\t");
    Serial.print(Wire.read());
    Serial.print("\t");
    Serial.print(Wire.read());
    Serial.print("\t");
    Serial.print(Wire.read());
    Serial.print("\t");
    Serial.println(Wire.read());
    delay(1000);
  }

  Serial.println("\ndone...");
}


void loop()
{
}

//  -- END OF FILE --
