//
//    FILE: ADS_RP2040_WIRE1.ino
//  AUTHOR: Rob.Tillaart / Intubun
// PURPOSE: read analog input
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potentiometer
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).


#include "ADS1X15.h"


//  choose your sensor
//  ADS1013 ADS(0x48);
//  ADS1014 ADS(0x48);
//  ADS1015 ADS(0x48);
//  ADS1113 ADS(0x48);
//  ADS1114 ADS(0x48);
ADS1115 ADS(0x48, &Wire1);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  //  SDA (Pin 26), SCL(Pin 27)
  Wire1.begin();
  Wire1.setSDA(26);
  Wire1.setSCL(27);
  
  ADS.begin();
  ADS.setGain(0);      //  6.144 volt
  ADS.setDataRate(7);  //  0 = slow   4 = medium   7 = fast
  ADS.setMode(0);      //  continuous mode
  ADS.readADC(0);      //  first read to trigger
}


void loop()
{
  Serial.println(ADS.getValue());
  //  optional other code here
}


//  -- END OF FILE --
