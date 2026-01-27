//
//    FILE: BL0942_SPI_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0942_SPI
//
//  need low level readRegister to be public.


#include "BL0942_SPI.h"


//BL0942_SPI mySensor(4, 5, 6, 7);
BL0942_SPI mySensor(255, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0942_SPI_LIB_VERSION: ");
  Serial.println(BL0942_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  numbers from the BL0942 APP NOTE
  float RF = (390000.0 * 5 + 510.0) / 510.0;
  float SHUNT = 0.001;

  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  Serial.println("dump all registers in HEX\n");

  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.readRegister(0x01) & 0xFFFFF, HEX);
  Serial.print("BL0942_REG_V_WAVE:\t");
  Serial.println(mySensor.readRegister(0x02) & 0xFFFFF, HEX);
  Serial.print("BL0942_REG_I_RMS:\t");
  Serial.println(mySensor.readRegister(0x03) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_V_RMS:\t");
  Serial.println(mySensor.readRegister(0x04) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_I_FAST_RMS:\t");
  Serial.println(mySensor.readRegister(0x05) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_WATT:\t");
  Serial.println(mySensor.readRegister(0x06) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_CF_CNT:\t");
  Serial.println(mySensor.readRegister(0x07) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_FREQ:\t");
  Serial.println(mySensor.readRegister(0x08) & 0xFFFF, HEX);
  Serial.print("BL0942_REG_STATUS:\t");
  Serial.println(mySensor.readRegister(0x09) & 0x3FF, HEX);
  Serial.print("BL0942_REG_I_RMSOS:\t");
  Serial.println(mySensor.readRegister(0x12) & 0xFF, HEX);
  Serial.print("BL0942_REG_WA_CREEP:\t");
  Serial.println(mySensor.readRegister(0x14) & 0xFF, HEX);
  Serial.print("BL0942_REG_I_FAST_RMS_TH:\t");
  Serial.println(mySensor.readRegister(0x15) & 0xFFFF, HEX);
  Serial.print("BL0942_REG_I_FAST_RMS_CYC:\t");
  Serial.println(mySensor.readRegister(0x16) & 0x07, HEX);
  Serial.print("BL0942_REG_FREQ_CYC:\t");
  Serial.println(mySensor.readRegister(0x17) & 0x03, HEX);
  Serial.print("BL0942_REG_OT_FUNX:\t");
  Serial.println(mySensor.readRegister(0x18) & 0x3F, HEX);
  Serial.print("BL0942_REG_MODE:\t");
  Serial.println(mySensor.readRegister(0x19) & 0x3FF, HEX);
  Serial.print("BL0942_REG_GAIN_CR:\t");
  Serial.println(mySensor.readRegister(0x1A) & 0x03, HEX);
  Serial.print("BL0942_REG_SOFT_RESET:\t");
  Serial.println(mySensor.readRegister(0x1C) & 0xFFFFFF, HEX);
  Serial.print("BL0942_REG_USR_WRPROT:\t");
  Serial.println(mySensor.readRegister(0x1D) & 0xFF, HEX);

}


void loop()
{

  delay(2000);
}


//  -- END OF FILE --
