//
//    FILE: ADC081S_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance measurement for ADC081S SPI based ADC
//     URL: https://github.com/RobTillaart/ADC081S
//


#include "ADC081S.h"

ADC081S adc;  //  HW SPI
// ADC081S adc(6, 7);    //  SW SPI UNO   - adjust pins if needed
// ADC081S adc(20, 21);  //  SW SPI ESP32 - adjust pins if needed
const uint8_t SELECT_PIN = 10;

uint32_t start, stop, read_time;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADC081S_LIB_VERSION: ");
  Serial.println(ADC081S_LIB_VERSION);
  Serial.println();

  SPI.begin();

  Serial.println("ADC\tMAXVALUE");
  Serial.print("adc\t");
  Serial.println(adc.maxValue());
  Serial.println("\nTiming in micros().\n");
  delay(100);

  Serial.println("***************************************\n");
  for (int s = 1; s <= 64; s++)
  {
    uint32_t val = 0;
    uint32_t speed = s * 1000000UL;
    adc.setSPIspeed(speed);
    adc.begin(SELECT_PIN);

    delay(100);
    start = micros();
    for (int i = 0; i < 1000; i++)
    {
    val += adc.read();
    }
    stop = micros();
    read_time = stop - start;

    Serial.print(speed);
    Serial.print("\tadc.read()\t");
    Serial.print(read_time);
    Serial.print("\t");
    Serial.println(val);
    delay(100);
  }

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --
