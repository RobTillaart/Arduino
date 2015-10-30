//
//    FILE: runningMedianTest1.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: test functionality
//    DATE: 2013-10-28
//     URL:
//
// Released to the public domain
//

// RunningMedianTest1.ino

#include <RunningMedian.h>

const int sourceData[] =
{ // 50 consecutive samples from Sharp distance sensor model GP2Y0A710K0F while stationary.
  300, 299, 296, 343, 307, 304, 303, 305, 300, 340,
  308, 305, 300, 304, 311, 304, 300, 300, 304, 304,
  284, 319, 306, 304, 300, 302, 305, 310, 306, 304,
  308, 300, 299, 304, 300, 305, 307, 303, 326, 311,
  306, 304, 305, 300, 300, 307, 302, 305, 296, 300
};
const int sourceSize = (sizeof(sourceData)/sizeof(sourceData[0]));

RunningMedian samples = RunningMedian(sourceSize);

void setup()
{
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect. Needed for Leonardo only.
  delay(1000); // Simply to allow time for the ERW versions of the IDE time to automagically open the Serial Monitor. 1 second chosen arbitrarily.
  Serial.print(F("Running Median Version: "));
  Serial.println(RUNNING_MEDIAN_VERSION);
#ifdef RUNNING_MEDIAN_ALL
  Serial.println(F("All methods available"));
#else
  Serial.println(F("Only constructor, destructor, clear(), add(), and getMedian() available"));
#endif
#ifdef RUNNING_MEDIAN_USE_MALLOC
  Serial.println(F("Dynamic version using malloc() enabled"));
#else
  Serial.print(F("Static version, will always allocate an array of "));
  Serial.print(MEDIAN_MAX_SIZE,DEC);
  Serial.println(F(" floats."));
#endif
}

void loop()
{
  test1();
  while (1);
}

void test1()
{
  unsigned long timerStart = 0;
  unsigned long timerStop = 0;
  float resultFLOAT = 0;
  byte resultBYTE = 0;

  Serial.print(F("Requested median array size = "));
  Serial.println(sourceSize,DEC);
  Serial.print(F("Actual allocated size = "));
  Serial.println(samples.getSize(),DEC);

  Serial.println();

  for(byte i = 0; i <= (sourceSize - 1); i++)
  {
    Serial.print(F("Loop number "));
    Serial.println((i + 1),DEC);

    timerStart = micros();
    samples.add(sourceData[i]);
    timerStop = micros();
    Serial.print(F("Time to add the next element to the array = "));
    Serial.print(timerStop - timerStart);
    Serial.println(F(" microseconds."));

    Serial.println(F("Cumulative source data added:"));
    Serial.print(F("    "));
    for(byte j = 0; j <= i; j++)
    {
      Serial.print(sourceData[j]);
      Serial.print(F(" "));
    }
    Serial.println();

    Serial.println(F("Unsorted accumulated array:"));
    Serial.print(F("    "));
    for(byte j = 0; j < samples.getCount(); j++)
    {
      Serial.print(samples.getElement(j));
      Serial.print(F(" "));
    }
    Serial.println();

    timerStart = micros();
    resultFLOAT = samples.getSortedElement(0);
    timerStop = micros();
    Serial.print(F("Time to sort array and return element number zero = "));
    Serial.print(timerStop - timerStart);
    Serial.println(F(" microseconds."));

    Serial.println(F("Sorted accumulated array:"));
    Serial.print(F("    "));
    for(byte j = 0; j < samples.getCount(); j++)
    {
      Serial.print(samples.getSortedElement(j));
      Serial.print(F(" "));
    }
    Serial.println();

    timerStart = micros();
    resultFLOAT = samples.getMedian();
    timerStop = micros();
    Serial.print(F("getMedian() result = "));
    Serial.println(resultFLOAT);
    Serial.print(F("Time to execute getMedian() = "));
    Serial.print(timerStop - timerStart);
    Serial.println(F(" microseconds."));

    timerStart = micros();
    resultFLOAT = samples.getAverage();
    timerStop = micros();
    Serial.print(F("getAverage() result = "));
    Serial.println(resultFLOAT);
    Serial.print(F("Time to execute getAverage() = "));
    Serial.print(timerStop - timerStart);
    Serial.println(F(" microseconds."));

    Serial.println(F("getAverage(x) results where:"));
    for(byte j = 1; j <= samples.getCount(); j++)
    {
      timerStart = micros();
      resultFLOAT = samples.getAverage(j);
      timerStop = micros();
      Serial.print(F("  x = "));
      Serial.print(j);
      Serial.print(F(" => "));
      Serial.print(resultFLOAT);
      Serial.print(F(" Time to execute = "));
      Serial.print(timerStop - timerStart);
      Serial.println(F(" microseconds."));
    }

    Serial.println(F("predict(x) results where:"));
    for(byte j = 1; j <= (samples.getCount() / 2); j++)
    {
      timerStart = micros();
      resultFLOAT = samples.predict(j);
      timerStop = micros();
      Serial.print(F("  x = "));
      Serial.print(j);
      Serial.print(F(" => "));
      Serial.print(resultFLOAT);
      Serial.print(F(" Time to execute = "));
      Serial.print(timerStop - timerStart);
      Serial.println(F(" microseconds."));
    }

    Serial.println();
    Serial.println();
  }
}