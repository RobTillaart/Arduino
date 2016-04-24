//
//    FILE: PCA9685_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 24-APR-2016
// VERSION: 0.1.00
// PUPROSE: test PCA9685 library
//

#include "PCA9685.h"
#include <Wire.h>

PCA9685 ledArray(0x20);

void setup()
{
    Serial.begin(115200);
    Serial.print("PCA9685 LIB version: ");
    Serial.println(PCA9685_LIB_VERSION);
    Serial.println();

    testSetON();
    testPWMMode();
    delay(2000);
    testSetOFF();

    Serial.print(millis());
    Serial.print("\t");
    Serial.println("done...");
}

void testSetON()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - setON");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setON(channel);
    }
}

void testSetOFF()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - setOFF");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setOFF(channel);
    }
}

void testPWMMode()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - setPwm getPWM");
    for (int channel = 0; channel < 16; channel++)
    {
        // every next line ~twice as much time
        ledArray.setPWM(channel, channel*127, channel*255);
        uint16_t a, b;
        ledArray.getPWM(channel, &a, &b);
        if (a != channel*127 || b != channel*255)
        {
            Serial.println(channel);
        }
    }
}

void loop()
{

}
