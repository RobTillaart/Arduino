//
//    FILE: fle.demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/FLE


#include "FLE.h"

FLE zero;
FLE one(1);
FLE PIE(PI);
FLE PIEP(22.0 / 7.0, PI - 22.0 / 7.0);
FLE PIEQ(355.0 / 113.0, PI - 355.0 / 113.0);
FLE EE(EULER);

FLE x(2, 0.1);
FLE y(7, 0.3);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FLE_LIB_VERSION: ");
  Serial.println(FLE_LIB_VERSION);
  Serial.println();

  test_printable();
  test_math_1();

  Serial.println("\nDone...");
}


void loop()
{
}


void test_printable()
{
  Serial.println(__FUNCTION__);
  Serial.print("zero\t");
  Serial.println(zero);

  Serial.print("one\t");
  Serial.println(one);

  Serial.print("PIE\t");
  Serial.println(PIE.setDecimals(8));

  Serial.print("22/7\t");
  Serial.println(PIEP.setDecimals(8));

  Serial.print("355/113\t");
  PIEQ.setDecimals(8);
  Serial.println(PIEQ);

  Serial.print("EULER\t");
  EE.setDecimals(8);
  Serial.println(EE);

  Serial.print("x\t");
  Serial.println(x);
  Serial.print("y\t");
  Serial.println(y);
  Serial.println();
  Serial.println();
}


void test_math_1()
{
  Serial.println(__FUNCTION__);
  Serial.print("x + y\t");
  Serial.println(x + y);
  Serial.print("x - y\t");
  Serial.println(x - y);
  Serial.print("x * y\t");
  Serial.println(x * y);
  Serial.print("x / y\t");
  Serial.println(x / y);
  Serial.println();

  FLE z = x;
  Serial.print("z = x\t");
  Serial.println(z);
  z += x;
  Serial.print("z += x\t");
  Serial.println(z);
  z -= x;
  Serial.print("z -= x\t");
  Serial.println(z);
  z *= x;
  Serial.print("z *= x\t");
  Serial.println(z);
  z /= x;
  Serial.print("z /= x\t");
  Serial.println(z);

  Serial.println();
  Serial.println();
}


// -- END OF FILE --
