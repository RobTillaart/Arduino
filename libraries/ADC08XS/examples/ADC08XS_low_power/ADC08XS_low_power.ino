//
//    FILE: ADC08XS_low_power.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ADC08XS
//
//  to see it work measure current of the sensor.


#include "ADC08XS.h"


ADC084S adc01;        //  use HWSPI


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADC08XS_LIB_VERSION: ");
  Serial.println(ADC08XS_LIB_VERSION);

  SPI.begin();
  adc01.begin(10);
}


void loop()
{
  Serial.println("low power for 15 seconds.");
  adc01.lowPower();
  delay(15000);

  Serial.println("wake up for 15 seconds.");
  if (adc01.isLowPower()) 
  {
    adc01.wakeUp();
  }
  Serial.print("READ: ");
  Serial.println(adc01.read(3));
  delay(15000);
}


//  -- END OF FILE --
