//
//    FILE: I2C_eeprom_struct.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo I2C_EEPROM library store /retrieve struct
//     URL: https://github.com/RobTillaart/I2C_EEPROM
//
//  uses a 24LC256 (32KB) EEPROM
//  as this test writes a lot it might wear out EEPROMs eventually.
//


#include "Wire.h"
#include "I2C_eeprom.h"


I2C_eeprom ee(0x50, I2C_DEVICESIZE_24LC256);

uint32_t start, duration;

struct
{
  float temperature;
  float humidity;
  float pressure;
} measurement;


void setup()
{
  Serial.begin(115200);
  while (!Serial);  //  wait for Serial port to connect. Needed for Leonardo only
  Serial.println(__FILE__);
  Serial.print("I2C_EEPROM_VERSION: ");
  Serial.println(I2C_EEPROM_VERSION);

  Wire.begin();

  ee.begin();
  if (! ee.isConnected())
  {
    Serial.println("ERROR: Can't find eeprom (stopped)...");
    // while (1);
  }

  Serial.print("size: \t");
  Serial.println(sizeof(measurement));

  //  clear EEPROM part
  ee.setBlock(0, 0, sizeof(measurement));

  //  make measurement here
  measurement.temperature = 22.5;
  measurement.humidity    = 53.1;
  measurement.pressure    = 1000.9;

  //  store it in EEPROM
  start = micros();
  ee.writeBlock(0, (uint8_t *) &measurement, sizeof(measurement));
  duration = micros() - start;
  Serial.print("write: \t");
  Serial.println(duration);
  delay(10);

  //  clear measurement struct
  measurement.temperature = 0;
  measurement.humidity    = 0;
  measurement.pressure    = 0;

  //  retrieve old measurement
  start = micros();
  ee.readBlock(0, (uint8_t *) &measurement, sizeof(measurement));
  duration = micros() - start;
  Serial.print("read: \t");
  Serial.println(duration);
  delay(10);

  Serial.print("temp:\t");
  Serial.println(measurement.temperature);
  Serial.print("hum:\t");
  Serial.println(measurement.humidity);
  Serial.print("pres:\t");
  Serial.println(measurement.pressure);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE

