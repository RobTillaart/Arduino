//
//    FILE: MLX90316_HW_SPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo dump millis + position.
//     URL: https://github.com/RobTillaart/MLX90316
//

#include "MLX90316.h"

MLX90316 re(9);  //  hardware SPI

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MLX90316_LIB_VERSION: ");
  Serial.println(MLX90316_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
}


void loop()
{
  uint16_t position = re.getRawValue();
  Serial.print(millis());
  Serial.print("\t");
  Serial.print(position);
  Serial.print("\t");
  Serial.println(re.getStatus());
  delay(50);
}


//  -- END OF FILE --
