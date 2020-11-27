//
//    FILE: FastNegate.ino
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.2.0
// PURPOSE: Fast negate for floating points
//
// HISTORY:
// 0.2.0    2020-06-30 main refactor
// 0.1.01 - 2013-09-08 added Gain:
// 0.1.00 - 2011-08-21 initial version
//

volatile float zz = 100;
volatile int x = 3;

uint32_t start, duration1, duration2;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  test_negfabs();
  test_fabs();
  test_negate();
  test_less_zero();
  test5();
}

void test_negfabs()
{
  Serial.println(__FUNCTION__);
  Serial.println("zz = -fabs(zz)");
  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    *(((byte*) &zz) + 3) |= 0x80;   // Force negative  == -fabs(zz);
  }
  duration1 = micros() - start;
  Serial.println(duration1 / 30000.0);
  Serial.println(zz);
  delay(10);

  zz = 100;
  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    zz = -fabs(zz);
  }
  duration2 = micros() - start;
  Serial.println(duration2 / 30000.0);
  Serial.print("Gain:\t");
  Serial.println(1.0 * duration2 / duration1);
  Serial.println(zz);
  Serial.println();
  delay(10);
}

void test_fabs()
{
  Serial.println(__FUNCTION__);
  Serial.println("zz = fabs(zz)");
  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    *(((byte*) &zz) + 3) &= 0x7F;     // force positive  == fabs(zz);
  }
  duration1 = micros() - start;
  Serial.println(duration1 / 30000.0);
  Serial.println(zz);
  delay(10);

  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    zz = fabs(zz);
  }
  duration2 = micros() - start;
  Serial.println(duration2 / 30000.0);
  Serial.print("Gain:\t");
  Serial.println(1.0 * duration2 / duration1);
  Serial.println(zz);
  Serial.println();
  delay(10);
}

void test_negate()
{
  Serial.println(__FUNCTION__);
  Serial.println("zz = -zz");
  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    *(((byte*) &zz) + 3) ^= 0x80;
  }
  duration1 = micros() - start;
  Serial.println(duration1 / 30000.0);
  Serial.println(zz);

  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    zz = -zz;
  }
  duration2 = micros() - start;
  Serial.println(duration2 / 30000.0);
  Serial.print("Gain:\t");
  Serial.println(1.0 * duration2 / duration1);
  Serial.println(zz);
  Serial.println();
  delay(10);
}

void test_less_zero()
{
  Serial.println(__FUNCTION__);
  Serial.println("if (zz < 0) ");
  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    if ( *(((byte*) &zz) + 3) & 0x80) x = 2; // equals if (zz < 0);
  }
  duration1 = micros() - start;
  Serial.println(duration1 / 30000.0);
  Serial.println(zz);

  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    if (zz < 0) x = 2;
  }
  duration2 = micros() - start;
  Serial.println(duration2 / 30000.0);
  Serial.print("Gain:\t");
  Serial.println(1.0 * duration2 / duration1);
  Serial.println(zz);

  start = micros();
  for (int i = 0; i < 30000; i++)
  {
    x = 2;
  }
  Serial.println((micros() - start) / 30000.0, 4);
  Serial.println(zz);
  Serial.println();
  delay(10);
}

void test5()
{
  Serial.println(__FUNCTION__);
  zz = -100;
  if (zz < 0) Serial.println("N");
  else Serial.println("P");
  zz = 100;
  if (zz < 0) Serial.println("N");
  else Serial.println("P");

  zz = -100;
  if (*(((byte*) &zz) + 3) & 0x80) Serial.println("N");
  else Serial.println("P");
  zz =  100;
  if (*(((byte*) &zz) + 3) & 0x80) Serial.println("N");
  else Serial.println("P");
}

void loop()
{
}

// -- END OF FILE --
