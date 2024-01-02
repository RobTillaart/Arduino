//
//    FILE: ADS_continuous.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog input
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).
//
//  See https://github.com/RobTillaart/ADS1X15/issues/49
//

#include "ADS1X15.h"


//  choose your sensor
//  ADS1013 ADS(0x48);
//  ADS1014 ADS(0x48);
//  ADS1015 ADS(0x48);
//  ADS1113 ADS(0x48);
//  ADS1114 ADS(0x48);
ADS1115 ADS(0x48);

uint16_t count = 0;
uint16_t value = 0;
uint16_t prev  = 0;
uint32_t lastTime = 0;
uint32_t lastSample = 0;


void setup()
{
  Serial.begin(500000);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();
  ADS.setGain(0);      //  6.144 volt
  ADS.setDataRate(7);  //  0 = slow   4 = medium   7 = fast
  ADS.setMode(0);      //  continuous mode
  ADS.readADC(0);      //  first read to trigger
}


void loop()
{
  uint32_t now = micros();
  if (now - lastSample >= 1160)   //  almost exact 860 SPS
  {
    lastSample = now;
    value = ADS.getValue();
    count++;
    Serial.print(count);
    Serial.print("\t");
    Serial.println(value);
  }
  if (now - 1000000 >= lastTime)
  {
    lastTime = now;
    count = 0;
  }
}


//  -- END OF FILE --

