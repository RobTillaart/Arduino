//
//    FILE: ADS_1114_two_continuous.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: demo reading four ADS1114 modules in parallel
//     URL: https://github.com/RobTillaart/ADS1X15


#include "ADS1X15.h"


ADS1114 ADS_1(0x49);
ADS1114 ADS_2(0x48);


//  two interrupt flags
volatile bool RDY_1 = false;
volatile bool RDY_2 = false;

int16_t val_1 = 0;
int16_t val_2 = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  //  SETUP FIRST ADS1114
  ADS_1.begin();
  ADS_1.setGain(0);         //  0 == 6.144 volt, default
  ADS_1.setDataRate(7);     //  0 = slow   4 = medium   7 = fast

  //  SET ALERT RDY PIN
  ADS_1.setComparatorThresholdHigh(0x8000);
  ADS_1.setComparatorThresholdLow(0x0000);
  ADS_1.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady_1, RISING);

  ADS_1.setMode(0);         //  0 == continuous mode
  ADS_1.readADC();          //  0 == default channel,  trigger first read


  //  SETUP SECOND ADS1114
  ADS_2.begin();
  ADS_2.setGain(0);         //  0 == 6.144 volt, default
  ADS_2.setDataRate(7);     //  7 == highest

  //  SET ALERT RDY PIN
  ADS_2.setComparatorThresholdHigh(0x8000);
  ADS_2.setComparatorThresholdLow(0x0000);
  ADS_2.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), adsReady_2, RISING);

  ADS_2.setMode(0);         //  0 == continuous mode
  ADS_2.readADC();          //  0 == default channel,  trigger first read
}


void loop()
{
  if (handleConversion() == true)
  {
    Serial.print('\t');
    Serial.print(val_1);
    Serial.print('\t');
    Serial.print(val_2);
    Serial.println();
  }
}


//  catch interrupt and set flag device 1
void adsReady_1()
{
  RDY_1 = true;
}

//  catch interrupt and set flag device 1
void adsReady_2()
{
  RDY_2 = true;
}


//  handle conversions that are ready
bool handleConversion()
{
  bool rv = false;
  if (RDY_1)
  {
    //  save the last value
    val_1 = ADS_1.getValue();
    ADS_1.readADC(0);
    RDY_1 = false;
    rv = true;
  }
  if (RDY_2)
  {
    //  save the last value
    val_2 = ADS_2.getValue();
    ADS_2.readADC(0);
    RDY_2 = false;
    rv = true;
  }
  return rv;
}


//  -- END OF FILE --

