/**
 *  @file
 *  @Author Septillion (https://github.com/sseptillion)
 *  @date 2016-05-20
 *  @brief Example how to use buttonRead8()
 *  
 *  buttonRead8() works the same as buttonRead() but works on all 
 *  pins simultaneous. You can give a mask as parameter to decide which 
 *  pins are affected (aka, made high for a short periode) during 
 *  a buttonRead8(). 
 *  
 *  The mask can also be set with setButtonMask(mask). Calling buttonRead8() 
 *  after that will be the same as calling buttonRead8(mask).
 *  
 *  ButtonRead8() can also be used for pins that are input only.
 *  
 *  In this example pin 0 of the PCF8574 (address 0x20) is used to blink a 
 *  LED but at the same time it can be used to toggle the onboard LED of 
 *  the Arduino.
 *  
 *  Pin 1 is also toggle but isn't affected by the buttonRead8();
 *  
 *  NOTE: The button will affect the LED on the same pin. The led will light up 
 *  no matter the set output state when you press the button.
 */


#include <PCF8574.h>
#include <Wire.h>


PCF8574 pcf20(0x20);

const byte onboardLed = 13;
const byte PcfButtonLedPin = 0;
const byte PcfLedPin = 1;

unsigned int blinkMillis;
unsigned int buttonMillis;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION: ");
  Serial.println(PCF8574_LIB_VERSION);
  
  Wire.begin();
  pcf20.begin();
  
  pinMode(onboardLed, OUTPUT);
  
  //  As alternative to adding the mask to buttonRead8() every time
  //  you can set it once.
  //  Without setting a mask buttonRead8() will effect ALL pins.
  //  Not a problem when using things like LEDs.
  //  pcf20.setButtonMask(_BV(PcfButtonLedPin));
}


void loop() {
  static bool state;
  unsigned int currentMillis = millis();
  
  //  Limit button read to 20 times a second
  //  Fast enough for most buttons 
  //  but this way you don't have a dimmer output because it's blanked during button read
  //  a read takes 460us t 16Mhz Arduino and normal I2C speed.
  if ((currentMillis - buttonMillis) >= 50) {
    buttonMillis = currentMillis;
    
    //  read all states but only force PcfButtonLedPin HIGH during the 
    //  buttonRead8()
    //  Alternatively the mask could have been set with setButtonMask().
    //  Then the mask can be omitted here. See setup()
    //  byte inputStates = pcf20.readButton8(_BV(PcfButtonLedPin));
    byte inputStates = pcf20.readButton8(1 << PcfButtonLedPin);      //  Keep Arduino-CI happy
    
    //  check the bit of PcfButtonLedPin
    if (state != bitRead(inputStates, PcfButtonLedPin)) {
      if (state) {
        //  toggle the LED
        digitalWrite(onboardLed, !digitalRead(onboardLed));
      }
      state = !state;
    }
  }
  
  //  Lets blink the same output
  if ((currentMillis - blinkMillis) >= 500) {
    //  Update time
    blinkMillis = currentMillis;
    
    pcf20.toggle(PcfButtonLedPin);
    pcf20.toggle(PcfLedPin);
    Serial.println(pcf20.read8(), BIN);
  }
}


//  -- END OF FILE --

