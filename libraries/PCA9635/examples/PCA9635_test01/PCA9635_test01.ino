//
//    FILE: PCA9635_test01.ino
//  AUTHOR: Rob Tillaart
//    DATE: 23-APR-2016
// VERSION: 0.1.01
// PUPROSE: test PCA9635 library
//

#include "PCA9635.h"
#include <Wire.h>

PCA9635 ledArray(0x20);

void setup()
{
    Serial.begin(115200);
    Serial.print("PCA9635 LIB version: ");
    Serial.println(PCA9635_LIB_VERSION);
    Serial.println();

    testSetLedDriverModeLEDON();
    testPWMMode();
    testWrite1();
    testWrite3();
    testWriteN();
    testSetGroupPWM_FREQ();
    testSetAndReadMode();
    testSetLedDriverModeLEDOFF();

    Serial.print(millis());
    Serial.print("\t");
    Serial.println("done...");
}

void testSetLedDriverModeLEDON()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - Switch all on");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setLedDriverMode(channel, PCA9635_LEDON);
        if (ledArray.getLedDriverMode(channel) != PCA9635_LEDON)
        {
            Serial.print(millis());
            Serial.print("\t");
            Serial.print("Channel: ");
            Serial.println(channel);
        }
    }
}

void testPWMMode()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - set pwm mode");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setLedDriverMode(channel, PCA9635_LEDON);
        delay(200);
        ledArray.setLedDriverMode(channel, PCA9635_LEDPWM);
        if (ledArray.getLedDriverMode(channel) != PCA9635_LEDPWM)
        {
            Serial.print(millis());
            Serial.print("\t");
            Serial.print("Channel: ");
            Serial.println(channel);
        }
    }
}

void testWrite1()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - write1 - I");
    for (int channel = 0; channel < 16; channel++)
    {
        for (int pwm = 0; pwm < 256; pwm++)
        {
            ledArray.write1(channel, pwm);
        }
    }
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - write 1 - II");
    for (int pwm = 0; pwm < 256; pwm++)
    {
        for (int channel = 0; channel < 16; channel++)
        {
            ledArray.write1(channel, pwm);
        }
    }
}

void testWrite3()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - write3 - random RGB");
    for (int channel = 0; channel < 13; channel++)  // 13 = 16 -3 !!!
    {
        uint8_t R = random(256);
        uint8_t G = random(256);
        uint8_t B = random(256);
        ledArray.write3(channel, R, G, B);
    }
}

void testWriteN()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - writeN ");
    uint8_t arr[16] = {16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255};
    ledArray.writeN(0, arr, 16);
}

void testSetGroupPWM_FREQ()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - GroupPWM");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setLedDriverMode(channel, PCA9635_LEDGRPPWM);
    }
    for (int pwm = 0; pwm < 256; pwm++)
    {
        ledArray.setGroupPWM(pwm);
        uint8_t p = ledArray.getGroupPWM();
        if (p != pwm)
        {
            Serial.print(millis());
            Serial.print("\t");
            Serial.print("pwm: ");
            Serial.println(pwm);
        }
    }
    ledArray.setGroupPWM(127);

    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - groupFRQ");
    for (int frq = 0; frq < 256; frq++)
    {
        ledArray.setGroupFREQ(frq);
        uint8_t f = ledArray.getGroupFREQ();
        if (f != frq)
        {
            Serial.print(millis());
            Serial.print("\t");
            Serial.print("frq: ");
            Serial.println(frq);
        }
    }
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setLedDriverMode(channel, PCA9635_LEDPWM);
    }
}

void testSetAndReadMode()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - readMode");
    uint8_t regval = ledArray.readMode(PCA9635_MODE1);
    ledArray.writeMode(PCA9635_MODE1, regval);     // non destructive;
    Serial.print(millis());
    Serial.print("\t");
    Serial.print("PCA9635_MODE1: ");
    Serial.println(regval);
    regval = ledArray.readMode(PCA9635_MODE2);
    ledArray.writeMode(PCA9635_MODE2, regval);
    Serial.print(millis());
    Serial.print("\t");
    Serial.print("PCA9635_MODE2: ");
    Serial.println(regval);
}

void testSetLedDriverModeLEDOFF()
{
    Serial.print(millis());
    Serial.print("\t");
    Serial.println("Test - Switch all off");
    for (int channel = 0; channel < 16; channel++)
    {
        ledArray.setLedDriverMode(channel, PCA9635_LEDOFF);
        if (ledArray.getLedDriverMode(channel) != PCA9635_LEDOFF)
        {
            Serial.print(millis());
            Serial.print("\t");
            Serial.print("Channel: ");
            Serial.println(channel);
        }
    }
}

void loop()
{

}
