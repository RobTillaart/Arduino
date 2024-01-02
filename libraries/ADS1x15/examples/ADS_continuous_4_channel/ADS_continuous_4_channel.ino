//
//    FILE: ADS_continuous_4_channel.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read multiple analog inputs continuously
//          interrupt driven to catch all conversions.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect multiple potmeters
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


//  choose your sensor
//  ADS1013 ADS(0x48);
//  ADS1014 ADS(0x48);
//  ADS1015 ADS(0x48);
//  ADS1113 ADS(0x48);
//  ADS1114 ADS(0x48);
ADS1115 ADS(0x48);

volatile bool RDY = false;
uint8_t channel = 0;
int16_t val[4] = { 0, 0, 0, 0 };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady, RISING);

  ADS.begin();
  ADS.setGain(0);        //  6.144 volt
  ADS.setDataRate(7);    //  0 = slow   4 = medium   7 = fast

  //  SET ALERT RDY PIN
  ADS.setComparatorThresholdHigh(0x8000);
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorQueConvert(0);

  //  SET INTERRUPT HANDLER TO CATCH CONVERSION READY
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), adsReady, RISING);

  ADS.setMode(0);        //  continuous mode
  ADS.readADC(channel);  //  trigger first read
}


void loop()
{
  handleConversion();

  for (int i = 0; i < 4; i++)
  {
    Serial.print(val[i]);
    Serial.print('\t');
    handleConversion();
  }
  Serial.println();
  delay(100);
}


//  interrupt service routine
//  kept as minimal as possible 
void adsReady()
{
  RDY = true;
}


void handleConversion()
{
  if (RDY)
  {
    //  save the value
    val[channel] = ADS.getValue();
    //  request next channel
    channel++;
    if (channel >= 4) channel = 0;
    ADS.readADC(channel);
    RDY = false;
  }
}


//  -- END OF FILE --

