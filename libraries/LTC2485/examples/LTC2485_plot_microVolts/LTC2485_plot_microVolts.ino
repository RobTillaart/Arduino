//
//    FILE: LTC2485_plot_microVolts.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo plotting microvolts
//     URL: https://github.com/RobTillaart/LTC2485


#include "Wire.h"
#include "LTC2485.h"

//  adjust address if needed
//  0x14  CA1 = LOW  CA0 = HIGH
LTC2485 LTC(0x16);

float VREF = 1.8;


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  // Serial.println();
  // Serial.println(__FILE__);
  // Serial.print(F("LTC2485_LIB_VERSION: "));
  // Serial.println(LTC2485_LIB_VERSION);
  // Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  LTC.begin(VREF);
  delay(200);

  while (!LTC.isConnected())
  {
    Serial.println("Could not connect to device");
    delay(2000);
  }

  //  minimize interference from 50-60 Hz sources.
  LTC.configure(LTC2485_SPEED_1X | LTC2485_REJECT_50_60_HZ);


  Serial.println("microVolts");
}


void loop()
{
  static uint32_t lastTime = 0;

  if ((millis() - lastTime) >= 1000)
  {
    lastTime = millis();
    Serial.println(LTC.getMicroVolts(), 3);
  }

}


//  -- END OF FILE --
