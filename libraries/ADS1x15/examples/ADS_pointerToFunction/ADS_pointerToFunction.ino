//    FILE: ADS_pointerToFunction.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: replace internal ADC with external ADC by using pointer to function
//     URL: https://github.com/RobTillaart/ADS1X15
//
//  WARNING ONLY TESTED ON AVR


#include "Arduino.h"
#include "ADS1X15.h"

//  adjust address if needed
ADS1115 ADS(0x48);  

//  pointer to ADC function
int (*readADC)(uint8_t);  


void setup() 
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(100000);

  ADS.begin();  //  use defaults
  
  readADC = analogRead;  //  start with internal 
}


void loop()
{
  delay(500);
  int x = readADC(1);
  Serial.println(x);
  if (millis() > 5000) readADC = wrapper;
}

//  wrapper takes care 
int wrapper(uint8_t x)
{
  return ADS.readADC(x);
}



//  -- END OF FILE --
