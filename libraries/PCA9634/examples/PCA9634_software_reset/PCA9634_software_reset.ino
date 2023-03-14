//
//    FILE: PCA9634_software_reset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9634 library


#include "Arduino.h"
#include "Wire.h"
#include "PCA9634.h"


PCA9634 ledArray(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.print("PCA9634 LIB version: ");
  Serial.println(PCA9634_LIB_VERSION);
  Serial.println();

  ledArray.begin();

  ledArray.setLedDriverMode(0, PCA9634_LEDON);
  delay(100);
  ledArray.I2C_SoftwareReset(0);
  delay(100);
  Serial.print("I2C_SoftwareReset(0) did ");
  if (ledArray.getLedDriverMode(0) == PCA9634_LEDON)
  {
    Serial.print("not ");
  }
  Serial.println("work. ");
  delay(2000);

  ledArray.begin();
  ledArray.setLedDriverMode(0, PCA9634_LEDON);
  delay(100);
  ledArray. I2C_SoftwareReset(1);
  delay(100);
  Serial.print("I2C_SoftwareReset(1) did ");
  if (ledArray.getLedDriverMode(0) == PCA9634_LEDON)
  {
    Serial.print("not ");
  }
  Serial.println("work. ");
  delay(2000);

  //  Forced led off.
  ledArray.setLedDriverMode(0, PCA9634_LEDOFF);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

