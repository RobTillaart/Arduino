//
//    FILE: SWSO_ESP32_listener.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: SWSO demo for ESP32
//     URL: https://github.com/RobTillaart/SWSerialOut
//
//  Serial2.RX listens to an SWSO


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
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
