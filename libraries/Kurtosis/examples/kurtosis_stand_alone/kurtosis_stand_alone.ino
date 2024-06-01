//
//    FILE: kurtosis_stand_alone.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2024-05-26
// PURPOSE: stand alone kurtosis function
//     URL: https://github.com/RobTillaart/Kurtosis


//  #include "Kurtosis.h"

double arr[100];


//
//                size * sum( (arr[i] - average)^4 )
//  kurtosis() = ------------------------------------
//                   sum( (arr[i] - average)^2 )^2
//
double kurtosis(double *arr, uint16_t size)
{
  // Average
  double sum = 0;
  for (uint16_t i = 0; i < size; i++) sum += arr[i];
  double average = sum / size;

  //  sum((x - average)^2)
  //  sum((x - average)^4)
  double a = 0;
  double b = 0;
  for (uint16_t i = 0; i < size; i++)
  {
    double val = arr[i] - average;
    val *= val;  //  (arr[i] - average)^2
    b   += val;
    val *= val;  //  (arr[i] - average)^4
    a   += val;
  }

  return (size * a) / (b * b);
}


//                   sum( (arr[i] - average)^3 )
//                   ---------------------------
//                              size
//  skewness() = ------------------------------------
//                   sum( (arr[i] - average)^2 )^1.5
//                   ---------------------------
//                             size^1.5
//
//  simplified
//
//                sqrt(size) * sum( (arr[i] - average)^3 )
//  skewness() = ------------------------------------------
//                   sum( (arr[i] - average)^2 )^1.5
//
double skewness(double *arr, uint16_t size)
{
  //  average
  double sum = 0;
  for (uint16_t i = 0; i < size; i++) sum += arr[i];
  double average = sum / size;

  //  a = sum((x - average)^2)
  //  b = sum((x - average)^2)
  double a = 0;
  double b = 0;
  for (uint16_t i = 0; i < size; i++)
  {
    double val = arr[i] - average;
    double val2 = val * val;   //  (arr[i] - average)^2
    double val3 = val2 * val;  //  (arr[i] - average)^3
    b += val2;
    a += val3;
  }

  return sqrt(1.0 * size) * a * pow(b, -1.5);
}


///////////////////////////////////////////////////////////////////////
//
//  MAIN
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  //  fill array with random values.
  for (int i = 0; i < 100; i++)
  {
    arr[i] = 0.001 * random(i * 10);  //  skewed on purpose
  }

  Serial.println();
  delay(100);

  Serial.println();
  Serial.println("COUNT:\t100");
  Serial.print("KURTOSIS:\t");
  Serial.println(kurtosis(arr, 100), 3);
  Serial.print("SKEWNESS:\t");
  Serial.println(skewness(arr, 100), 3);
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --
