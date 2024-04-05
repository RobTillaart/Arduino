//
//    FILE: AM2320_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch for AM2320 I2C humidity & temperature sensor
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
//  do not forget pull up resistors between SDA, SCL and VDD.


#include "AM232X.h"

AM232X AM2320;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (! AM2320.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }
  AM2320.wakeUp();
  delay(2000);

  //  sensor only returns one decimal.
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
  Serial.print("Temperature:\t");
  Serial.println(AM2320.getTemperature(), 1);
  Serial.print("   Humidity:\t");
  Serial.println(AM2320.getHumidity(), 1);

  Serial.println();
  Serial.println("GET SENSOR INFO (experimental)");
  Serial.print("  Model:\t");
  Serial.println(AM2320.getModel());
  Serial.print("Version:\t");
  Serial.println(AM2320.getVersion());
  Serial.print("  DevId:\t");
  Serial.println(AM2320.getDeviceID());

  Serial.println();
  Serial.println("GET REGISTERS (experimental)");
  Serial.print(" Status:\t");
  Serial.println(AM2320.getStatus());
  Serial.print("  UserA:\t");
  Serial.println(AM2320.getUserRegisterA());
  Serial.print("  UserB:\t");
  Serial.println(AM2320.getUserRegisterB());

  Serial.println();
  Serial.println("SET REGISTERS (experimental)");
  AM2320.setStatus(42);
  Serial.print("Status   42  ==> ");
  Serial.println(AM2320.getStatus());
  AM2320.setUserRegisterA(1234);
  Serial.print("UserA   1234 ==> ");
  Serial.println(AM2320.getUserRegisterA());
  AM2320.setUserRegisterB(5678);
  Serial.print("UserB   5678 ==> ");
  Serial.println(AM2320.getUserRegisterB());

  Serial.println("done...\n");
}


void loop()
{
  delay(2000);

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
}


//  -- END OF FILE --
