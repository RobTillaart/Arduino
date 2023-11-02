#pragma once
//
//    FILE: GST.h
// VERSION: 0.1.4
// PURPOSE: Arduino library for Gold Standard Test metrics
//     URL: https://github.com/RobTillaart/GST
//          https://en.wikipedia.org/wiki/Sensitivity_and_specificity
//          https://en.wikipedia.org/wiki/Confusion_matrix
//
//  formula's based upon Wikipedia.


#define GST_LIB_VERSION           (F("0.1.4"))


#include "Arduino.h"


class GST
{
public:
  GST();

  //  These four values of the matrix need to be set to get started.
  void setTruePositive(float v = 0);
  void setTrueNegative(float v = 0);
  void setFalsePositive(float v = 0);
  void setFalseNegative(float v = 0);
  void clearAll();

  //  These are used for updating the test matrix
  float addTruePositive(float v);
  float addTrueNegative(float v);
  float addFalsePositive(float v);
  float addFalseNegative(float v);


  //  Output functions I
  float getTruePositive();
  float getTrueNegative();
  float getFalsePositive();
  float getFalseNegative();

  float getTotal();
  float getActualPositive();
  float getActualNegative();
  float getTestedPositive();
  float getTestedNegative();

  float sensitivity();
  float specificity();


  float truePositiveRate();
  float TPR();
  float trueNegativeRate();
  float TNR();
  float falseNegativeRate();
  float FNR();
  float falsePositiveRate();
  float FPR();


  //  Output functions II
  float positivePredictiveValue();
  float PPV();
  float negativePredictiveValue();
  float NPV();
  float falseDiscoveryRate();
  float FDR();
  float falseOmissionRate();
  float FOR();


  float positiveLikelihoodRatio();
  float LRplus();
  float negativeLikelihoodRatio();
  float LRminus();


  float prevalenceThreshold();
  float threatScore();
  float criticalSuccessIndex();


  float prevalence();
  float accuracy();
  float balancedAccuracy();
  float F1Score();


  float MatthewsCorrelationCoefficient();
  float phi();
  float MCC();
  float FowlkesMallowsIndex();
  float FM();
  float BookmakerInformedness();
  float BM();


  float markedness();
  float deltaP();
  float MK();
  float diagnosticOddsRatio();
  float DOR();


private: 
  float AP;   //  actual positive
  float AN;   //  actual negative
  float TP;   //  true positive
  float TN;   //  true negative
  float FP;   //  false positive
  float FN;   //  false positive
};


//  -- END OF FILE --

