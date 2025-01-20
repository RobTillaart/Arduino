//
//    FILE: AD5593R_AD5593R_test_adc.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test adc mode
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x08);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5593R_LIB_VERSION: ");
  Serial.println(AD5593R_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  set all eight pins to ADC mode.
  AD.setADCmode(0xFF);
}


void loop()
{
  for (int pin = 0; pin < 8; pin++)
  {
    Serial.print(AD.readADC(pin));
    Serial.print("\t");
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
