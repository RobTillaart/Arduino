//
//    FILE: INA3221_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance 1 channel
//     URL: https://github.com/RobTillaart/INA3221_RT


#include "INA3221.h"


INA3221 INA(0x40);
uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA3221_LIB_VERSION: ");
  Serial.println(INA3221_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  else
  {
    Serial.print("Found: \t");
    Serial.println(INA.getAddress());
  }

  Serial.print("DieID: \t");
  Serial.println(INA.getDieID(), HEX);
  Serial.print("ManID: \t");
  Serial.println(INA.getManufacturerID(), HEX);
  Serial.print(" Conf: \t");
  Serial.println(INA.getConfiguration(), HEX);

  //  overwrite default shunts.
  INA.setShuntR(0, 0.100);
  INA.setShuntR(1, 0.102);
  INA.setShuntR(2, 0.099);

  performance(100000);
  performance(200000);
  performance(300000);
  performance(400000);
}


void performance(uint32_t speed)
{
  Wire.setClock(speed);
  Serial.print("\nSpeed:\t");
  Serial.println(speed);

  delay(100);  // fllussssh IO

  start = micros();
  float busVoltage = INA.getBusVoltage(1);
  stop = micros();
  Serial.print("BUS V:\t");
  Serial.print(busVoltage, 3);
  Serial.print("\t");
  Serial.println(stop - start);

  delay(100);

  start = micros();
  float shuntVoltage = INA.getShuntVoltage_mV(1);
  stop = micros();
  Serial.print("SHUNT mV:\t");
  Serial.print(shuntVoltage, 3);
  Serial.print("\t");
  Serial.println(stop - start);

  delay(100);

  start = micros();
  float mA = INA.getCurrent_mA(1);
  stop = micros();
  Serial.print("mA:\t");
  Serial.print(mA, 3);
  Serial.print("\t");
  Serial.println(stop - start);

  delay(100);

  start = micros();
  float mW = INA.getPower_mW(1);
  stop = micros();
  Serial.print("mW:\t");
  Serial.print(mW, 3);
  Serial.print("\t");
  Serial.println(stop - start);
}


void loop()
{
}

//  -- END OF FILE --
