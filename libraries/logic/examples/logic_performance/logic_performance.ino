//
//    FILE: logic_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/logic
//

#include "logic.h"

logic LGC;

uint32_t start, stop;

volatile bool t;

void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGIC_LIB_VERSION: ");
  Serial.println(LOGIC_LIB_VERSION);
  Serial.println();
  delay(100);


  //  fill the truth table.
  start = micros();
  LGC.setTable(0x1855A53F);
  stop = micros();

  Serial.print("SETTABLE:\t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);

  volatile bool a = random(2);
  volatile bool b = random(2);
  volatile bool c = random(2);
  volatile bool d = random(2);
  volatile bool e = random(2);

  //  EVAL

  start = micros();
  t = LGC.eval(a, b);
  stop = micros();
  Serial.print("EVAL(a,b):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.eval(a, b, c);
  stop = micros();
  Serial.print("EVAL(a,b,c):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.eval(a, b, c, d);
  stop = micros();
  Serial.print("EVAL(a,b,c,d):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.eval(a, b, c, d, e);
  stop = micros();
  Serial.print("EVAL(a,b,c,d,e):\t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);

  //  NEVAL
  start = micros();
  t = LGC.neval(a, b);
  stop = micros();
  Serial.print("NEVAL(a,b):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.neval(a, b, c);
  stop = micros();
  Serial.print("NEVAL(a,b,c):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.neval(a, b, c, d);
  stop = micros();
  Serial.print("NEVAL(a,b,c,d):\t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  t = LGC.neval(a, b, c, d, e);
  stop = micros();
  Serial.print("NEVAL(a,b,c,d,e):\t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --
