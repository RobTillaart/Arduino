//
//    FILE: ADS_read_async.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - asynchronous
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).
//


#include "ADS1X15.h"

ADS1115 ADS(0x48);
float f = 0;
int16_t val_0;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);
  delay(100);

  Wire.begin();
  Wire.setClock(100000);

  ADS.begin();
  ADS.setGain(0);
  f = ADS.toVoltage();      //  voltage factor

  start = micros();
  ADS.requestADC(0);
  stop = micros();
  Serial.println(stop - start);
  delay(100);
  while (ADS.isBusy());
  start = micros();
  val_0 = ADS.getValue();
  stop = micros();
  Serial.println(stop - start);
  delay(100);

  ADS.requestADC(0);
}


void loop()
{
  if (ADS.isBusy() == false)
  {
    val_0 = ADS.getValue();
    //  request a new one
    ADS.requestADC(0);
    Serial.print("\tAnalog0: ");
    Serial.print(val_0);
    Serial.print('\t');
    Serial.println(val_0 * f, 3);
  }
  //  simulate other tasks...
  delay(2000);
}


//  -- END OF FILE --

