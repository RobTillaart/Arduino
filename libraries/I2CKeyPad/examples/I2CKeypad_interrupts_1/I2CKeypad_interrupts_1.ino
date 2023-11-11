//
//    FILE: I2CKeypad_interrupts_1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo interrupt checking keyPressed
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  interrupts are supported since version 0.2.1
//  this sketch show usage and some comparison with polling.
//
//   KEYPAD   PCF8574     UNO
//   rows     p0-p3
//   columns  p4-p7
//            IRQ         pin 2
//            SDA         A4
//            SCL         A5
//  4x4 or smaller keypad.


//  notes
//  an interrupt takes less than 10 micros() on an UNO
//  source - https://forum.arduino.cc/t/how-fast-can-i-interrupt/25884/6
//
//  At I2C 100KHz one polling takes 472 micros() on an UNO
//  this is at least 50x longer than handling a single interrupt.
//
//  Given that the interrupt is executed once per press/release and
//  polling at e.g 10Hz (to stay reactive) adds up both in CPU time used
//  and also in occupation of the I2C bus.
//
//  The PCF8574 will generate an interrupt both on press and release.
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
#include "Wire.h"
#include "I2CKeyPad.h"


const uint8_t KEYPAD_ADDRESS = 0x20;
I2CKeyPad keyPad(KEYPAD_ADDRESS);
char keys[] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail (e.g. > 1 keys pressed)

// volatile for IRQ var
volatile bool keyChange = false;


void keyChanged()
{
  keyChange = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);


  //  NOTE: PCF8574 will generate an interrupt on key press and release.
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(1, keyChanged, FALLING);
  keyChange = false;

  Wire.begin();
  Wire.setClock(100000);
  if (keyPad.begin() == false)
  {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1);
  }

  measurePolling();
}


void loop()
{
  if (keyChange)
  {
    uint8_t index = keyPad.getKey();
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


void measurePolling()
{
  //  measure time to check isPressed() by polling.

  //  CLOCK      TIME (us)
  //  ---------------------
  //  100K       472
  //  200K       268
  //  300K       200
  //  400K       168
  //  500K       152
  //  600K       136
  //  700K       124
  //  800K       error
  for (uint32_t clock = 100000; clock <= 800000; clock += 100000)
  {
    Wire.setClock(clock);
    for (int i = 0; i < 1; i++)
    {
      //  reference time for keyPressed check UNO ~
      uint32_t start = micros();
      uint8_t index = keyPad.isPressed();
      uint32_t stop = micros();

      Serial.print(clock);
      Serial.print("\t");
      Serial.print(index);
      Serial.print("\t");
      Serial.print(keys[index]);
      Serial.print("\t");
      Serial.println(stop - start);
      delay(10);
    }
  }
}


//  -- END OF FILE --

