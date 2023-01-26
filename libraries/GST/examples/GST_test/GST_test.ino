//    FILE: GST_test.ino
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

  gst.setTruePositive(653);
  gst.setTrueNegative(312);
  gst.setFalsePositive(124);
  gst.setFalseNegative(423);

  confusion_matrix();
  confusion_matrix_normalized();
  test_3();
  test_4();
  test_5();
  test_6();

  Serial.println("\ndone...");

}


void loop()
{
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


void test_3()
{
  Serial.println();

  Serial.print("positive predictive value:\t");
  Serial.println(gst.PPV(), 4);
  Serial.print("negative predictive value:\t");
  Serial.println(gst.NPV(), 4);
  Serial.print("false discovery rate:\t\t");
  Serial.println(gst.FDR(), 4);
  Serial.print("false omission rate:\t\t");
  Serial.println(gst.FOR(), 4);
}


void test_4()
{
  Serial.println();

  Serial.print("positive likelihood ratio:\t");
  Serial.println(gst.LRplus(), 4);
  Serial.print("negative likelihood ratio:\t");
  Serial.println(gst.LRminus(), 4);
}


void test_5()
{
  Serial.println();

  Serial.print("prevalenceThreshold:\t\t");
  Serial.println(gst.prevalenceThreshold(), 4);
  Serial.print("criticalSuccessIndex:\t\t");
  Serial.println(gst.criticalSuccessIndex(), 4);
  Serial.print("prevalence:\t\t\t");
  Serial.println(gst.prevalence(), 4);
  Serial.print("accuracy:\t\t\t");
  Serial.println(gst.accuracy(), 4);
  Serial.print("balancedAccuracy:\t\t");
  Serial.println(gst.balancedAccuracy(), 4);
  Serial.print("F1Score:\t\t\t");
  Serial.println(gst.F1Score(), 4);
}


void test_6()
{
  Serial.println();

  Serial.print("Matthews correlation coefficient:\t");
  Serial.println(gst.MCC(), 4);
  Serial.print("Fowlkes–Mallows index:\t\t\t");
  Serial.println(gst.FM(), 4);
  Serial.print("Bookmaker informedness:\t\t\t");
  Serial.println(gst.BM(), 4);
  Serial.print("markedness:\t\t\t\t");
  Serial.println(gst.MK(), 4);
  Serial.print("diagnostic odds ratio:\t\t\t");
  Serial.println(gst.DOR(), 4);
}


//  -- END OF FILE --
