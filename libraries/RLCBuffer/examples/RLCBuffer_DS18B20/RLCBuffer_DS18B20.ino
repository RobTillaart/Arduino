//
//    FILE: RLCBuffer_DS18B20.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/RLCBuffer
//
//  does not work nice for negative temperatures (or disconnect)
//

#include "RLCBuffer.h"
RLCBuffer RLCB(100);

#include "DS18B20.h"

#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RLCBUFFER_LIB_VERSION: ");
  Serial.println(RLCBUFFER_LIB_VERSION);
  Serial.print("DS18B20_LIB_VERSION: ");
  Serial.println(DS18B20_LIB_VERSION);
  Serial.println();
  Serial.println("test takes about a minute.");

  if (RLCB.begin() == false)
  {
    Serial.println("RLCB failed allocating mem");
    while (1);
  }
  Serial.print("SIZE:\t");  Serial.println(RLCB.size());
  Serial.print("COUNT:\t");  Serial.println(RLCB.count());
  Serial.println();

  sensor.begin();

  //  fill the buffer with random numbers and generate different timestamps
  for (int i = 0; i < 60; i++)
  {
    sensor.requestTemperatures();
    delay(500);
    //  use integer part only
    int temp = sensor.getTempC();

    //  catch negative temp + error codes.
    if (temp < 0) temp = 200 - temp;
    Serial.println(temp);
    RLCB.writeData(temp);
  }

  Serial.print("SIZE:\t");  Serial.println(RLCB.size());
  Serial.print("COUNT:\t");  Serial.println(RLCB.count());
  Serial.println();

  for (int i = 0; i <= RLCB.count(); i++)
  {
    Serial.print(RLCB.readCount(i));
    Serial.print('\t');
    Serial.println(RLCB.readData(i));
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
