//
//    FILE: INA229_demo_two_devices.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA229
//          based on discussion in issue #10.

#include "INA229.h"

//  select, dataIn, dataOut, clock == SOFTWARE SPI
INA229 INA1(5, 6, 7, 8);
//  select, &SPI === HW SPI
INA229 INA2(9, &SPI);


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA229_LIB_VERSION: ");
  Serial.println(INA229_LIB_VERSION);
  Serial.println();

  SPI.begin();
  if (!INA1.begin())
  {
    Serial.println("Could not connect INA1. Fix and Reboot");
    while (1);
  }
  if (!INA2.begin())
  {
    Serial.println("Could not connect INA2. Fix and Reboot");
    while (1);
  }

  INA1.setMaxCurrentShunt(10, 0.0002);
  INA2.setMaxCurrentShunt(10, 0.0002);
}


void loop() {
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");

  Serial.print(INA1.getBusVoltage());
  Serial.print("\t");
  Serial.print(INA1.getShuntMilliVolt());
  Serial.print("\t");
  Serial.print(INA1.getMilliAmpere());
  Serial.print("\t");
  Serial.print(INA1.getMilliWatt());
  Serial.print("\t");
  Serial.print(INA1.getTemperature());
  Serial.println();
  delay(1000);
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  Serial.print(INA2.getBusVoltage());
  Serial.print("\t");
  Serial.print(INA2.getShuntMilliVolt());
  Serial.print("\t");
  Serial.print(INA2.getMilliAmpere());
  Serial.print("\t");
  Serial.print(INA2.getMilliWatt());
  Serial.print("\t");
  Serial.print(INA2.getTemperature());
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
