//    FILE: atomic_weight_split.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"
#include "AtomicWeight.h"


PTOE ptoe;

char formula0[24] = "C6H6O6";
char formula1[24] = "((COH)3)2";
char formula2[24] = "H2SO4";
char formula3[24] = "CuO2";
char formula4[24] = "(COH)3(COH)2COH";
// char formula4[24] = "(CH)6O6";
// char formula4[24] = "xH2";  // fails => 0;
char formula5[24] = "YBa2Cu3O7";


uint8_t cnt;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ATOMIC_WEIGHT_LIB_VERSION: ");
  Serial.println(ATOMIC_WEIGHT_LIB_VERSION);

  test("C");
  test("C6");
  test("CCCCCCC");
  test("He6");
  test("NaCl");

  test(formula0);
  test(formula1);
  test(formula2);
  test(formula3);
  test(formula4);
  test(formula5);

  Serial.println("done");
}


void loop()
{
}


void test(char * formula)
{
  Serial.println();
  Serial.println(formula);
  uint8_t cnt = ptoe.splitElements(formula);
  for (int i = 0; i < cnt; i++)
  {
    Serial.print(ptoe.name(ptoe.element(i)));
    Serial.print("\t");
    Serial.println(ptoe.massPercentage(formula, ptoe.name(ptoe.element(i))), 3);
  }

  delay(100);
  uint32_t start = micros();
  cnt = ptoe.splitElements(formula);
  uint32_t stop = micros();
  Serial.print("TIME:\t");
  Serial.print(stop - start);
  Serial.println(" us.");

  Serial.println();
}


//  -- END OF FILE --
