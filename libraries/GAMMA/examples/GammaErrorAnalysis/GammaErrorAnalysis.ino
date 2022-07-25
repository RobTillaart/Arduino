//
//    FILE: GammaErrorAnalysis.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "gamma.h"


GAMMA gt1(256);
GAMMA gt2(128);
GAMMA gt3(64);
GAMMA gt4(32);
GAMMA gt5(16);
GAMMA gt6(8);
GAMMA gt7(4);
GAMMA gt8(2);

uint32_t start, d1;
volatile int x;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GAMMA_LIB_VERSION: ");
  Serial.println(GAMMA_LIB_VERSION);

  gt1.begin();
  gt2.begin();
  gt3.begin();
  gt4.begin();
  gt5.begin();
  gt6.begin();
  gt7.begin();
  gt8.begin();

  Serial.println("\nError Analysis 256 elements = reference\n");
  Serial.println("Size\tErrors\tMaximum");
  test_error(gt1);
  test_error(gt2);
  test_error(gt3);
  test_error(gt4);
  test_error(gt5);
  test_error(gt6);
  test_error(gt7);
  test_error(gt8);
  Serial.println();

  Serial.println("\ndone...\n");
}


void test_error(GAMMA gt)
{
  int count = 0;
  int maxdiff = 0;

  for (int i = 0; i < 256; i++)
  {
    int diff = abs(gt[i] - gt1[i]);
    if (diff != 0) count++;
    if (diff > maxdiff) maxdiff = diff;
  }

  Serial.print(gt.size());
  Serial.print('\t');
  Serial.print(count);
  Serial.print('\t');
  Serial.println(maxdiff);
}


void loop()
{
}


// -- END OF FILE --

