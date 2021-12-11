//
//    FILE: ADS_async_16_channel.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo reading four ADS1115 modules in parallel
//    DATE: 2021-07-06
//     URL: https://github.com/RobTillaart/ADS1X15


// Note all IO with the sensors are guarded by an isConnected()
// this is max robust, in non critical application one may either
// cache the value or only verify it in setup (least robust).
// Less robust may cause the application to hang - watchdog reset ?


#include "ADS1X15.h"


ADS1115 ADS[4];
uint16_t val[16];
int idx = 0;

uint32_t last = 0, now = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t address = 0x48 + i;
    ADS[i] = ADS1115(address);

    Serial.print(address, HEX);
    Serial.print("  ");
    Serial.println(ADS[i].begin() ? "connected" : "not connected");

    ADS[i].setDataRate(4);  // 7 is fastest, but more noise
  }
  ADS_request_all();
}


void loop()
{
  // Serial.println(__FUNCTION__);
  // wait until all is read...
  while (ADS_read_all());

  // we have all values
  ADS_print_all();

  delay(1000);      // wait a second.
  ADS_request_all();
}


void ADS_request_all()
{
  //  Serial.println(__FUNCTION__);
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected()) ADS[i].requestADC(idx);
  }
}


bool ADS_read_all()
{
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected() && ADS[i].isBusy()) return true;
  }
  // Serial.print("IDX:\t");
  // Serial.println(idx);
  for (int i = 0; i < 4; i++)
  {
    if (ADS[i].isConnected())
    {
      val[i * 4 + idx] = ADS[i].getValue();
    }
  }
  idx++;
  if (idx < 4)
  {
    ADS_request_all();
    return true;
  }
  idx = 0;
  return false;
}


void ADS_print_all()
{
  // Serial.println(__FUNCTION__);
  // TIMESTAMP
  now = millis();
  Serial.print(now - last);
  last = now;
  Serial.println();

  // PRINT ALL VALUES
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      Serial.print(val[j * 4 + i]);
      Serial.print("\t");
    }
    Serial.println();
  }
  Serial.println();
}


// -- END OF FILE --

