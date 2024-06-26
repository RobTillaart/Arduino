//
//    FILE: ADS_high_speed_differential.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read from 2 IC's for high speed differential
//          interrupt driven to catch all conversions.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test setup (not tested yet)
//  - connect 2 ADS1x15 to I2C bus
//  - connect potmeters to all channels
//  - code reads both at the same frequency
//    and calculates differential per pair.
//    as 2 ADC's go in parallel, two ADS1015 should get
//    3000+ differential samples / second.
//


#include "ADS1X15.h"

//  adjust addresses if needed
ADS1115 ADS_1(0x49);
ADS1115 ADS_2(0x48);

volatile bool RDY_1     = false;
volatile bool RDY_2     = false;
uint8_t channel         = 0;
int32_t differential[4] = { 0, 0, 0, 0 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  //  SETUP FIRST ADS1115
  ADS_1.begin();
  ADS_1.setGain(0);        //  6.144 volt
  ADS_1.setDataRate(7);    //  0 = slow   4 = medium   7 = fast

  //  SET ALERT RDY PIN (QueConvert mode)
  //  set the MSB of the Hi_thresh register to 1
  ADS_1.setComparatorThresholdHigh(0x8000);
  //  set the MSB of the Lo_thresh register to 0
  ADS_1.setComparatorThresholdLow(0x0000);
  ADS_1.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady_1, RISING);

  ADS_1.setMode(0);          //  continuous mode
  ADS_1.readADC(channel);    //  trigger first read


  //  SETUP SECOND ADS1115
  ADS_2.begin();
  ADS_2.setGain(0);          //  6.144 volt
  ADS_2.setDataRate(7);

  //  SET ALERT RDY PIN
  //  set the MSB of the Hi_thresh register to 1
  ADS_2.setComparatorThresholdHigh(0x8000);
  // set the MSB of the Lo_thresh register to 0
  ADS_2.setComparatorThresholdLow(0x0000);
  ADS_2.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), adsReady_2, RISING);

  ADS_2.setMode(0);          //  continuous mode
  ADS_2.readADC(channel);    //  trigger first read
}


void loop()
{
  if (handleConversion() == true)
  {
    for (int i = 0; i < 4; i++)
    {
      Serial.print(differential[i]);
      Serial.print("\t");
    }
    Serial.println();
  }
}


//  catch interrupt and set flag
void adsReady_1()
{
  RDY_1 = true;
}

void adsReady_2()
{
  RDY_2 = true;
}


//  handle conversions if both are ready
bool handleConversion()
{
  if (RDY_1 == false) return false;
  if (RDY_2 == false) return false;

  //  read the value of both
  int16_t a = ADS_1.getValue();
  int16_t b = ADS_2.getValue();
  differential[channel] = a - b;
  //  request next channel
  channel++;
  if (channel >= 4) channel = 0;
  ADS_1.readADC(channel);
  ADS_2.readADC(channel);
  RDY_1 = false;
  RDY_2 = false;

  return true;
}


//  -- END OF FILE --

