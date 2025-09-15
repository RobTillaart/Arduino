//
//    FILE: SWSO_ESP32_listener.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: SWSO demo for ESP32 - echo incoming data
//     URL: https://github.com/RobTillaart/SWSerialOut
//
//  Serial2.RX listens to an SWSO


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  //  Serial.print("SWSERIALOUT_LIB_VERSION: ");
  //  Serial.println(SWSERIALOUT_LIB_VERSION);
  Serial.println();

  Serial2.begin(38400);
}


void loop()
{
  //  echo incoming data
  while (Serial2.available())
  {
    Serial.print((char)Serial2.read());
  }
  Serial.println();
  delay(200);
}


//  -- END OF FILE --
