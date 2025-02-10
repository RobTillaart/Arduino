//
//    FILE: ERCFS_HW_SPI_RPM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo RPM.
//     URL: https://github.com/RobTillaart/ERCFS
//

#include "ERCFS.h"

ERCFS re(9);  //  hardware SPI

uint32_t  lastDisplay = 0;
int16_t   position = 0;
int16_t   previous = 0;
float     RPM = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ERCFS_LIB_VERSION: ");
  Serial.println(ERCFS_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  previous = re.getRawValue();
}


void loop()
{
  uint32_t duration = micros() - re.lastRead();
  if (duration >= 20000)
  {
    position = re.getRawValue();
    float delta = abs(position - previous);
    previous = position;
    RPM = (60e6 / 16384) * delta / duration; 
  }
  if (millis() - lastDisplay > 500)
  {
    Serial.println(RPM);
  }
}


//  -- END OF FILE --
