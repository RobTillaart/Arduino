//
//    FILE: MAX6675_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/MAX6675
//     URL: https://github.com/RobTillaart/MAX6675/issues/11


#include "MAX6675.h"

const int ThermoCouplesNum = 3;
MAX6675 ThermoCouples[ThermoCouplesNum] =
{
  MAX6675(3, &SPI),   //  HW SPI
  MAX6675(4, &SPI),   //  HW SPI
  MAX6675(5, 6, 7)    //  SW SPI
};


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX6675_LIB_VERSION: ");
  Serial.println(MAX6675_LIB_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();

  for (int i = 0; i < ThermoCouplesNum; i++)
  {
    ThermoCouples[i].begin();
    ThermoCouples[i].setSPIspeed(4000000);
  }
}


void loop()
{
  delay(100);

  for (int THCnumber = 0; THCnumber < ThermoCouplesNum; THCnumber++)
  {
    start = micros();
    int status = ThermoCouples[THCnumber].read();
    stop = micros();
    float temp = ThermoCouples[THCnumber].getTemperature();

    Serial.print(millis());
    Serial.print("\tID: ");
    Serial.print(THCnumber);
    Serial.print("\tstatus: ");
    Serial.print(status);
    Serial.print("\ttemp: ");
    Serial.print(temp);
    Serial.print("\tus: ");
    Serial.println(stop - start);

    delay(1000);  //  time to flush all Serial stuff
  }
  Serial.println();
}

//  -- END OF FILE --
