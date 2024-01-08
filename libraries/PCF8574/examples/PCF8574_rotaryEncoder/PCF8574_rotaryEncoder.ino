//
//    FILE: PCF8574_rotaryEncoder.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2021-05-08
// PURPOSE: demo PCF8574 as rotary encoder reader.
//     URL: https://github.com/RobTillaart/PCF8574
//
//
//  RotaryEncoder    PCF8574      UNO
//  --------------------------------------
//    pin A           pin 0       (add pull ups, also for not connected lines)
//    pin B           pin 1
//    ....            ....        (up to 4 RE)
//
//                    SDA         A4
//                    SCL         A5
//                    INT         2
//
//  note: a dedicated rotary decoder class is created 
//        - https://github.com/RobTillaart/rotaryDecoder -


#include "PCF8574.h"

PCF8574 decoder(0x20);


//  hold position of 4 RE + last position
uint8_t lastpos[4] = {0, 0, 0, 0};
int32_t encoder[4] = {0, 0, 0, 0};
volatile bool flag = false;


////////////////////////////////////////////////
//
//  IRQ routine
//
void moved()
{
  flag = true;
}


////////////////////////////////////////////////
//
//  rotary routines
//
void initRotaryDecoder()
{
  uint8_t val = decoder.read8();
  for (uint8_t i = 0; i < 4; i++)
  {
    lastpos[i] = val & 0x03;
    val >>= 2;
  }
}


//  assumes 4 rotary encoders connected to one PCF8574
void updateRotaryDecoder()
{
  uint8_t val = decoder.read8();

  //  check which of 4 has changed
  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t currentpos = (val & 0x03);
    if (lastpos[i] != currentpos)     //  moved!
    {
      uint8_t change = (lastpos[i] << 2) | currentpos;
      switch (change)
      {
        case 0b0001:  //  fall through..
        case 0b0111:
        case 0b1110:
        case 0b1000:
          encoder[i]++;
          break;
        case 0b0010:
        case 0b0100:
        case 0b1101:
        case 0b1011:
          encoder[i]--;
          break;
      }
      lastpos[i] = currentpos;
    }
    val >>= 2;
  }
}


////////////////////////////////////////////////
//
//  main code
//
void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, moved, FALLING);
  flag = false;

  Wire.begin();

  if (decoder.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to PCF8574.");
    Serial.println("Please reboot / adjust address.\n");
    while (1);
  }
  Wire.setClock(600000);
  
  initRotaryDecoder();

  uint32_t start = micros();
  for (int i = 0; i < 10; i++)
  {
    updateRotaryDecoder();
  }
  uint32_t stop = micros();
  Serial.println((stop - start) * 0.1);
}


void loop()
{
  if (flag)
  {
    updateRotaryDecoder();
    flag = false;
    for (int i = 0; i < 4; i++)
    {
      Serial.print("\t");
      Serial.print(encoder[i]);
    }
    Serial.println();
  }
}


//  -- END OF FILE --

