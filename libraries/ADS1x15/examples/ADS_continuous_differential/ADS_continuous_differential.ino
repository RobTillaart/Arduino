//
//    FILE: ADS_continuous_differential.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read multiple differential continuously
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 4 potmeters
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x  - connect to AIN0..4.
//


#include "ADS1X15.h"


//  choose your sensor
//  ADS1013 ADS(0x48);
//  ADS1014 ADS(0x48);
//  ADS1015 ADS(0x48);
//  ADS1113 ADS(0x48);
//  ADS1114 ADS(0x48);
ADS1115 ADS(0x48);


//  interrupt flag
volatile bool RDY = false;
//  which pair to use for differential
uint8_t pair = 01;
//  two values to hold differential measurements.
int16_t val_01 = 0;
int16_t val_23 = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady, RISING);

  ADS.begin();
  Serial.print("connected: ");
  Serial.println(ADS.isConnected());
  ADS.setGain(0);        //  6.144 volt
  ADS.setDataRate(0);    //  0 = slow   4 = medium   7 = fast  (7 = fails )
  //  every step is about a factor 2 slower.

  //  SET ALERT RDY PIN (QueConvert mode)
  //  set the MSB of the Hi_thresh register to 1
  ADS.setComparatorThresholdHigh(0x8000);
  //  set the MSB of the Lo_thresh register to 0
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorQueConvert(0);

  //  continuous mode
  ADS.setMode(0);
  //  start with first pair
  pair = 01;
  //  trigger first read
  ADS.requestADC_Differential_0_1();
}


void loop()
{
  static uint32_t last = 0;
  if (handleConversion() == true)
  {
    uint32_t now = millis();
    Serial.print(now - last);
    last = now;
    Serial.print("\tCOMP:\t");
    Serial.print(val_01);
    Serial.print("\t");
    Serial.print(val_23);
    Serial.println();
  }

  //  do other stuff here
  //  delay(10);
}


//  interrupt handler, sets the RDY flag
void adsReady()
{
  RDY = true;
}


//  can be changed to hold other differentials or normal reads too.
bool handleConversion()
{
  if (RDY)
  {
    RDY = false;
    if (pair == 01)
    {
      val_01 = ADS.getValue();
      pair = 23;
      ADS.requestADC_Differential_2_3();
      return false;  //  only one done
    }

    //  last of series to check
    if (pair == 23)
    {
      val_23 = ADS.getValue();
      pair = 01;
      ADS.requestADC_Differential_0_1();
      return true;   //  both are updated
    }
  }
  return false;      //  default not all read
}


//  -- END OF FILE --

