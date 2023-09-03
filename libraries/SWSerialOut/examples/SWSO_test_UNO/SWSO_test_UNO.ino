//
//    FILE: SWSO_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: HX711 demo
//     URL: https://github.com/RobTillaart/SWSerialOut


#include "SWSerialOut.h"
#include "SoftwareSerial.h"

SWSerialOut SWS(7);
// SoftwareSerial SWS(6, 7);


void setup()
{
  Serial.begin(19200);
  Serial.println(__FILE__);
  Serial.print("SWSERIALOUT_LIB_VERSION: ");
  Serial.println(SWSERIALOUT_LIB_VERSION);
  Serial.println();

  for (uint32_t baud = 19000; baud < 20000; baud += 10)
  {
    SWS.begin(baud);
    Serial.print(baud);
    Serial.print(" ");
    delay(100);
    // SWS.debug();

    SWS.print("Hello world");

    //  echo incoming data
    Serial.print(Serial.available());
    Serial.print("\t");
    while (Serial.available())
    {
      Serial.print((char)Serial.read());
    }
    Serial.println();
    delay(200);
  }


  Serial.println("\nDone...");

}

void loop()
{

}


//  -- END OF FILE --
