//
//    FILE: BL0940_SPI_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0940_SPI
//
//  need low level readRegister to be public.


#include "BL0940_SPI.h"


//BL0940_SPI mySensor(4, 5, 6, 7);
BL0940_SPI mySensor(255, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0940_SPI_LIB_VERSION: ");
  Serial.println(BL0940_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  numbers from the BL0940 APP NOTE
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;

  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor = scalar.


  Serial.println("dump RO registers in HEX\n");

  Serial.print("BL0940_REG_I_FAST_RMS:\t");
  Serial.println(mySensor.readRegister(0x00) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_I_WAVE:\t");
  Serial.println(mySensor.readRegister(0x01) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_V_WAVE:\t");
  Serial.println(mySensor.readRegister(0x03) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_I_RMS:\t");
  Serial.println(mySensor.readRegister(0x04) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_V_RMS:\t");
  Serial.println(mySensor.readRegister(0x06) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_WATT:\t");
  Serial.println(mySensor.readRegister(0x08) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_CF_CNT:\t");
  Serial.println(mySensor.readRegister(0x0A) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_ANGLE:\t");
  Serial.println(mySensor.readRegister(0x0C) & 0xFFFF, HEX);
  Serial.print("BL0940_REG_INT_TEMP:\t");
  Serial.println(mySensor.readRegister(0x0E) & 0x3FF, HEX);
  Serial.print("BL0940_REG_EXT_TEMP:\t");
  Serial.println(mySensor.readRegister(0x0F) & 0x3FF, HEX);

  Serial.println("\ndump RW registers in HEX\n");

  Serial.print("BL0940_REG_I_FAST_RMS_CTRL:\t");
  Serial.println(mySensor.readRegister(0x10) & 0xFFFF, HEX);
  Serial.print("BL0940_REG_I_RMSOS:\t");
  Serial.println(mySensor.readRegister(0x13) & 0xFF, HEX);
  Serial.print("BL0940_REG_WATTOS:\t");
  Serial.println(mySensor.readRegister(0x15) & 0xFF, HEX);
  Serial.print("BL0940_REG_WA_CREEP:\t");
  Serial.println(mySensor.readRegister(0x17) & 0xFF, HEX);
  Serial.print("BL0940_REG_MODE:\t");
  Serial.println(mySensor.readRegister(0x18) & 0xFFFF, HEX);
  Serial.print("BL0940_REG_SOFT_RESET:\t");
  Serial.println(mySensor.readRegister(0x19) & 0xFFFFFF, HEX);
  Serial.print("BL0940_REG_USR_WRPROT:\t");
  Serial.println(mySensor.readRegister(0x1A) & 0xFF, HEX);
  Serial.print("BL0940_REG_TEMP_CTRL:\t");
  Serial.println(mySensor.readRegister(0x1B) & 0xFFFF, HEX);
  Serial.print("BL0940_REG_EXT_TEMP_GAIN:\t");
  Serial.println(mySensor.readRegister(0x1C) & 0xFF, HEX);
  Serial.print("BL0940_REG_EXT_TEMP_OS:\t");
  Serial.println(mySensor.readRegister(0x1D) & 0xFF, HEX);
}


void loop()
{

  delay(2000);
}


//  -- END OF FILE --
