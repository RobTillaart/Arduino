//
//    FILE: ADS_continuous_8_channel.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read multiple analog inputs continuously
//          interrupt driven to catch all conversions.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect multiple potmeters to 2 ADS1115
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x  - connect to AIN0..4.
//
//  for the test it is good to have AIN3 connected to 5V and AIN4 to GND
//  so one can see these as references in the output.
//


#include "ADS1X15.h"


//  adjust addresses if needed
ADS1115 ADS_1(0x49);
ADS1115 ADS_2(0x48);

//  two interrupt flags
volatile bool RDY_1 = false;
volatile bool RDY_2 = false;

uint8_t channel_1 = 0;         //  channel from device 1
uint8_t channel_2 = 0;         //  channel from device 2

//  array to hold the data.
int16_t val[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };


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

  //  SET ALERT RDY PIN
  ADS_1.setComparatorThresholdHigh(0x8000);
  ADS_1.setComparatorThresholdLow(0x0000);
  ADS_1.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady_1, RISING);

  ADS_1.setMode(0);          //  continuous mode
  ADS_1.readADC(channel_1);  //  trigger first read


  //  SETUP SECOND ADS1115
  ADS_2.begin();
  ADS_2.setGain(0);          //  6.144 volt
  ADS_2.setDataRate(7);

  //  SET ALERT RDY PIN
  ADS_2.setComparatorThresholdHigh(0x8000);
  ADS_2.setComparatorThresholdLow(0x0000);
  ADS_2.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), adsReady_2, RISING);

  ADS_2.setMode(0);          //  continuous mode
  ADS_2.readADC(channel_2);  //  trigger first read
}


void loop()
{
  handleConversion();

  for (int i = 0; i < 8; i++)
  {
    Serial.print(val[i]);
    Serial.print('\t');
    handleConversion();
  }
  Serial.println();
  delay(100);
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
    val[channel_1] = ADS_1.getValue();
    //  request next channel
    channel_1++;
    if (channel_1 >= 4) channel_1 = 0;
    ADS_1.readADC(channel_1);
    RDY_1 = false;
    rv = true;
  }
  if (RDY_2)
  {
    //  save the last value
    val[4 + channel_2] = ADS_2.getValue();
    //  request next channel
    channel_2++;
    if (channel_2 >= 4) channel_2 = 0;
    ADS_2.readADC(channel_2);
    RDY_2 = false;
    rv = true;
  }
  return rv;
}


//  -- END OF FILE --

