  //
//    FILE: BL0940_SPI_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0940_SPI


#include "BL0940_SPI.h"


BL0940_SPI mySensor(4, 5, 6, 7);


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
  
  mySensor.calibrate(SHUNT, RF);  //  shunt in ohm, reduction factor voltage.


  Serial.println("get all registers");
  Serial.println("READ ONLY\n");

  Serial.print("BL0940_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  Serial.print("BL0940_REG_V_WAVE:\t");
  Serial.println(mySensor.getVWave());
  Serial.print("BL0940_REG_I_RMS:\t");
  Serial.println(mySensor.getIRMS());
  Serial.print("BL0940_REG_V_RMS:\t");
  Serial.println(mySensor.getVRMS());

  Serial.print("BL0940_REG_I_FAST_RMS:\t");
  Serial.println(mySensor.getIRMSFast());
  Serial.print("BL0940_REG_WATT:\t");
  Serial.println(mySensor.getWatt());
  Serial.print("BL0940_REG_CF_CNT:\t");
  Serial.println(mySensor.getCFPulseCount());

  Serial.print("BL0940_REG_ANGLE:\t");
  Serial.println(mySensor.getPhaseAngle());
  Serial.print("BL0940_REG_INT_TEMP:\t");
  Serial.println(mySensor.getIntTemperature(), HEX);
  Serial.print("BL0940_REG_EXT_TEMP:\t");
  Serial.println(mySensor.getExtTemperature(), HEX);


  Serial.println("\nREAD WRITE\n");

  Serial.print("BL0940_REG_I_FAST_RMS_CONTROL:\t");
  Serial.println(mySensor.getFastRMSControl());
  Serial.print("BL0940_REG_I_RMSOS:\t");
  Serial.println(mySensor.getCurrentRMSOffset());
  Serial.print("BL0940_REG_WATTOS:\t");
  Serial.println(mySensor.getPowerOffset());
  Serial.print("BL0940_REG_WA_CREEP:\t");
  Serial.println(mySensor.getPowerCreep());
  
  Serial.print("BL0940_REG_MODE:\t");
  Serial.println(mySensor.getUserMode());
  //  Serial.print("BL0940_REG_SOFT_RESET:\t");
  //  Serial.println(mySensor.readRegister(0x19), HEX);
  Serial.print("BL0940_REG_USR_WRPROT:\t");
  Serial.println(mySensor.getWriteProtect());
  
  Serial.print("BL0940_REG_TPS_CTRL:\t");
  Serial.println(mySensor.getTemperatureControl());
  Serial.print("BL0940_REG_TPS2_GAIN:\t");
  Serial.println(mySensor.getExtTempGain());
  Serial.print("BL0940_REG_TPS2_OFFSET:\t");
  Serial.println(mySensor.getTemperatureControl());
}


void loop()
{
  delay(2000);
}


//  -- END OF FILE --
