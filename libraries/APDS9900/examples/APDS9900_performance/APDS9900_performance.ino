//
//    FILE: APDS9900_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/APDS9900


#include "APDS9900.h"
#include "Wire.h"

APDS9900 apds;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("APDS9900_LIB_VERSION: ");
  Serial.println(APDS9900_LIB_VERSION);
  Serial.println();

  Wire.begin();
  apds.begin();

  delay(12);  //  page 14

  //  dump default settings
  Serial.print("Address:\t");
  Serial.println(apds.getAddress(), HEX);   //  0x39 (57)
  Serial.print("Connected:\t");
  Serial.println(apds.isConnected(), HEX);  //  0x01
  Serial.print("Revision:\t");
  Serial.println(apds.getRevision(), HEX);  //  0x01
  Serial.print("DeviceID:\t");
  Serial.println(apds.getDeviceID(), HEX);  //  0x29 (41)
  Serial.print("  Status:\t");
  Serial.println(apds.getStatus(), HEX);    //  ??
  Serial.println();

  for (uint32_t speed = 100000; speed <= 800000; speed += 100000)
  {
    Serial.println();
    Serial.println();
    test(speed);
  }

  Serial.println("\ndone...");
}


void test(uint32_t speed)
{
  uint32_t start, stop;
  uint16_t x;
  Wire.setClock(speed);
  Serial.print("clock:\t");
  Serial.println(speed);

  delay(100);
  start = micros();
  x = apds.getALS_CDATA();
  stop = micros();
  Serial.print("ALS_CDATA:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x);

  delay(100);
  start = micros();
  x = apds.getALS_IRDATA();
  stop = micros();
  Serial.print("ALS_IRDATA:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x);

  delay(100);
  start = micros();
  x = apds.getPROX_DATA();
  stop = micros();
  Serial.print("PROX_DATA:\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x);

  delay(100);
  start = micros();
  float f = apds.getLux();
  stop = micros();
  Serial.print("LUX:\t\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(f);
}

void loop()
{
}


//  -- END OF FILE --
