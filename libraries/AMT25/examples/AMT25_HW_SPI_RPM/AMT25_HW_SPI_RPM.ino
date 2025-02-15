//
//    FILE: AMT25_HW_SPI_RPM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo RPM.
//     URL: https://github.com/RobTillaart/AMT25
//

#include "AMT25.h"

AMT25 re(9);  //  hardware SPI

uint32_t  lastDisplay = 0;
int16_t   position = 0;
int16_t   previous = 0;
float     RPM = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AMT25_LIB_VERSION: ");
  Serial.println(AMT25_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin(14);
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
