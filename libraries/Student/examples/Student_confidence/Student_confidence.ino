//
//    FILE: Student_confidence.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Student


#include "Student.h"

Student S;

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("STUDENT_LIB_VERSION: ");
  Serial.println(STUDENT_LIB_VERSION);
  Serial.println();

  S.reset();
  S.add(12.4);
  S.add(11.8);
  S.add(12.0);
  S.add(11.7);
  S.add(12.1);
  S.add(12.3);
  S.add(11.9);
  S.add(11.6);
  S.add(11.9);
  S.add(12.3);

  //  for (int i = 0; i < 10; i++)
  //  {
  //    S.add(i);
  //  }
  Serial.print("Size:\t");
  Serial.println(S.getSize());
  Serial.print("Count:\t");
  Serial.println(S.getCount());

  Serial.print("mean:\t");
  Serial.println(S.mean(), 3);
  Serial.print("var:\t");
  Serial.println(S.variance(), 3);
  Serial.print("dev:\t");
  Serial.println(S.deviation(), 3);
  Serial.print("E dev:\t");
  Serial.println(S.estimatedDeviation(), 3);
  Serial.println();

  Serial.println("Conf\tMeanLow\tMeanUp\tRange");
  for (int confidence = 80; confidence < 100; confidence++)
  {
    Serial.print(confidence);
    Serial.print("\t");
    Serial.print(S.meanLower(confidence), 3);
    Serial.print("\t");
    Serial.print(S.meanUpper(confidence), 3);
    Serial.print("\t");
    Serial.println(S.meanUpper(confidence) - S.meanLower(confidence), 3);
  }

  Serial.println("\ndone...");
}


void loop(void)
{
}




//  -- END OF FILE --
