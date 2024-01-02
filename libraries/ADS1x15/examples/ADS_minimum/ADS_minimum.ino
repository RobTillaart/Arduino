//
//    FILE: ADS_minimum.ino
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
//  view with Serial Plotter


#include "ADS1X15.h"


// choose your sensor
// ADS1013 ADS(0x48);
// ADS1014 ADS(0x48);
// ADS1015 ADS(0x48);
// ADS1113 ADS(0x48);
// ADS1114 ADS(0x48);

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();
  ADS.setGain(0);  //  6.144 volt
  Serial.println("Voltage");
}


void loop() 
{
  int16_t raw = ADS.readADC(0);
  Serial.println(ADS.toVoltage(raw), 3);
}


//  -- END OF FILE --

