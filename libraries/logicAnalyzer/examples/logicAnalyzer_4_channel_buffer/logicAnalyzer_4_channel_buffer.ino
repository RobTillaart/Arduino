//
//    FILE: logicAnalyzer_4_channel_buffer.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: experimental time length compression (TEST)
//     URL: https://github.com/RobTillaart/logicAnalyzer
//
//  EXPERIMENTAL
//  a circular buffer measures the duration in millis() + value
//  as long as there are no or few changes a relative small circular
//  buffer can hold quite some data.


#include "logicAnalyzer.h"

//  hardcoded simple circular buffer with internal duration counter.
//  might be a library of its own.
class TLC_Buffer
{
  public:
    TLC_Buffer()
    {
      //  TODO allocate dynamic buffer...
      reset();
    }

    void reset()
    {
      _lastTime = 0;
      _lastValue = 0;
      _index = 0;
      _buffer[0] = 0;
      _times[0] = 0;
    }

    void writeValue(uint32_t value)
    {
      //  do we have a new value?
      if (value == _lastValue) return;
      _lastValue = value;
      //  write duration of previous value first.
      _times[_index++] = millis() - _lastTime;
      _lastTime = millis();
      //  buffer the next value.
      _buffer[_index] = value;
    }

    uint32_t readValue(uint32_t index)
    {
      return _buffer[index];
    }

    uint32_t readDuration(uint32_t index)
    {
      return _times[index];
    }

    uint32_t size()
    {
      return _index;
    }

  private:
    //  1024 bytes in total
    uint32_t _buffer[128];
    uint32_t _times[128];
    uint32_t _index;
    uint32_t _lastTime;
    uint32_t _lastValue;
}  B;


logicAnalyzer LA;

uint8_t dataPins[] = { 8, 9, 10, 11 };

uint32_t lastMeasurement;


void setup()
{
  Serial.begin(1000000);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LOGICANALYZER_LIB_VERSION: ");
  Serial.println(LOGICANALYZER_LIB_VERSION);
  Serial.println();

  LA.configPins(dataPins, 4);
  lastMeasurement = LA.sample();
}


void loop()
{
  //  might take a while before the buffer is filled.
  uint32_t measurement = LA.sample();
  B.writeValue(measurement);
  //  Serial.print(B.size());
  //  Serial.print('\t');
  //  Serial.println(measurement);
  if (B.size() >= 100)
  {
    //  decompress & print
    for (int i = 0; i < 100; i++)
    {
      uint32_t dur = B.readDuration(i);
      uint32_t val = B.readValue(i);
      //      Serial.print(dur);
      //      Serial.print('\t');
      //      Serial.println(val);

      LA.inject(val);
      for (uint32_t j = 0; j < dur; j++)
      {
        LA.plot();
      }
    }
    // Serial.println(LA.getCount());
    while (1);
  }
}


//  -- END OF FILE --
