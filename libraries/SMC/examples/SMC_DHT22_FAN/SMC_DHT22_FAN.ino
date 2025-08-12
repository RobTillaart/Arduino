//
//    FILE: SMC_DHT22_FAN.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/SMC
//
//  EXPERIMENTAL


#include "SMC.h"
#include "dhtnew.h"

DHTNEW dht(8);  //  adjust pinnumber if needed
SMC smc;

float temperature = 0;
float maxValue = 255;  //  0..255 PWM
float outValue;
float errorWeight = 0.5;
float deltaErrorWeight = 1.5;
float offset = 0;
float setPoint = 15;

int PWMpin = 9;

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SMC_LIB_VERSION: ");
  Serial.println(SMC_LIB_VERSION);
  Serial.println();

  //  setPoint, outValue, errorWeight, deltaErrorWeight
  smc.begin(setPoint, maxValue, 0.5, 1.5);
  smc.setMode(SMC_SIMPLE);

  Serial.println("Settings:");
  Serial.println(smc.getMode());
  Serial.println(smc.getSetPoint());
  Serial.println(smc.getMaxValue());
  Serial.println(smc.getWeight1());
  Serial.println(smc.getWeight2());
}


void loop()
{
  delay(20);
  //  dht.read();
  //  temperature = dht.getTemperature();
  outValue = smc.outValue(temperature);

  Serial.print(temperature, 2);
  Serial.print("\t");
  Serial.print(outValue, 2);
  Serial.print("\t");
  Serial.print(maxValue - outValue, 2);
  Serial.print("\n");

  //  normal PWM for heater
  analogWrite(PWMpin, outValue);
  //  inverted PWM for fan (cooling)
  //  analogWrite(PWMpin, maxValue - outValue);

  //  simulate the temperature
  //  simulate the setpoint
  //  change the mode
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '+') temperature += 0.2;
    if (c == '-') temperature -= 0.2;
    if (c == '0') temperature = 0.0;
    if (c == '*') setPoint += 0.2;
    if (c == '/') setPoint -= 0.2;
    if (c == 'L') smc.setMode(SMC_LINEAR);
    if (c == 'E') smc.setMode(SMC_EXPONENTIAL);
    if (c == 'S') smc.setMode(SMC_SIMPLE);
    smc.setOffset(offset);
    smc.setSetPoint(setPoint);
  }

}


//  -- END OF FILE --
