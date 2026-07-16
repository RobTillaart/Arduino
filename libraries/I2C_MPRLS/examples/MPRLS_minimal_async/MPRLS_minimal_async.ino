//
//    FILE: MPRLS_minimal_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2C_MPRLS


#include "I2C_MPRLS.h"


//  adjust address of sensor if needed
I2C_MPRLS P(0x58);

uint32_t lastRequest = 0;
bool requestPending = false;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_MPRLS_LIB_VERSION: ");
  Serial.println(I2C_MPRLS_LIB_VERSION);
  Serial.println();

  Wire.begin();
  P.begin(16);  //  implicit minPressure of 0
  //  optimistic no error check

}


void loop()
{
  if (millis() - lastRequest >= 5000)
  {
    if (P.request() == I2C_MPRLS_OK)
    {
      lastRequest += 5000;
    }
  }

  if (P.conversionReady())
  {
    Serial.print(millis());
    Serial.print(":\t");
    int err = P.getData();
    if (err == I2C_MPRLS_OK)
    {
      Serial.print("pressure:\t");
      Serial.println(P.getPressure());
    }
    else
    {
      Serial.print("error: ");
      Serial.println(err);
    }
    P.request();  //  request new data
  }
  delay(1000);
}


//  -- END OF FILE --
