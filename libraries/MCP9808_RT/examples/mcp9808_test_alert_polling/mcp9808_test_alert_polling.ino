//
//    FILE: mcp9808_test_alert_polling.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo alert to PIN5 of Arduino UNO.
//    DATE: 2020-11-16
//    (c) : MIT
//

//
//  MCP9808 breakout board
//  +----------+
//  |0   ALERT |---------------+--[ 4K7 ]---- +5V
//  |       A2 |---- GND       |
//  |       A1 |---- GND       +--< INTERRUPT PIN2 ARDUINO
//  |       A0 |---- GND
//  |      SDA |---- I2C MCU
//  |      SCL |---- I2C MCU
//  |      GND |---- GND MCU
//  |0     VCC |---- +5V
//  +----------+
//

#include "mcp9808.h"

MCP9808 ts(24);

const uint8_t ALERTPIN = 5;     // ADJUST IF NEEDED


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  // SET TEMPERATURE WINDOW FOR COMPERATOR MODE �C
  // small window for 'fast' effect
  ts.setTlower(22);
  ts.setTupper(23);
  // SET AUTO RESET  (p32 datasheet)
  // same value as Tupper to have auto reset in comparator mode.
  // note no hysteresis set
  ts.setTcritical(23);

  Serial.print("LOW:\t");
  Serial.println(ts.getTlower());
  Serial.print("HIGH\t");
  Serial.println(ts.getTupper());
  Serial.print("CRIT\t");
  Serial.println(ts.getTcritical());

  pinMode(ALERTPIN, INPUT_PULLUP);

  // SET ALERT PARAMETERS
  uint16_t cfg = ts.getConfigRegister();
  cfg &= ~0x0001;      // set comparator mode
  // cfg &= ~0x0002;      // set polarity HIGH
  cfg |= 0x0002;       // set polarity LOW
  cfg &= ~0x0004;      // use upper lower and critical
  cfg |= 0x0008;       // enable alert
  ts.setConfigRegister(cfg);
}

void loop()
{
  // will keep on alerting until pin = LOW again  
  // real difference with irq-RISING or CHANGE
  if (digitalRead(ALERTPIN) == HIGH)
  {
    Serial.println("---> ALERT !!!");
  }
  Serial.print(ts.getConfigRegister() & 0x0010);
  Serial.print('\t');
  Serial.print(ts.getStatus());
  Serial.print('\t');
  Serial.print(ts.getTemperature(), 4);
  Serial.print('\n');
  delay(500);
}


// -- END OF FILE --
