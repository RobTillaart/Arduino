//
//    FILE: AM2320_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: demo sketch for AM2320 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0   2017-12-11 initial version
// 0.1.1   2017-12-12 added test for set* functions
// 0.1.2   2020-05-03 updated to 0.2.0 version of lib.
// 0.1.3   2021-01-28  added begin() ++

//  Bottom view 
//       +---+
//  VDD  |o  |
//  SDA  |o  |
//  GND  |o  |
//  SCL  |o  |
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.


#include <AM232X.h>

AM232X AM2320;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  if (! AM2320.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }

  // sensor only returns one decimal.
  Serial.println();
  Serial.println("Read:\t");
  int status = AM2320.read();
  switch (status)
  {
  case AM232X_OK:
    Serial.println("OK");
    break;
  default:
    Serial.println(status);
    break;
  }
  Serial.print("Temp:\t");
  Serial.println(AM2320.getTemperature(), 1);
  Serial.print("Hum:\t");
  Serial.println(AM2320.getHumidity(), 1);

  Serial.println();
  Serial.println("GET SENSOR INFO (experimental)");
  Serial.print("Model:\t");
  Serial.println(AM2320.getModel());
  Serial.print("Version:\t");
  Serial.println(AM2320.getVersion());
  Serial.print("DevId:\t");
  Serial.println(AM2320.getDeviceID());

  Serial.println();
  Serial.println("GET REGISTERS (experimental)");
  Serial.print("Status:\t");
  Serial.println(AM2320.getStatus());
  Serial.print("UserA:\t");
  Serial.println(AM2320.getUserRegisterA());
  Serial.print("UserB:\t");
  Serial.println(AM2320.getUserRegisterB());

  Serial.println();
  Serial.println("SET REGISTERS (experimental)");
  AM2320.setStatus(42);
  Serial.print("Status 42 ==> ");
  Serial.println(AM2320.getStatus());
  AM2320.setUserRegisterA(1234);
  Serial.print("UserA 1234 ==> ");
  Serial.println(AM2320.getUserRegisterA());
  AM2320.setUserRegisterB(5678);
  Serial.print("UserB 5678 ==> ");
  Serial.println(AM2320.getUserRegisterB());

  Serial.println("done...");
}


void loop()
{
}

// -- END OF FILE --
