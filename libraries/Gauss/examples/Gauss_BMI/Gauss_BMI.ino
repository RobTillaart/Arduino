//
//    FILE: Gauss_BMI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - not a medical program

#include "Gauss.h"

Gauss G;


void setup(void)
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("GAUSS_LIB_VERSION:\t");
  Serial.println(GAUSS_LIB_VERSION);
  Serial.println();

  //  BMI - adjust to your local situation
  //  https://en.wikipedia.org/wiki/List_of_sovereign_states_by_body_mass_index
  //  stddev is assumption.
  G.begin(25.0, 2.5);
}


void loop(void)
{
  //  flush
  while (Serial.available()) Serial.read();

  Serial.println("Enter your weight in kg: ");
  while (!Serial.available());
  float weight = Serial.parseFloat();
  if (weight == 0) return;

  while (Serial.available()) Serial.read();
  Serial.println("Enter your length in cm: ");
  while (!Serial.available());
  float length = Serial.parseFloat();
  if (length == 0) return;

  float BMI = (10000.0 * weight) / (length * length);

  float stddev = G.normalize(BMI);
  Serial.print("\tWeight:\t\t");
  Serial.println(weight);

  Serial.print("\tLength:\t\t");
  Serial.println(length);

  Serial.print("\tBMI:\t\t");
  Serial.println(BMI);

  Serial.print("\tStddev:\t\t");
  if (stddev >= 0) Serial.print('+');
  Serial.println(stddev, 2);

  Serial.print("\tSmaller:\t");
  Serial.print(100.0 * G.P_smaller(BMI));
  Serial.println("%");

  Serial.print("\tLarger:\t\t");
  Serial.print(100.0 * G.P_larger(BMI));
  Serial.println("%");

  Serial.print("\tSame:\t\t");
  Serial.print(100.0 * G.P_between(BMI - 0.1, BMI + 0.1));
  Serial.print("%");
  Serial.println();
  Serial.println();
}


//  -- END OF FILE --
