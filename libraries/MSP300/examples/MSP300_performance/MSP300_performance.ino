//
//    FILE: MSP300_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure I2C readPT timing MSP300 pressure transducer
//     URL: https://github.com/RobTillaart/MSP300


#include "MSP300.h"


MSP300 MSP(0x28);
volatile uint32_t x = 0;
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.println("MSP300_LIB_VERSION: ");
  Serial.println(MSP300_LIB_VERSION);
  Serial.println();

  Wire.begin();
  bool b = MSP.begin(100);
  Serial.println(b ? "true" : "false");
  Serial.println(MSP.isConnected());

  //  HEADER
  Serial.println();
  Serial.println("|  speed  | readP() | readPT() |");
  Serial.println("|:-------:|:-------:|:--------:|");
  //  TABLE
  for (uint32_t speed = 50000; speed <= 500000; speed += 50000)
  {
    Wire.setClock(speed);
    start = micros();
    x = MSP.readP();
    stop = micros();

    Serial.print("| ");
    Serial.print(speed);
    Serial.print(" | ");
    Serial.print(stop - start);
   delay(100);
    
    start = micros();
    x = MSP.readPT();
    stop = micros();
    Serial.print(" | ");
    Serial.print(stop - start);
    Serial.print(" |\n");
    delay(100);
  }
  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --
