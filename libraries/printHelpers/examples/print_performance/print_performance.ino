//
//    FILE: print_sci_eng_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program SCI
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


uint32_t start = 0;
uint32_t stop = 0;
char * b;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  Serial.println(sizeof(float));
  Serial.println(sizeof(double));


  double c = 2.99792458E8;   //  speed of light;
  double m = 7.34767309E20;  //  mass of moon
  double E = m * c * c;

  Serial.println();
  Serial.println("     Mass moon M = 7.34767309E+20");
  Serial.println("Speed of light c = 2.99792458E+8");
  Serial.println("         Print E = Mc^2 = 6.6037592413026551656653076E+37 \n");
  Serial.println();

  E = 660375924130265516;

  //  Serial.println(E, 16);
  Serial.println();
  Serial.println("print64");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = print64(int64_t(E), 10);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);

  Serial.println();
  Serial.println("SCI");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = sci(E, len);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);

  Serial.println();
  Serial.println("ENG");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = eng(E, len);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);


#if defined(__AVR__)
  Serial.println();
  Serial.println("dtostrf");
  delay(100);
  char buffer[200];
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    dtostrf(E, 4, len, buffer);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(buffer);
  delay(100);

  Serial.println();
  Serial.println("dtostre");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    dtostre(E, buffer, len, 0 );
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(buffer);
  delay(100);
#endif


  Serial.println();
  Serial.println("toBytes");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = toBytes(E, len);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);

  Serial.println();
  Serial.println("hex");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = hex(uint64_t(E));
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);

  Serial.println();
  Serial.println("bin");
  delay(100);
  start = micros();
  for (int len = 0; len < 16; len++)
  {
    b = bin(uint64_t(E));
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);


  Serial.println();
  Serial.println("toRoman");
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b = toRoman(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);


  Serial.println();
  Serial.println("printInch");
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b = printInch(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);


  Serial.println();
  Serial.println("printFeet");
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b = printFeet(i);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);


  Serial.println();
  Serial.println("CSI");
  volatile uint64_t big = 1234567890987654321;
  delay(100);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    b = csi(big);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(csi(big));
  Serial.println(print64(big));
  delay(100);


  Serial.println();
  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
