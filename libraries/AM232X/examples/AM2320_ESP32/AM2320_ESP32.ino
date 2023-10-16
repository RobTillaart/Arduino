//
//    FILE: AM2320_ESP32.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: AM2320 demo sketch for AM2320 I2C humidity & temperature sensor
//          with second I2C port of ESP32
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
//  do not forget pull up resistors between SDA, SCL and VDD..


#include "AM232X.h"

#define pd_scl_dht 14
#define pd_sda_dht 27

TwoWire I2C_IMU = TwoWire(0);   //  I2C1 bus
TwoWire I2C_DHT = TwoWire(1);   //  I2C2 bus


AM232X AM2320(&I2C_DHT);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  I2C_IMU.begin();
  I2C_DHT.begin(pd_sda_dht, pd_scl_dht, 100000ul);
  
  if (! AM2320.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }
  AM2320.wakeUp();
  delay(2000);

  Serial.println("Type,\tStatus,\tHumidity (%),\tTemperature (C)");
}


void loop()
{
  //  READ DATA
  Serial.print("AM2320, \t");
  int status = AM2320.read();
  switch (status)
  {
    case AM232X_OK:
      Serial.print("OK,\t");
      break;
    default:
      Serial.print(status);
      Serial.print("\t");
      break;
  }
  //  DISPLAY DATA, sensor only returns one decimal.
  Serial.print(AM2320.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(AM2320.getTemperature(), 1);

  delay(2000);
}


//  -- END OF FILE --
