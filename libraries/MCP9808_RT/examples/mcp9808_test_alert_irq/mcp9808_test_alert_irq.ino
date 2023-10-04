//
//    FILE: mcp9808_test_alert_irq.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo alert to interrupt 0 = PIN2 of Arduino UNO.
//    DATE: 2020-11-16
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

const uint8_t ALERTPIN = 2;     // ADJUST IF NEEDED
volatile bool flag = false;


// interrupt routine
void detectAlert()
{
  flag = true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP9808_LIB_VERSION: ");
  Serial.println(MCP9808_LIB_VERSION);

  Wire.begin();

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
  attachInterrupt(digitalPinToInterrupt(ALERTPIN), detectAlert, RISING);  // CHANGE


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
  if (flag)
  {
    flag = false;
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
