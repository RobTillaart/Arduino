//
//    FILE: PCA9634_test01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9634 library
//     URL: https://github.com/RobTillaart/PCA9634


#include "PCA9634.h"


PCA9634 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9634_LIB_VERSION: ");
  Serial.println(PCA9634_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ledArray.begin();

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
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDON);
    if (ledArray.getLedDriverMode(channel) != PCA963X_LEDON)
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
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDON);
    delay(200);
    ledArray.setLedDriverMode(channel, PCA963X_LEDPWM);
    if (ledArray.getLedDriverMode(channel) != PCA963X_LEDPWM)
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
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
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
    for (int channel = 0; channel < ledArray.channelCount(); channel++)
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
  for (int channel = 0; channel < ledArray.channelCount() - 3; channel++)
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
  Serial.println("Test - writeN");
  uint8_t arr[8] = {16, 32, 64, 96, 128, 160, 192, 255};
  ledArray.writeN(0, arr, 8);     //  8 == ledArray.channelCount()
}


void testSetGroupPWM_FREQ()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - GroupPWM");
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDGRPPWM);
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

  //  reset to LEDPWM
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDPWM);
  }
}


void testSetAndReadMode()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - readMode");
  uint8_t regval = ledArray.readMode(PCA963X_MODE1);
  ledArray.writeMode(PCA963X_MODE1, regval);     //  non destructive;
  Serial.print(millis());
  Serial.print("\t");
  Serial.print("PCA963X_MODE1: ");
  Serial.println(regval);
  regval = ledArray.readMode(PCA963X_MODE2);
  ledArray.writeMode(PCA963X_MODE2, regval);
  Serial.print(millis());
  Serial.print("\t");
  Serial.print("PCA963X_MODE2: ");
  Serial.println(regval);
}


void testSetLedDriverModeLEDOFF()
{
  Serial.print(millis());
  Serial.print("\t");
  Serial.println("Test - Switch all off");
  for (int channel = 0; channel < ledArray.channelCount(); channel++)
  {
    ledArray.setLedDriverMode(channel, PCA963X_LEDOFF);
    if (ledArray.getLedDriverMode(channel) != PCA963X_LEDOFF)
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


//  -- END OF FILE --

