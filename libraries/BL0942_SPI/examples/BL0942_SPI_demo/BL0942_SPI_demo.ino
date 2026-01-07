//
//    FILE: BL0942_SPI_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/BL0942_SPI


#include "BL0942_SPI.h"


BL0942_SPI mySensor(4, 5, 6, 7);


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


  Serial.println("get all registers");
  Serial.println("READ ONLY\n");

  Serial.print("BL0942_REG_I_WAVE:\t");
  Serial.println(mySensor.getIWave());
  Serial.print("BL0942_REG_V_WAVE:\t");
  Serial.println(mySensor.getVWave());
  Serial.print("BL0942_REG_I_RMS:\t");
  Serial.println(mySensor.getIRMS());
  Serial.print("BL0942_REG_V_RMS:\t");
  Serial.println(mySensor.getVRMS());

  Serial.print("BL0942_REG_I_FAST_RMS:\t");
  Serial.println(mySensor.getIRMSFast());
  Serial.print("BL0942_REG_WATT:\t");
  Serial.println(mySensor.getWatt());
  Serial.print("BL0942_REG_CF_CNT:\t");
  Serial.println(mySensor.getCFPulseCount());
  Serial.print("BL0942_REG_FREQ:\t");
  Serial.println(mySensor.getFrequency());
  Serial.print("BL0942_REG_STATUS:\t");
  Serial.println(mySensor.getStatus());


  Serial.println("\nREAD WRITE\n");

  Serial.print("BL0942_REG_I_RMSOS:\t");
  Serial.println(mySensor.getCurrentRMSOffset());
  Serial.print("BL0942_REG_WA_CREEP:\t");
  Serial.println(mySensor.getPowerCreep());
  Serial.print("BL0942_REG_I_FAST_RMS_TH:\t");
  Serial.println(mySensor.getFastRMSThreshold());
  Serial.print("BL0942_REG_I_FAST_RMS_CYC:\t");
  Serial.println(mySensor.getFastRMSCycles());
  Serial.print("BL0942_REG_FREQ_CYC:\t");
  Serial.println(mySensor.getFrequencyCycles());


  Serial.print("BL0942_REG_OT_FUNX:\t");
  Serial.println(mySensor.getOutputConfigMask());
  Serial.print("BL0942_REG_MODE:\t");
  Serial.println(mySensor.getUserMode());
  Serial.print("BL0942_REG_GAIN_CR:\t");
  Serial.println(mySensor.getCurrentGain());
  //  Serial.print("BL0942_REG_SOFT_RESET:\t");
  //  Serial.println(mySensor.readRegister(0x1C), HEX);
  Serial.print("BL0942_REG_USR_WRPROT:\t");
  Serial.println(mySensor.getCurrentGain());

}


void loop()
{
  delay(2000);
}


//  -- END OF FILE --
