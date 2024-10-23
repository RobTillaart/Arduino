//
//    FILE: INA228_demo_two_devices.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo core functions
//     URL: https://github.com/RobTillaart/INA228
//          based on discussion in issue #10.


#include "INA228.h"


INA228 INA1(0x45);
INA228 INA2(0x41);


void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  Wire.begin();
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
  Serial.print(INA1.getShuntVoltage_mV());
  Serial.print("\t");
  Serial.print(INA1.getCurrent_mA());
  Serial.print("\t");
  Serial.print(INA1.getPower_mW());
  Serial.print("\t");
  Serial.print(INA1.getTemperature());
  Serial.println();
  delay(1000);
  Serial.println("\nBUS\tSHUNT\tCURRENT\tPOWER\tTEMP");
  Serial.print(INA2.getBusVoltage());
  Serial.print("\t");
  Serial.print(INA2.getShuntVoltage_mV());
  Serial.print("\t");
  Serial.print(INA2.getCurrent_mA());
  Serial.print("\t");
  Serial.print(INA2.getPower_mW());
  Serial.print("\t");
  Serial.print(INA2.getTemperature());
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
