//
//    FILE: adt7470_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ADT7470 library


#include "ADT7470.h"

ADT7470 ADT(ADT7470_ADDR_FLOAT);  //  default Wire


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("ADT7470_LIB_VERSION: ");
  Serial.println(ADT7470_LIB_VERSION);
  Serial.println();


  Wire.begin();

  Serial.begin(115200);
  Serial.print(F("\n\nStart "));
  Serial.println(__FILE__);
  Serial.println();

  if (!ADT.isConnected())
  {
    Serial.println("Cannot connect ADT7470...\n");
    // while(1);
  }
  // else
  {
    testStart();
    testRevision();
    testTemp();
    testPWM();
    testTach();
    testFanSpeed();

    testStop();
  }
  Serial.println("Done");
}


void testStart()
{
  Serial.println(F("ADT7470 testStart"));
  ADT.powerUp();
  ADT.startMonitoring();
  Serial.println();
  Serial.println();
  delay(1000);
}


void testRevision()
{
  Serial.print("ADT7470_LIB_VERSION:\t");
  Serial.println(ADT7470_LIB_VERSION);

  Serial.print("ADT7470 getRevision:\t");
  Serial.println(ADT.getRevision());
  Serial.print("ADT7470 getDeviceID:\t");
  Serial.println(ADT.getDeviceID());
  Serial.print("ADT7470 getCompanyID:\t");
  Serial.println(ADT.getCompanyID());
  Serial.println();
  Serial.println();
  delay(10);
}


void testTemp()
{
  Serial.println(F("ADT7470 testTemp 0..9"));

  Serial.print("temp:");
  for (uint8_t i = 0; i < 10; i++)
  {
    Serial.print("\t");
    Serial.print(ADT.getTemperature(i));
  }
  Serial.println();
  Serial.print("max:\t");
  Serial.println(ADT.getMaxTemperature());

  Serial.println();
  Serial.println();
  delay(10);
}


void testPWM()
{
  Serial.println(F("ADT7470 getPWM 0..3"));
  Serial.print(F("set:"));
  for (int i = 0; i < 4; i++)
  {
    uint8_t pwm = random(255);
    ADT.setPWM(i, pwm);
    Serial.print("\t");
    Serial.print(pwm);
  }
  Serial.println();

  Serial.print(F("get:"));
  for (int i = 0; i < 4; i++)
  {
    uint8_t pwm = ADT.getPWM(i);
    Serial.print("\t");
    Serial.print(pwm);
  }
  Serial.println();
  Serial.println();
  delay(10);
}


void testTach()
{
  uint8_t ppr[4];
  Serial.println(F("ADT7470 testTach 0..3"));
  Serial.print(F("getPPR: "));
  for (uint8_t i = 0; i < 4; i++)
  {
    ppr[i] = ADT.getPulsesPerRevolution(i);
    Serial.print("\t");
    Serial.print(ppr[i]);
  }
  Serial.println();

  Serial.print(F("setPPR: "));
  for (uint8_t i = 0; i < 4; i++)
  {
    ADT.setPulsesPerRevolution(i, ppr[i]);
    bool b = (ppr[i] == ADT.getPulsesPerRevolution(i));
    Serial.print("\t");
    Serial.print(b ? "T" : "F");          //  expect TTTT
  }
  Serial.println();

  ADT.setSlowTach();
  Serial.println(F("setSlowTach"));
  Serial.print(F("getTach:"));
  for (uint8_t i = 0; i < 4; i++)
  {
    uint16_t tach = ADT.getTach(i);
    Serial.print("\t");
    Serial.print(tach);
  }
  Serial.println();
  Serial.print(F("getRPM :"));
  for (int i = 0; i < 4; i++)
  {
    uint32_t rpm = ADT.getRPM(i);
    Serial.print("\t");
    Serial.print(rpm);
  }
  Serial.println();

  ADT.setFastTach();
  Serial.println(F("setFastTach"));
  Serial.print(F("getTach:"));
  for (uint8_t i = 0; i < 4; i++)
  {
    uint16_t tach = ADT.getTach(i);
    Serial.print("\t");
    Serial.print(tach);
  }
  Serial.println();
  Serial.print(F("getRPM :"));
  for (int i = 0; i < 4; i++)
  {
    uint32_t rpm = ADT.getRPM(i);
    Serial.print("\t");
    Serial.print(rpm);
  }
  Serial.println();
  Serial.println();
  delay(10);
}


void testFanSpeed()
{
  Serial.println(F("ADT7470 testFanSpeed"));
  Serial.print("low:\t");
  for (uint8_t i = 0; i < 8; i++)
  {
    ADT.setFanLowFreq(i);
    Serial.print(i);
    Serial.print("\t");
    delay(1000);
  }
  Serial.println();

  Serial.print("high:\t");
  for (uint8_t i = 0; i < 8; i++)
  {
    ADT.setFanHighFreq(i);
    Serial.print(i);
    Serial.print("\t");
    delay(1000);
  }
  Serial.println();
  ADT.setFanHighFreq(2);

  Serial.println();
  Serial.println();
  delay(10);
}


void testStop()
{
  Serial.println(F("ADT7470 testStop"));
  ADT.stopMonitoring();
  ADT.powerDown();
  delay(2000);
  //  TODO how to check if it is down - datasheet.
}


void loop()
{
}


//  -- END OF FILE --

