//
//    FILE: CHT832X_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT832X I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT832X

//  Always check datasheet for connections


#include "CHT832X.h"

//  check all valid addresses
//  if not connected ==> fail
CHT832X CHT(0x44);    //  CHT832X_DEFAULT_ADDRESS
CHT832X CHT1(0x45);
CHT832X CHT2(0x46);
CHT832X CHT3(0x47);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print(F("CHT832X_LIB_VERSION: "));
  Serial.println(CHT832X_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  CHT.begin();
  CHT1.begin();
  CHT2.begin();
  CHT3.begin();

  Serial.print("Connect:\t");
  Serial.println(CHT.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT.getManufacturer());
  delay(1000);

  Serial.print("Connect:\t");
  Serial.println(CHT1.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT1.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT1.getManufacturer());
  delay(1000);

  Serial.print("Connect:\t");
  Serial.println(CHT2.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT2.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT2.getManufacturer());
  delay(1000);

  Serial.print("Connect:\t");
  Serial.println(CHT3.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT3.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT3.getManufacturer());
  delay(1000);
}


void loop()
{

}


//  -- END OF FILE --
