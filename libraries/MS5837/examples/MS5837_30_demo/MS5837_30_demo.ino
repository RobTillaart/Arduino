//    FILE: MS5837_30_demo.ino
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
  if (MS.begin(0) == true)
  {
    Serial.println("MS5837 found.");
  }
  else
  {
    Serial.println("MS5837 not found. halt.");
    // while (1);
  }
  Serial.println();
}


void loop()
{
  if (MS.read(8) != 0)
  {
    Serial.print("Read Error!!\t");
  }
  Serial.print("\tT: ");
  Serial.print(MS.getTemperature(), 2);
  Serial.print("\tP: ");
  Serial.print(MS.getPressure(), 2);
  Serial.print("\tA: ");
  Serial.print(MS.getAltitude(), 2);
  Serial.print("\tD: ");
  Serial.print(MS.getDepth(), 2);
  Serial.print("\tE: ");
  Serial.print(MS.getLastError());
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
