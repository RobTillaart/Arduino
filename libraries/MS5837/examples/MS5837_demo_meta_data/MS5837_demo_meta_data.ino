//    FILE: MS5837_demo_meta_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MS5837 library
//     URL: https://github.com/RobTillaart/MS5837

/*  AVR I2C codes
  |     0  |  success
  |     1  |  length to long for buffer
  |     2  |  address send, NACK received
  |     3  |  data send, NACK received
  |     4  |  other twi error
  |     5  |  timeout
*/


#include "Arduino.h"
#include "Wire.h"

#include "MS5837.h"

MS5837 MS(&Wire);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5837_LIB_VERSION: ");
  Serial.println(MS5837_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  MS5837_30 = 0
  //  MS5837_02 = 1
  if (MS.begin(1) == true)
  {
    Serial.println("MS5837 found.");
  }
  else
  {
    Serial.println("MS5837 not found. halt.");
    // while (1);
  }
  Serial.println(MS.getCRC());
  Serial.println(MS.getLastError());
  Serial.println(MS.getProduct());
  Serial.println(MS.getLastError());
  Serial.println(MS.getFactorySettings());
  Serial.println(MS.getLastError());
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
