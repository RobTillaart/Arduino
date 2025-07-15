//
//    FILE: AS5600_pwm_test2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AS5600
//          https://forum.arduino.cc/t/questions-using-the-as5600-in-pwm-mode/1266957/3
//
//  monitor the PWM output to determine the angle
//  not tested with hardware yet
//
//  this is a slightly optimized version of AS5600_pwm_test.ino


int PWMpin = 7;

//  variables for the timing
float bitTime = 1.0;
float f1 = 1.0;
float f2 = 1.0;

void measurePWMBitTime()
{
  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  // wait for HIGH
  while (digitalRead(PWMpin) == LOW);
  uint32_t rise = micros();
  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  // wait for HIGH
  while (digitalRead(PWMpin) == LOW);
  long fullPeriod = micros() - rise;
  bitTime = fullPeriod / 4351.0;
  //  precalculate constants.
  f1 = 128 * bitTime;
  f2 = (360.0 / (4095 * bitTime));
}


float measureAngle()
{
  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  // wait for HIGH
  while (digitalRead(PWMpin) == LOW);
  uint32_t rise = micros();

  // wait for LOW
  while (digitalRead(PWMpin) == HIGH);
  uint32_t highPeriod = micros() - rise;

  //  precalculated constant
  //  f1 = 128 * bittime
  //  f2 = 360.0 / (4095 * bitTime)
  float dataPeriod = highPeriod - f1;
  float angle = dataPeriod * f2;
  return angle;
}


//float testMath(uint32_t fullPeriod, uint32_t highPeriod)
//{
//  float bitTime = fullPeriod / 4351.0;
//  float dataPeriod = highPeriod - 128 * bitTime;
//  float angle = 360.0 * dataPeriod / (4095 * bitTime);
//  return angle;
//}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();

  pinMode(PWMpin, INPUT_PULLUP);
  measurePWMBitTime();
  

//  //  test code
//  for (int pwm = 0; pwm < 4096; pwm++)
//  {
//    Serial.println(testMath(4351, 128 + pwm), 2);
//  }
}


void loop()
{
  float angle = measureAngle();
  Serial.println(angle, 1);  //  print with 1 decimal

  delay(1000);
}


//  -- END OF FILE --
