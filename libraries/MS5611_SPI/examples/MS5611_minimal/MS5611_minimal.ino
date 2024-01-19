//
//    FILE: MS5611_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//     URL: https://github.com/RobTillaart/MS5611_SPI


#include "MS5611_SPI.h"


//  BREAKOUT  MS5611  aka  GY63 - see datasheet
//
//  SPI    I2C
//              +--------+
//  VCC    VCC  | o      |
//  GND    GND  | o      |
//         SCL  | o      |
//  SDI    SDA  | o      |
//  CSO         | o      |
//  SDO         | o L    |   L = led
//          PS  | o    O |   O = opening  PS = protocol select
//              +--------+
//
//  PS to VCC  ==>  I2C  (GY-63 board has internal pull up, so not needed)
//  PS to GND  ==>  SPI
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77


//  SPI      UNO/NANO    ESP32 (V)  ESP32(H)
//  SELECT    10            5         15
//  MOSI      11            23        13
//  MISO      12            19        12
//  CLOCK     13            18        14


// MS5611_SPI(select, dataOut, dataIn, clock);
// --------------------------------------------
// MS5611_SPI MS5611(10, 11, 12, 13);   // UNO SW SPI (5V problem?
// MS5611_SPI MS5611(10);               // UNO  HW SPI
//
// MS5611_SPI MS5611( 5, 23, 19, 18);   // ESP32 SW SPI
MS5611_SPI MS5611(15, 13, 12, 14);   // ESP32 SW SPI
//
// SPIClass *mySPI = new SPIClass(HSPI);
// MS5611_SPI MS5611(15, mySPI);        // ESP32 HW SPI (HSPI)
// SPIClass *mySPI = new SPIClass(VSPI);
// MS5611_SPI MS5611(5, mySPI);                // ESP32 HW SPI (VSPI)


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5611_SPI_LIB_VERSION: ");
  Serial.println(MS5611_SPI_LIB_VERSION);

  SPI.begin();

  if (MS5611.begin() == true)
  {
    Serial.print("MS5611 found: ");
    Serial.println(MS5611.getDeviceID(), HEX);
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1);
  }
  Serial.println();
}


void loop()
{
  //  MS5611.reset();
  uint32_t start = micros();
  MS5611.read();           //  note no error checking => "optimistic".
  uint32_t stop = micros();
  Serial.print("T:\t");
  Serial.print(MS5611.getTemperature(), 2);
  Serial.print("\tP:\t");
  Serial.print(MS5611.getPressure(), 2);
  Serial.print("\tt:\t");
  Serial.print(stop - start);
  Serial.println();
  delay(2000);
}


//  -- END OF FILE --
