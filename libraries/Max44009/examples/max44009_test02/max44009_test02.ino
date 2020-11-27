//
//    FILE: max44009_test02.ino
//  AUTHOR: Moritz Ulmer
// VERSION: 0.3.1
// PURPOSE: demo of max44009 library
//    NOTE: To select the alternative I2C address on the GY-49 breakout board,
//          the A0 pin has to be set to 3V3. It is soldered to GND by default.
//          See switch S1 / jp1 in the schematics.
//          Made for ESP specific; does not work on UNO; 
//    DATE: 2020-01-19
//
// Released to the public domain
//

#include "Wire.h"
#include "Max44009.h"

// Don't begin I2C interface (Wire). Will be called in setup()
Max44009 myLuxA(Max44009::Boolean::False);
Max44009 myLuxB(Max44009::Boolean::False);
Max44009 myLuxC(Max44009::Boolean::False);
Max44009 myLuxD(Max44009::Boolean::False);

uint32_t lastDisplay = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start max44009_test02 : ");
  Serial.println(MAX44009_LIB_VERSION);

  Wire.begin(19, 18);
  Wire1.begin(22, 23);
  myLuxA.configure(MAX44009_DEFAULT_ADDRESS, &Wire);
  myLuxB.configure(MAX44009_ALT_ADDRESS, &Wire);
  myLuxC.configure(MAX44009_DEFAULT_ADDRESS, &Wire1);
  myLuxD.configure(MAX44009_ALT_ADDRESS, &Wire1);
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

// END OF FILE