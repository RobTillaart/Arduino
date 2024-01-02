//
//    FILE: ADS_differential.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read differential
//     URL: https://github.com/RobTillaart/ADS1X15

//  test 1
//  connect 2 potmeters in series
//
//  GND ---[   x   ]------[   y   ]---- 5V
//             |              |
//
//  measure at x and y  (connect to AIN0 and AIN1). 
//  x should be lower or equal to y

//  test 2
//  connect 2 potmeters parallel
//
//  GND ---[   x   ]------ 5V
//             |
//
//  GND ---[   y   ]------ 5V
//             |
//
//  measure at x and y  (connect to AIN0 and AIN1).
//  range from -VDD .. +VDD are possible


#include <ADS1X15.h>

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();
  ADS.setGain(0);
}


void loop() 
{
  int16_t val_01 = ADS.readADC_Differential_0_1();  
  int16_t val_03 = ADS.readADC_Differential_0_3();  
  int16_t val_13 = ADS.readADC_Differential_1_3();  
  int16_t val_23 = ADS.readADC_Differential_2_3(); 
  float volts_01 = ADS.toVoltage(val_01); 
  float volts_03 = ADS.toVoltage(val_03); 
  float volts_13 = ADS.toVoltage(val_13); 
  float volts_23 = ADS.toVoltage(val_23); 

  Serial.print("\tval_01: "); Serial.print(val_01); Serial.print("\t"); Serial.println(volts_01, 3);
  Serial.print("\tval_03: "); Serial.print(val_03); Serial.print("\t"); Serial.println(volts_03, 3);
  Serial.print("\tval_13: "); Serial.print(val_13); Serial.print("\t"); Serial.println(volts_13, 3);
  Serial.print("\tval_23: "); Serial.print(val_23); Serial.print("\t"); Serial.println(volts_23, 3);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

