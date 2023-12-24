//    FILE: MS5837_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo MS5837 library
//     URL: https://github.com/RobTillaart/MS5837


#include "Arduino.h"
#include "Wire.h"

#include "MS5837.h"

MS5837 MS(&Wire);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("MS5837_LIB_VERSION: ");
  Serial.println(MS5837_LIB_VERSION);
  Serial.println();

  Wire.begin();
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
  MS.read();           //  note no error checking => "optimistic".
  Serial.print("T:\t");
  Serial.print(MS.getTemperature(), 2);
  Serial.print("\tP:\t");
  Serial.print(MS.getPressure(), 2);
  Serial.print("\tA:\t");
  Serial.print(MS.getAltitude(), 2);
  Serial.print("\tD:\t");
  Serial.print(MS.getDepth(), 2);
  Serial.println();
  delay(10000);
}


//  -- END OF FILE --
