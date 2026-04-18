//
//    FILE: FSR40X_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/FSR40X


#include "FSR40X.h"


FSR40X FSR(A0, 5.0, 1023);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSR40X_LIB_VERSION: ");
  Serial.println(FSR40X_LIB_VERSION);
  Serial.println();

  FSR.begin(10000);
}


void loop()
{
  if (FSR.readNewton() > 0)
  {
    Serial.print(FSR.getNewton(), 3);
    Serial.print("\t");
    Serial.print(FSR.getKgf(), 4);
    Serial.print("\t");
    Serial.println(FSR.getLbf(), 4);
  }
  delay(100);
}


//  -- END OF FILE --
