//
//    FILE: DHT_endless_debug.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DHTNEW

//  make _bits public + disable CRC check to run this program.


//  DHT PIN layout from left to right
//  =================================
//  FRONT : DESCRIPTION
//  pin 1 : VCC
//  pin 2 : DATA
//  pin 3 : Not Connected
//  pin 4 : GND


#include <dhtnew.h>

DHTNEW dht(5);   //  ESP 16    UNO 5    MKR1010 5

uint32_t count = 0;
uint32_t start, stop;

uint32_t errors[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void setup()
{
  while (!Serial);    //  MKR1010 needs this

  Serial.begin(115200);
  Serial.println();
  Serial.println("DHT_endless_debug.ino");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTNEW_LIB_VERSION);
  Serial.println();

  //  MKR1010 needs this
  //  mySensor.setDisableIRQ(false);
}


void loop()
{
  dht.read();

  float HumiVal = dht.getHumidity();
  float TempVal = dht.getTemperature();

  Serial.print(count++);
  Serial.print("\t");
  for (int i = 0; i < 5; i++)
  {
    if (dht._bits[i] < 0x10) Serial.print("0");
    Serial.print(dht._bits[i], HEX);
    Serial.print(" ");
  }
  Serial.print("\t\t");
  Serial.print(TempVal);
  Serial.print("\t");
  Serial.print(HumiVal);
  Serial.println();

  delay(2000);
}


//  -- END OF FILE --
