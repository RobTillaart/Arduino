//
//    FILE: AM2320_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo sketch for AM2320 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0 - 2017-12-11 initial version
//
// Released to the public domain
//

#include <AM232X.h>

AM232X AM2320;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  AM2320.read();
  
  // sensor only returns one decimal.
  Serial.print("Temp:\t");
  Serial.println(AM2320.temperature, 1);
  Serial.print("Hum:\t");
  Serial.println(AM2320.humidity, 1);
  
  Serial.print("Model:\t");
  Serial.println(AM2320.getModel());
  Serial.print("Version:\t");
  Serial.println(AM2320.getVersion());
  Serial.print("DevId:\t");
  Serial.println(AM2320.getDeviceID());
  
  Serial.print("Status:\t");
  Serial.println(AM2320.getStatus());
  Serial.print("UserA:\t");
  Serial.println(AM2320.getUserRegisterA());
  Serial.print("UserB:\t");
  Serial.println(AM2320.getUserRegisterB());

  Serial.println("done...");
}

void loop()
{
}

//
// END OF FILE
//