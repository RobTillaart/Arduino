//
//    FILE: ADS_read_getError.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs and check for error.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).


#include "ADS1X15.h"

ADS1115 ADS(0x48);

int16_t value[4];
int err = ADS1X15_OK;
float voltageFactor = 1;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);
  Serial.println();

  Wire.begin();
  ADS.begin();

  voltageFactor = ADS.toVoltage(1);
}


void loop()
{
  ADS.setGain(0);

  float f = ADS.toVoltage(1);  //  voltage factor

  for (int channel = 0; channel < 4; channel++)
  {
    value[channel] = ADS.readADC(channel);
    err = ADS.getError();
    if (err != ADS1X15_OK)
    {
      Serial.print(channel);
      Serial.print(" returns error: ");
      Serial.println(err);
    }

    Serial.print("\tChannel ");
    Serial.print(channel);
    Serial.print(": ");
    Serial.print(value[channel]);
    Serial.print('\t');
    Serial.println(value[channel] * voltageFactor, 3);
  }

  //  optional do other things with value[channel]

  delay(1000);
}


//  -- END OF FILE --
