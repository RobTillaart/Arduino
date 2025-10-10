//
//    FILE: SHT4x_two_I2C.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo two I2C busses
//     URL: https://github.com/RobTillaart/SHT4x
//
//   NOTE: see issue #22 (SHT31) for details
//         originally written for a ATSAMD21G18A custom board.

/*
For async call:
requestData(measurementType = SHT4x_MEASUREMENT_SLOW);

For sync call:
read(uint8_t measurementType = SHT4x_MEASUREMENT_SLOW, bool errorCheck = true);

| measurement type                    |  duration  |  heater  |  power   |  notes  |
|:-----------------------------------:|:----------:|:--------:|:--------:|:-------:|
| SHT4x_MEASUREMENT_SLOW              |     9 ms   |     N    |     -    | default |
| SHT4x_MEASUREMENT_MEDIUM            |     5 ms   |     N    |     -    |
| SHT4x_MEASUREMENT_FAST              |     2 ms   |     N    |     -    |
| SHT4x_MEASUREMENT_LONG_HIGH_HEAT    |  1100 ms   |     Y    |  200 mW  |
| SHT4x_MEASUREMENT_LONG_MEDIUM_HEAT  |  1100 ms   |     Y    |  110 mW  |
| SHT4x_MEASUREMENT_LONG_LOW_HEAT     |  1100 ms   |     Y    |   20 mW  |
| SHT4x_MEASUREMENT_SHORT_HIGH_HEAT   |   110 ms   |     Y    |  200 mW  |
| SHT4x_MEASUREMENT_SHORT_MEDIUM_HEAT |   110 ms   |     Y    |  110 mW  |
| SHT4x_MEASUREMENT_SHORT_LOW_HEAT    |   110 ms   |     Y    |   20 mW  |

*/

#include "Wire.h"
#include "SHT4x.h"


// TwoWire myWire(&sercom5, 0, 1);
TwoWire myWire = Wire1;       //  test.


// note: address reuse on second I2C bus
#define SHT4x_ADDRESS_1   0x44
#define SHT4x_ADDRESS_2   0x45
#define SHT4x_ADDRESS_3   0x44
#define SHT4x_ADDRESS_4   0x45


SHT4x sht_1(SHT4x_ADDRESS_1, &Wire);
SHT4x sht_2(SHT4x_ADDRESS_2, &Wire);
SHT4x sht_3(SHT4x_ADDRESS_3, &myWire);
SHT4x sht_4(SHT4x_ADDRESS_4, &myWire);


bool b1, b2, b3, b4;


void setup()
{
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SHT4x_LIB_VERSION: \t");
  Serial.println(SHT4x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  myWire.begin();
  myWire.setClock(100000);

  //  see datasheet for details
  //  pinPeripheral(0, PIO_SERCOM_ALT);
  //  pinPeripheral(1, PIO_SERCOM_ALT);

  b1 = sht_1.begin();
  b2 = sht_2.begin();
  b3 = sht_3.begin();
  b4 = sht_4.begin();

  //  see if they are connected
  Serial.print("BEGIN:\t");
  Serial.print(b1);
  Serial.print("\t");
  Serial.print(b2);
  Serial.print("\t");
  Serial.print(b3);
  Serial.print("\t");
  Serial.print(b4);
  Serial.print("\t");
  Serial.println();
}


void loop()
{
  //  request data on all sensors that are found
  if (b1) sht_1.requestData();
  if (b2) sht_2.requestData();
  if (b3) sht_3.requestData();
  if (b4) sht_4.requestData();

  // wait for all data to be ready
  if (b1) while(!sht_1.dataReady()) yield();
  if (b2) while(!sht_2.dataReady()) yield();
  if (b3) while(!sht_3.dataReady()) yield();
  if (b4) while(!sht_4.dataReady()) yield();

  Serial.print(sht_1.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_2.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_3.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_4.getTemperature(), 1);
  Serial.print("\t");
  Serial.print(sht_1.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_2.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_3.getHumidity(), 1);
  Serial.print("\t");
  Serial.print(sht_4.getHumidity(), 1);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --
