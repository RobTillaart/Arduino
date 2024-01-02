//
//    FILE: ADS_1114_four.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: demo reading four ADS1114 modules in parallel
//     URL: https://github.com/RobTillaart/ADS1X15


// Note all IO with the sensors are guarded by an isConnected()
// this is max robust, in non critical application one may either
// cache the value or only verify it in setup (least robust).
// Less robust may cause the application to hang - watchdog reset ?


#include "ADS1X15.h"


ADS1114 ADS[4];
uint16_t val[4];

uint32_t last = 0, now = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t address = 0x48 + i;
    ADS[i] = ADS1114(address);

    Serial.print(address, HEX);
    Serial.print("  ");
    Serial.println(ADS[i].begin() ? "connected" : "not connected");

    //  0 = slow   4 = medium   7 = fast, but more noise
    ADS[i].setDataRate(4);
  }
  ADS_request_all();
}


void loop()
{
  //  Serial.println(__FUNCTION__);
  //  wait until all is read...
  while(ADS_read_all());

  //  we have all values, so process (print) them
  ADS_print_all();

  //  wait a second, comment this line for more samples.
  delay(1000);
  ADS_request_all();
}


void ADS_request_all()
{
  //  Serial.println(__FUNCTION__);
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected()) ADS[i].requestADC(0);
    //  get them evenly spaced in time ...
    delayMicroseconds(200);
  }
}


bool ADS_read_all()
{
  //  Serial.println(__FUNCTION__);
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected() && ADS[i].isBusy()) return true;
  }
  //  Serial.print("IDX:\t");
  //  Serial.println(idx);
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected())
    {
      val[i] = ADS[i].getValue();
    }
  }
  ADS_request_all();
  return false;
}


void ADS_print_all()
{
  //  Serial.println(__FUNCTION__);
  //  print duration since last print.
  now = millis();
  Serial.print(now - last);
  last = now;
  Serial.println();

  //  PRINT ALL VALUES
  for (int i = 0; i < 4; i++)
  {
    Serial.print(val[i]);
    Serial.print("\t");
  }
  Serial.println();
}


//  -- END OF FILE --
