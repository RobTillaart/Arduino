//
//    FILE: BL0940_SPI_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0940_SPI


#include "BL0940_SPI.h"


// BL0940_SPI mySensor();  //  HW SPI default
BL0940_SPI mySensor(5, 6, 7);


uint32_t start, stop;
static float f;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0940_SPI_LIB_VERSION: ");
  Serial.println(BL0940_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  numbers from the BL0940 APP NOTE
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;

  delay(100);
  start = micros();
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.
  stop = micros();
  Serial.print("CALIBRATE: \t");
  Serial.println(stop - start);

  delay(100);
  start = micros();
  f = mySensor.getIWave();
  stop = micros();
  Serial.print("RW REGISTER: \t");  //  all register calls are 48 bits.
  Serial.println(stop - start);

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --
