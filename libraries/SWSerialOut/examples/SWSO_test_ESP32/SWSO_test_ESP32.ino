//
//    FILE: SWSO_test_ESP32.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: SWSO demo for ESP32
//     URL: https://github.com/RobTillaart/SWSerialOut
//
//  Connect pin 25 with Serial2.RX to run this program
//  or patch code :)

#include "SWSerialOut.h"

SWSerialOut SWS(25);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SWSERIALOUT_LIB_VERSION: ");
  Serial.println(SWSERIALOUT_LIB_VERSION);
  Serial.println();

  test_short(300);
  test_short(600);
  test_short(1200);
  test_short(2400);
  test_short(4800);
  test_short(7200);
  test_short(9600);
  test_short(19200);
  test_short(38400);
  test_short(57600);
  test_short(76800);  //  fails without pull up
  test_short(100000);
  test_short(125000); //  fails

  Serial.println("\nDone...");
}


void test_short(uint32_t bd)
{
  Serial2.begin(bd);

  SWS.begin(bd);
  Serial.print(bd);
  Serial.print(" ");
  delay(100);

  SWS.print("Hello world");

  //  echo incoming data
  Serial.print(Serial2.available());  //  should be 11
  Serial.print("\t");
  while (Serial2.available())
  {
    Serial.print((char)Serial2.read());
  }
  Serial.println();
  delay(200);
}


void test_scan(uint32_t bd)
{
  Serial2.begin(bd);
  for (uint32_t baud = bd * 0.95; baud < bd * 1.05; baud += bd * 0.01)
  {
    SWS.begin(baud);
    Serial.print(baud);
    Serial.print(" ");
    delay(100);

    SWS.print("Hello world");

    //  echo incoming data
    Serial.print(Serial2.available());  //  should be 11
    Serial.print("\t");
    while (Serial2.available())
    {
      Serial.print((char)Serial2.read());
    }
    Serial.println();
    delay(200);
  }
}




void loop()
{
}


//  -- END OF FILE --
