//    FILE: ACS712_ESP32_external_ADC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to measure mA DC with external ADC
//     URL: https://github.com/RobTillaart/ACS712

//  see also ACS712_20_DC_external_ADC.ino

#include "Arduino.h"
#include "ACS712.h"
#include "ADS1X15.h"


//  I2C config
#define ADS1015_ADDRESS         0x48
#define ADS1015_SCL             22   //  default SCL ESP32
#define ADS1015_SDA             21   //  default SDA ESP32

//  ADS1x15 config
#define SENSOR_ACS712_ADSPIN    1


//  explicit parameters for demo
ADS1015 ads1015(ADS1015_ADDRESS, &Wire);  //  ADS1015 == 12 bit


//  SENSOR_ACS712_ADSPIN sets pin 1 of the ADS1015, 5.0 volt, 4095 = 12 bit, 100 = mVperAmpere
ACS712 ACS(SENSOR_ACS712_ADSPIN, 5.0, 4095, 100);


//  ACS712 ADC WRAPPER FOR ADS1015    Note: uses only one direction.
uint16_t readADS1015(uint8_t pin)
{
  uint16_t ADS_raw = ads1015.readADC(pin);
  Serial.print("ADS_raw: ");
  Serial.println(ADS_raw);
  return ADS_raw;
}


///////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  Serial.println();


  //  ESP32 set wire pins explicitly
  Wire.begin(ADS1015_SDA, ADS1015_SCL);
  Wire.setClock(400000);


  //  initialize ADS1015, if fail => report
  if (ads1015.begin() == false)
  {
    Serial.println("ADS1x15 not found. Check wires and pins. Reboot.");
    while(1);
  }

  //  set up the external ADC for the ACS712
  ACS.setADC(readADS1015, 5.0, 4095);
}


void loop()
{
  int mA = ACS.mA_DC();
  Serial.println(mA);
  delay(1000);
}


//  -- END OF FILE --
