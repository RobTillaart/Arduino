#pragma once
//
//    FILE: GST.h
// VERSION: 0.1.0
// PURPOSE: Arduino library for Gold Standard Test metrics
//     URL: https://github.com/RobTillaart/GST
//          https://en.wikipedia.org/wiki/Sensitivity_and_specificity
//          https://en.wikipedia.org/wiki/Confusion_matrix
//
// formula's based upon wikipedia.


#define GST_LIB_VERSION           (F("0.1.0"))


class GST
{
public:
  GST() {};

  // These 4 need to be filled in.
  void setTruePositive(float v)   { TP = v; P = TP + FN; };
  void setTrueNegative(float v)   { TN = v; N = TN + FP; };
  void setFalsePositive(float v)  { FP = v; N = TN + FP; };
  void setFalseNegative(float v)  { FN = v; P = TP + FN; };

  float getTruePositive()   { return TP; };
  float getTrueNegative()   { return TN; };
  float getFalsePositive()  { return FP; };
  float getFalseNegative()  { return FN; };

  float getTotal()          { return  P + N; };
  float getActualPositive() { return  P; };
  float getActualNegative() { return  N; };
  float getTestedPositive() { return TP + FP; };
  float getTestedNegative() { return TN + FN; };

  float sensitivity()       { return TPR(); };
  float specificity()       { return TNR(); };



  //  true positive rate
  float TPR() { return TP / P; };
  //  true negative rate
  float TNR() { return TN / N; };

  //  false negative rate
  float FNR() { return FN / (FN + TP); };
  //  false positive rate
  float FPR() { return FP / (FP + TN); };



  //  positive predictive value
  float PPV() { return TP / (TP + FP); };
  //  negative predictive value
  float NPV() { return TN / (TN + FN); };

  //  false discovery rate
  float FDR() { return FP / (FP + TP); };
  //  false omission rate
  float FOR() { return FN / (FN + TN); };



  //  positive likelihood ratio
  float LRplus()  { return TPR() / FPR(); };
  //  negative likelihood ratio
  float LRminus() { return FNR() / TNR(); };



  float prevalenceThreshold()  { return sqrt(FPR()) / (sqrt(TPR()) + sqrt(FPR())); };
  float threatScore()  { return TP / (TP + FN + FP); };
  float criticalSuccessIndex() { return threatScore(); };



  float prevalence()       { return P / (P + N); };
  float accuracy()         { return (TP + TN) / (P + N); };
  float balancedAccuracy() { return (TPR() + TNR()) / 2; };
  float F1Score()          { return (2 * TP)/(2 * TP + FP + FN); };



  //  Matthews correlation coefficient
  float MCC() { return (TP*TN-FP*FN)/sqrt((TP+FP)*(TP+FN)*(TN+FP)*(TN+FN)); };
  float phi() { return MCC(); };
  //  Fowlkes–Mallows index
  float FM() { return sqrt(PPV()*TPR()); };
  //  Bookmaker informedness
  float BM() { return TPR() + TNR() - 1; };
  //  markedness
  float MK() { return PPV() + NPV() - 1; };
  float deltaP() { return MK(); };
  //  diagnostic odds ratio
  float DOR() { return LRplus() / LRminus(); };


private:
  float P  = 0;
  float N  = 0;
  float TP = 0;
  float TN = 0;
  float FP = 0;
  float FN = 0;
};


// -- END OF FILE --

