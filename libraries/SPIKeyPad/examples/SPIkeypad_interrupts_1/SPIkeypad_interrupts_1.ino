//
//    FILE: SPIKeypad_interrupts_1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo interrupt checking keyPressed
//     URL: https://github.com/RobTillaart/SPIKeyPad
//
//  TO TEST WITH HW - NOT WORKING YET
//
//  interrupts are supported since version x.x.x
//  this sketch show usage and some comparison with polling.
//
//   KEYPAD   MCP23S08    UNO R3
//   rows     p0-p3
//   columns  p4-p7
//            IRQ         pin 2
//            1           SPI CLOCK
//            2           SPI MOSI
//            3           SPI MISO
//  4x4 or smaller keypad.


//  notes
//  an interrupt takes less than 10 micros() on an UNO R3
//  source - https://forum.arduino.cc/t/how-fast-can-i-interrupt/25884/6
//
//  Given that the interrupt is executed once per press/release and
//  polling at e.g 10Hz (to stay reactive) adds up both in CPU time used
//  and also in occupation of the SPI bus.
//
//  The MCP23S08 will generate an interrupt both on press and release.
//  So this code reads the keypad on both signals!
//
//  Note: depending on keypad used some bouncing may occur
//        (saw it only during release)
//  can be solved by tracking the last interrupt in the ISR routine
//  however it is more efficient to reset the flag only after the
//  keypress is handled.
//
//  Note: multiple keypresses are not queued.


////////////////////////////////////////////////////////////////////////
//
//
//

#include "SPIKeyPad.h"

constexpr uint8_t SELECT = 10;
constexpr uint8_t SDOUT = 11;    //  MOSI
constexpr uint8_t SDIN = 12;     //  MISO
constexpr uint8_t SCLOCK = 13;   //  CLK

SPIKeyPad keyPad(SELECT);
//  SPIKeyPad keyPad(SELECT, SDIN, SDOUT, SCLOCK, 0);

char keys[] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail (e.g. > 1 keys pressed)

//  volatile for IRQ variable
volatile bool keyChange = false;


void keyChanged()
{
  keyChange = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SPI_KEYPAD_LIB_VERSION: ");
  Serial.println(SPI_KEYPAD_LIB_VERSION);
  Serial.println();


  //  NOTE: MCP23S08 will generate an interrupt on key press and release.
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, keyChanged, FALLING);
  keyChange = false;

  if (keyPad.usesHWSPI())
  {
    SPI.begin();
  }

  keyPad.begin();

  keyPad.setDebounceThreshold(50);
}


void loop()
{
  if (keyChange)
  {
    uint8_t index = keyPad.getKey();
    //  ignore key bounces
    if (index == SPI_KEYPAD_THRESHOLD)
        return;
    //  only after keyChange is handled it is time reset the flag
    keyChange = false;
    if (index != 16)
    {
      Serial.print("press: ");
      Serial.println(keys[index]);
    }
    else
    {
      Serial.println("release");
    }

  }
}




//  -- END OF FILE --
