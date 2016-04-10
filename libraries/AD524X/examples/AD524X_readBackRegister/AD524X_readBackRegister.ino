//
//    FILE: AD524X_readBackRegister.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: AD524X demo program
//    DATE: 2016-04-10
//     URL:
//
// Released to the public domain
//

#include "AD524X.h"
#include "Wire.h"

AD524X AD01(0x2C);  // AD0 & AD1 == GND

void setup()
{
    Serial.begin(115200);
    Serial.print("\nStart AD524X_readBackRegister : ");
    Serial.println(AD524X_VERSION);

    Wire.begin();
    TWBR = 12;  // 400 KHz
}

void loop()
{
    for (int rdac = 0; rdac < 2; rdac++)
    {
        for (int val = 0; val < 255; val++)
        {
            test(rdac, val);
        }
    }
    delay(1000);
}

void test(uint8_t rdac, uint8_t val)
{
    Serial.print(val);
    AD01.write(rdac, val);
    delay(100);
    int x = AD01.read(rdac);
    int y = AD01.readBackRegister();
    Serial.print('\t');
    Serial.print(x);
    Serial.print('\t');
    Serial.println(y);
    delay(100);
}