//
//    FILE: GST.cpp
// VERSION: 0.1.4
// PURPOSE: Arduino library for Gold Standard Test metrics
//     URL: https://github.com/RobTillaart/GST
//          https://en.wikipedia.org/wiki/Sensitivity_and_specificity
//          https://en.wikipedia.org/wiki/Confusion_matrix
//
//  formula's based upon Wikipedia.


#include "GST.h"


GST::GST()
{
  clearAll();
};


///////////////////////////////////////////////////////
//
//  INPUT FUNCTIONS
//
void GST::setTruePositive(float v)
{
  TP = v;
  AP = TP + FN;
};


void GST::setTrueNegative(float v)
{
  TN = v;
  AN = TN + FP;
};


void GST::setFalsePositive(float v)
{
  FP = v;
  AN = TN + FP;
};


void GST::setFalseNegative(float v)
{
  FN = v;
  AP = TP + FN;
};


void GST::clearAll()
{
  AP = 0;
  AN = 0;
  TP = 0;
  TN = 0;
  FP = 0;
  FN = 0;
}


//  These are used for updating the test matrix
float GST::addTruePositive(float v)
{
  TP += v;
  AP = TP + FN;
  return TP;
};


float GST::addTrueNegative(float v)
{
  TN += v;
  AN = TN + FP;
  return TN;
};


float GST::addFalsePositive(float v)
{
  FP += v;
  AN = TN + FP;
  return FP;
};


float GST::addFalseNegative(float v)
{
  FN += v;
  AP = TP + FN;
  return FN;
};


///////////////////////////////////////////////////////
//
//  OUTPUT FUNCTIONS I
//
float GST::getTruePositive()   { return TP; };
float GST::getTrueNegative()   { return TN; };
float GST::getFalsePositive()  { return FP; };
float GST::getFalseNegative()  { return FN; };

float GST::getTotal()          { return AP + AN; };
float GST::getActualPositive() { return AP; };
float GST::getActualNegative() { return AN; };
float GST::getTestedPositive() { return TP + FP; };
float GST::getTestedNegative() { return TN + FN; };

float GST::sensitivity()       { return TPR(); };
float GST::specificity()       { return TNR(); };


float GST::truePositiveRate()  { return TPR(); };
float GST::TPR() { return TP / AP; };
float GST::trueNegativeRate()  { return TNR(); };
float GST::TNR() { return TN / AN; };
float GST::falseNegativeRate() { return FNR(); };
float GST::FNR() { return FN / AP; };
float GST::falsePositiveRate() { return FPR(); };
float GST::FPR() { return FP / AN; };


///////////////////////////////////////////////////////
//
//  OUTPUT FUNCTIONS II
//
float GST::positivePredictiveValue() { return PPV(); };
float GST::PPV() { return TP / (TP + FP); };
float GST::negativePredictiveValue() { return NPV(); };
float GST::NPV() { return TN / (TN + FN); };
float GST::falseDiscoveryRate() { return FDR(); };
float GST::FDR() { return FP / (TP + FP); };
float GST::falseOmissionRate() { return FOR(); };
float GST::FOR() { return FN / (TN + FN); };


float GST::positiveLikelihoodRatio() { return LRplus(); };
float GST::LRplus()  { return TPR() / FPR(); };
float GST::negativeLikelihoodRatio() { return LRminus(); };
float GST::LRminus() { return FNR() / TNR(); };


float GST::prevalenceThreshold()
{
  return sqrt(FPR()) / (sqrt(TPR()) + sqrt(FPR()));
};


float GST::threatScore()
{
  return TP / (TP + FN + FP);
};


float GST::criticalSuccessIndex()
{
  return threatScore();
};


float GST::prevalence()
{
  return AP / (AP + AN);
};


float GST::accuracy()
{
  return (TP + TN) / (AP + AN);
};


float GST::balancedAccuracy()
{
  return (TPR() + TNR()) * 0.5;
};


float GST::F1Score()
{
  return (2 * TP) / (2 * TP + FP + FN);
};


float GST::MatthewsCorrelationCoefficient() { return MCC(); };
float GST::phi() { return MCC(); };
float GST::MCC()
{
  return (TP*TN - FP*FN)/sqrt((TP+FP) * (TP+FN) * (TN+FP) * (TN+FN));
};


float GST::FowlkesMallowsIndex() { return FM(); };
float GST::FM()
{
  return sqrt(PPV()*TPR());
};


float GST::BookmakerInformedness() { return BM(); };
float GST::BM() 
{
  return TPR() + TNR() - 1;
};


float GST::markedness() { return MK(); };
float GST::deltaP() { return MK(); };
float GST::MK() 
{
  return PPV() + NPV() - 1;
};


float GST::diagnosticOddsRatio() { return DOR(); };
float GST::DOR()
{
  return LRplus() / LRminus();
};


//  -- END OF FILE --

