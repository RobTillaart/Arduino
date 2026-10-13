//
//    FILE: ADG728_multiplex_NTC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo ADG728 I2C multiplexer
//     URL: https://github.com/RobTillaart/ADG728
//
//  multiplex NTC
//  calibrate your hardware in NTC_Celsius()
//  note: all NTC's need same beta constant
//
//                            ADG728                                 uProc
//                          +------------+                        +------------+
//  5 Volt ---+----[NTC]----|o 7      D o|--+---[10K]--- GND      |            |
//            +----[NTC]----|o 6         |  |                     |            |
//            +----[NTC]----|o 5         |  |                     |            |
//            +----[NTC]----|o 4         |  +---------------------|o A0 analog |
//            +----[NTC]----|o 3         |                        |            |
//            +----[NTC]----|o 2         |                        |            |
//            +----[NTC]----|o 1    SDA o|------------------------|o SDA       |
//            +----[NTC]----|o 0    SCL o|------------------------|o SCL       |
//                          +------------+                        +------------+
//


#include "ADG728.h"


ADG728 MP(0x4C);  //  0x4C..0x4F
uint8_t channel = 0;
uint32_t lastTime = 0;


float NTC_Celsius(int raw)
{
  //  adjust calibration values
  const float R10k   = 9870.0f;  //  ohm
  const float VCC    = 5.0f;     //  volts
  const float maxADC = 1023.0f;  //  steps
  const float beta   = 4300.0f;  //  NTC specific constant

  //  calculate voltage across 10K resistor
  float VoltageR10k = raw * VCC / maxADC;
  //  calculate voltage across NTC
  float VoltageNTC = VCC - VoltageR10k;
  //  calculate resistance of NTC
  float RNTC = R10k * VoltageNTC / VoltageR10k;
  //  calculate tempersture
  float Kelvin = 298.15f / (1.0f + (298.15f / beta) * log(RNTC * (1.0f / 10000.0f)));
  float Celsius = Kelvin - 273.15f;
  return Celsius;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADG728_LIB_VERSION: ");
  Serial.println(ADG728_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  initialize multiplexer
  if (MP.begin() == false)
  {
    Serial.println("Multiplexer error");
  }

  channel = 0;
}


void loop()
{
  if ((millis() - lastTime) >= 500)
  {
    lastTime = millis();
    channel++;
    if (channel >= MP.channelCount()) channel = 0;
    MP.selectChannel(channel);

    int raw = analogRead(A0);
    Serial.print(channel);
    Serial.print("\t");
    Serial.print(raw);
    Serial.print("\t");
    Serial.print(NTC_Celsius(raw), 1);
    Serial.print("\n");
  }
}


//  -- END OF FILE --
