//
//    FILE: Max44007_test02.ino
//  AUTHOR: Moritz Ulmer
// PURPOSE: demo of Max44007 library
//    DATE: 2022-01-04
//
//    NOTE: To select the alternative I2C address on the GY-49 breakout board,
//          the A0 pin has to be set to 3V3. It is soldered to GND by default.
//          See switch S1 / jp1 in the schematics.
//          Made for ESP specific; does not work on UNO; 


#include "Wire.h"
#include "Max44007.h"


// Don't begin I2C interface (Wire). Will be called in setup()
Max44007 myLuxA(Max44007::Boolean::False);
Max44007 myLuxB(Max44007::Boolean::False);
Max44007 myLuxC(Max44007::Boolean::False);
Max44007 myLuxD(Max44007::Boolean::False);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start Max44007_test02 : ");
  Serial.println(Max44007_LIB_VERSION);

  Wire.begin(19, 18);
  Wire1.begin(22, 23);
  myLuxA.configure(Max44007_DEFAULT_ADDRESS, &Wire);
  myLuxB.configure(Max44007_ALT_ADDRESS, &Wire);
  myLuxC.configure(Max44007_DEFAULT_ADDRESS, &Wire1);
  myLuxD.configure(Max44007_ALT_ADDRESS, &Wire1);
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


// -- END OF FILE --

