//
//    FILE: max44009_test02.ino
//  AUTHOR: Moritz Ulmer
// PURPOSE: demo of max44009 library
//    DATE: 2020-01-19
//     URL: https://github.com/RobTillaart/MAX44009
//
//    NOTE: To select the alternative I2C address on the GY-49 breakout board,
//          the A0 pin has to be set to 3V3. It is soldered to GND by default.
//          See switch S1 / jp1 in the schematics.
//          Made for ESP specific; does not work on UNO; 


#include "Wire.h"
#include "Max44009.h"


//  Don't begin I2C interface (Wire). Will be called in setup()
Max44009 myLuxA(MAX44009_DEFAULT_ADDRESS, &Wire);
Max44009 myLuxB(MAX44009_ALT_ADDRESS, &Wire);
Max44009 myLuxC(MAX44009_DEFAULT_ADDRESS, &Wire1);
Max44009 myLuxD(MAX44009_ALT_ADDRESS, &Wire1);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44009_LIB_VERSION: ");
  Serial.println(MAX44009_LIB_VERSION);
  Serial.println();

  Wire.begin(19, 18);
  Wire1.begin(22, 23);
}


void loop() {
  if (millis() - lastDisplay >= 1000) {
    lastDisplay += 1000;

    Serial.println("Sensor|Error|Lux");
    Serial.printf("A     |%d    |%f\n", myLuxA.getError(), myLuxA.getLux());
    Serial.printf("B     |%d    |%f\n", myLuxB.getError(), myLuxB.getLux());
    Serial.printf("C     |%d    |%f\n", myLuxC.getError(), myLuxC.getLux());
    Serial.printf("D     |%d    |%f\n", myLuxD.getError(), myLuxD.getLux());
  }
}


//  -- END OF FILE --

