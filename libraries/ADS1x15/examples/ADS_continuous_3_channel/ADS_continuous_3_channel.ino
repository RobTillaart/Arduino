//
//    FILE: ADS_continuous_3_channel.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read multiple analog inputs continuously
//          interrupt driven to catch all conversions.
//     URL: https://github.com/RobTillaart/ADS1X15
//          https://github.com/RobTillaart/ADS1X15/issues/49
//
//  experimental, not tested extensively

//  test
//  connect multiple potmeters
//
//  RDY ----------------- pin 2 (for IRQ)
//
//  GND ---[   x   ]------ 5V
//             |
//             |
//           ADS(n)
//
//  measure at x  - connect to AIN0..3.
//
//  for the test it is an option to have AIN3 connected to 5V and AIN4 to GND
//  so one can see these as references in the output.
//
//  has an issue with the index of the channels. not not investigated yet.


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

int SPS = 0;
uint32_t lastTime = 0;


void setup()
{
  Serial.begin(230400);       //  <<<<<<<<<  fast!
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();
  Wire.setClock(400000);

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

  ADS.setMode(0);            //  continuous mode
  channel = 0;
  ADS.requestADC(channel);   //  start at 0
}


void loop()
{
  //  if conversion ready
  //  request a new one and print the last one.
  if (RDY)
  {
    SPS++;
    val[channel] = ADS.getValue();
    //  request next channel asap
    channel++;
    if (channel >= 3) channel = 0;
    ADS.requestADC(channel);
    RDY = false;

    //  to see it works
    if (SPS % 200 == 0)
    {
      for (int i = 0; i < 4; i++)
      {
        Serial.print('\t');
        Serial.print(val[i]);
      }
      Serial.println();
    }
  }


  //  print the SPS
  if (millis() - lastTime >= 1000)
  {
    lastTime = millis();
    Serial.print("SPS: ");
    Serial.println(SPS);
    SPS = 0;
  }
}


//  interrupt service routine
//  kept as minimal as possible
void adsReady()
{
  RDY = true;
}


//  -- END OF FILE --

