//
//    FILE: pulse_sender.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2020-08-08
// PURPOSE: for calibrating the pulse length
//          uses timer1
//
// This sketch sends a test pattern of 1000 ms LOW and 1000 ms HIGH ==> Duty Cycle = 50%
// From measuring the duration of the pulses one can derive the correction factor to adjust the timing.
//
// Pulse sender used an UNO R3 board.
//
// Used two ways to measure
// 1: ESP32 with pulse_measure.ino sketch 
// 2: Saleae Logic analyzer 2.3.4 Alpha 
//
// The correction factor was not identical but close  -2.46% vs -2.78% 
// The Saleae gave a pulse length after correction of 999.99 mSec so pretty good for UNO.
// Currently the correction factor is in steps of 1/4096, to get in the order of 0.1% accuracy


///////////////////////////////////////////////////////////////////////////////////////////////
//
// CODE STARTS HERE
//


#include "PulsePattern.h"

// uint16_t test_pattern[] = { 1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000};
// uint8_t patternSize = 30;

uint16_t test_pattern[] = { 1000, 1000 };  // 0.5 Hz 50% duty cycle
uint8_t patternSize = 2;
uint8_t startLevel = LOW;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // as the prescaler = 1024 the periods of the pattern are a
  // few percent less than a millisecond

  // -0.0278 = - 2.78%       Saleae logic analyzer
  // -0.0246 = - 2.46%       ESP32

  PPGenerator.setFactor(-0.0248); 
  Serial.println(PPGenerator.getFactor(), 6);
  
  // PIN 13 shows a blinking LED.
  PPGenerator.init(13, test_pattern, patternSize, startLevel, PRESCALE_1024);
  PPGenerator.start();
}


void loop()
{
}


// -- END OF FILE --

