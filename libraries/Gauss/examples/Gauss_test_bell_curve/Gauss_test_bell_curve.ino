//
//    FILE: Gauss_test_bell_curve.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//
//  use plotter to create the graph in two ways

#include "Gauss.h"

Gauss G;

volatile float x;

void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("GAUSS_LIB_VERSION: ");
  Serial.println(GAUSS_LIB_VERSION);
  Serial.println();

  get_bell_curve();
  approximate();

  Serial.println("\ndone...");
}


void loop(void)
{
}


void get_bell_curve()
{
  G.begin(0, 1);

  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    Serial.println(100.0 * G.bellCurve(f), 6);
  }
  Serial.println();
}


//  approximation of the bell curve
void approximate()
{
  G.begin(0, 1);

  for (float f = -5.0; f <= 5.0; f += 0.01)
  {
    //  width == 2x 0.5233 == 1.0466
    //  0.0466 heuristic correction factor to match peak of the bell curve()
    //  not an exact match but almost perfect
    //  cf found with separate function below
    float cf = 0.52330751;
    float a = G.P_smaller(f - cf);
    float b = G.P_smaller(f + cf);
    Serial.println(100.0 * (b - a), 6);
  }
  Serial.println();
}


//  find the correction factor for the approximate function
//  so the peak matches the bell curve function.
//  ==>  0.52330751
void find_correction_factor()
{
  G.begin(0, 1);

  float ref = 100.0 * G.bellCurve(0);
  float cf  = 0.5233;  //  0.52330751;

  do
  {
    cf += 0.0000001;
    float a = G.P_smaller(-cf);
    float b = G.P_smaller(+cf);
    x = 100.0 * (b - a);
  }
  while (x < ref);
  Serial.print("Correction Factor: ");
  Serial.println(cf, 8);
  Serial.println();
}


// -- END OF FILE --
