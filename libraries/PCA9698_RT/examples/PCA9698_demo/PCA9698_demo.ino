//
//    FILE: PCA9698_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo how to use
//     URL: https://github.com/RobTillaart/PCA9698_RT
//
//  looping high / low.


#include "PCA9698.h"

PCA9698 PCA(0x20);  //  adjust if needed


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9698_LIB_VERSION:\t");
  Serial.println(PCA9698_LIB_VERSION);

  Wire.begin();

  PCA.begin();

  uint8_t buf[5];
  Serial.print("DEVICE_ID:");
  Serial.println(PCA.getDeviceID());

  Serial.print("POLARITY:");
  PCA.getPolarity40(buf);
  for (int i = 0; i < 5; i++)
  {
    Serial.print("\t");
    Serial.print(buf[i], HEX);
  }
  Serial.println();

  Serial.print("PINMODE:");
  PCA.getPinMode40(buf);
  for (int i = 0; i < 5; i++)
  {
    Serial.print("\t");
    Serial.print(buf[i], HEX);
  }
  Serial.println();

  Serial.print("INTERRUPT");
  PCA.getInterrupt40(buf);
  for (int i = 0; i < 5; i++)
  {
    Serial.print("\t");
    Serial.print(buf[i], HEX);
  }
  Serial.println();

}


void loop()
{
  for (int pin = 0; pin < 39; pin++)
  {
    PCA.write1(pin, HIGH);
    delay(200);
    PCA.write1(pin, LOW);
    delay(200);
  }
  delay(1000);

  for (int pin = 39; pin >= 0; pin--)
  {
    PCA.toggle1(pin);
    delay(100);
    PCA.toggle1(pin);
    delay(100);
  }
  delay(1000);

  for (int bank = 0; bank < 5; bank++)
  {
    PCA.write8(bank, 0xFF);
    delay(500);
    PCA.write8(bank, 0x00);
    delay(500);
  }
  delay(1000);

  for (int bank = 0; bank < 5; bank++)
  {
    PCA.toggle8(bank, 0xFF);
    delay(250);
    PCA.toggle8(bank, 0x00);
    delay(250);
  }
  delay(1000);

  uint8_t buf[5] = { 0x0F, 0xF0, 0x3C, 0x0F, 0xF0 };
  PCA.write40(buf);
  delay(500);
  for (int i = 0; i < 5; i++) buf[i] = 0;
  PCA.write40(buf);
  delay(500);
  delay(1000);
}


//  -- END OF FILE --
