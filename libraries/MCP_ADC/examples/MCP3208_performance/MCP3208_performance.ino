//
//    FILE: MCP3208_performance.ino
//  AUTHOR: Rob Tillaart, Alex Uta
// PURPOSE: simple performance measurement for MCP3208
//     URL: https://github.com/RobTillaart/MCP_ADC


#include "MCP_ADC.h"


MCP3208 mcp28;
#define MCP3208_CS_PIN 25

uint32_t start, stop, 
         analog_read_time,
         analog_read_multiple_time;

const uint8_t num_channels = 8;
uint8_t channels_list[num_channels] = {
    0,1,2,3,4,5,6,7
};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP_ADC_LIB_VERSION: ");
  Serial.println(MCP_ADC_LIB_VERSION);

  SPI.begin();

  Serial.println();
  Serial.println("ADC\tCHAN\tMAXVALUE");
  Serial.print("mcp28\t");
  Serial.print(mcp28.channels());
  Serial.print("\t");
  Serial.println(mcp28.maxValue());

  Serial.println("\nTiming in micros().\n");
  delay(10);

  Serial.println("***************************************\n");
  for (int s = 1; s <= 16; s++)
  {
    Serial.println(s * 1000000UL);
    mcp28.setSPIspeed(s * 1000000UL);
    mcp28.begin(MCP3208_CS_PIN);
    test();
  }

  testChannelsRead();
  Serial.println("done...");
}


void loop()
{
}


void test()
{
  uint32_t val = 0;

  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.read(channel);
  }
  stop = micros();
  analog_read_time = stop - start;
  
  Serial.print("mcp28.read()\t8x: \t");
  Serial.println(analog_read_time);
  delay(10);


  start = micros();
  int16_t readings[num_channels];
  
  mcp28.readMultiple(channels_list, num_channels, readings);
  stop = micros();
  analog_read_multiple_time = stop - start;

  Serial.print("mcp28.readMultiple()\t8x: \t");
  Serial.println(stop - start);

  Serial.print("read() time / readMultiple() time \t");
  Serial.println((1.0 * analog_read_time) / analog_read_multiple_time);
  delay(10);


  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.differentialRead(channel);
  }
  stop = micros();
  Serial.print("mcp28.differentialRead() 8x: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  for (int channel = 0; channel < mcp28.channels(); channel++)
  {
    val += mcp28.deltaRead(channel);
  }
  stop = micros();
  Serial.print("mcp28.deltaRead()\t8x: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(10);

}


void testChannelsRead() {
  Serial.println("***************************************\n");

  mcp28.setSPIspeed(8000000);  //  8 MHz
  mcp28.begin(MCP3208_CS_PIN);
  Serial.println("8000000");

  for (uint8_t numChannelsToRead = 1; numChannelsToRead <= num_channels; numChannelsToRead++) {

    delay(10);

    //  read()
    start = micros();
    for (uint8_t i = 0; i < numChannelsToRead; i++) {
      mcp28.read(i);
    }
    stop = micros();
    analog_read_time = stop - start;

    Serial.print("mcp28.read()\t");
    Serial.print(numChannelsToRead);
    Serial.print(": \t");
    Serial.print(analog_read_time);
    Serial.println("");

    //  readMultiple()
    uint8_t channels_list[numChannelsToRead];
    for (uint8_t i = 0; i < numChannelsToRead; i++) {
      channels_list[i] = i;
    }

    delay(10);

    int16_t readings[numChannelsToRead];
    start = micros();
    mcp28.readMultiple(channels_list, numChannelsToRead, readings);
    stop = micros();
    analog_read_multiple_time = stop - start;

    Serial.print("mcp28.readMultiple()\t");
    Serial.print(numChannelsToRead);
    Serial.print(": \t");
    Serial.println(analog_read_multiple_time);

    Serial.print("read() time / readMultiple() time \t");
    Serial.println((1.0 * analog_read_time) / analog_read_multiple_time, 2);  //  print as float
    
    Serial.println("\n");
    delay(10);
  }

}


//  -- END OF FILE --
