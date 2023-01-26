//    FILE: GST_add_runtime.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/GST


#include "Arduino.h"
#include "GST.h"


GST gst;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  gst.setTruePositive(0);
  gst.setTrueNegative(0);
  gst.setFalsePositive(0);
  gst.setFalseNegative(0);

}

void loop()
{
  //  simulate a test result
  delay(500);
  int score = random(4);
  switch (score)
  {
    case 0:
      gst.addTruePositive(1);
      break;
    case 1:
      gst.addTrueNegative(1);
      break;
    case 2:
      gst.addFalsePositive(1);
      break;
    case 3:
      gst.addFalseNegative(1);
      break;
  }
  confusion_matrix();
  //  confusion_matrix_normalized();
}


void confusion_matrix()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println();

  //  PRINTED IN A MATRIX
  Serial.print("\t");
  Serial.print(gst.getTotal());
  Serial.print("\t");
  Serial.print(gst.getTestedPositive());
  Serial.print("\t");
  Serial.println(gst.getTestedNegative());

  Serial.print("\t");
  Serial.print(gst.getActualPositive());
  Serial.print("\t");
  Serial.print(gst.getTruePositive());
  Serial.print("\t");
  Serial.println(gst.getFalseNegative());

  Serial.print("\t");
  Serial.print(gst.getActualNegative());
  Serial.print("\t");
  Serial.print(gst.getFalsePositive());
  Serial.print("\t");
  Serial.println(gst.getTrueNegative());

  Serial.println();
  Serial.print("\tSensitivity:\t");
  Serial.println(gst.sensitivity(), 4);
  Serial.print("\tSpecificity:\t");
  Serial.println(gst.specificity(), 4);
}


void confusion_matrix_normalized()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  Serial.println();

  //  PRINTED IN A MATRIX
  Serial.print("\t");
  Serial.print("100.00%");
  Serial.print("\t");
  Serial.print(gst.getTestedPositive());
  Serial.print("\t");
  Serial.println(gst.getTestedNegative());

  Serial.print("\t");
  Serial.print(gst.getActualPositive());
  Serial.print("\t");
  Serial.print(gst.TPR(), 4);
  Serial.print("\t");
  Serial.println(gst.FNR(), 4);

  Serial.print("\t");
  Serial.print(gst.getActualNegative());
  Serial.print("\t");
  Serial.print(gst.FPR(), 4);
  Serial.print("\t");
  Serial.println(gst.TNR(), 4);
}


//  -- END OF FILE --

