//
//    FILE: INA226_USI_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/INA226_USI
//
//  compiles ATtiny85 (38% PROGMEM, 54 bytes RAM)
//           ATtiny45 (77% PROGMEM, 54 bytes RAM)
//  compiles ATtiny84 (38% PROGMEM, 54 bytes RAM)
//           ATtiny44 (77% PROGMEM, 54 bytes RAM)


#include "INA226_USI.h"


INA226 INA(0x40);

uint8_t LED1 = 2;
uint8_t LED2 = 3;


void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  TinyWireM.begin();
  INA.begin();
  INA.setAverage(2);
  delay(100);

  INA.setMaxCurrentShunt(1, 0.002);
}


void loop()
{
  float bv = INA.getBusVoltage();
  digitalWrite(LED1, bv > 4);

  float cu = INA.getCurrent_mA();
  digitalWrite(LED2, cu > 20);
}


//  -- END OF FILE --
