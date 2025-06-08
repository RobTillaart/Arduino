//
//    FILE: I2C_PWM_generator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
//    DATE: 2024-11-25
// PURPOSE: Arduino UNO as 6 channel PWM co-processor.
//     URL: https://github.com/RobTillaart/I2C_PWM_generator
//          https://github.com/RobTillaart/PCA9553/issues/9
//

#include <avr/wdt.h>
#include <Wire.h>

//  adjust if needed
#define I2C_BASE_ADDRESS    0x30
#define I2C_ADDRESS_PIN     4
#define I2C_BASE_CLOCK      100000


const int PWMpins[6] = {3, 5, 6, 9, 10, 11};
//  power on start (POS) values can be adapted to your need.
const uint8_t POSValue[6] = {0, 0, 0, 0, 0, 0 };
//  cache current value, prep for getPWM()
uint8_t currentValue[6];

const int LEDPIN = 13;
uint32_t lastBlink = 0;

int reg = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);  //  for debugging

  //  HEARTBEAT PIN
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  //  POWER ON START
  for (int i = 0; i < 6; i++)
  {
    analogWrite(PWMpins[i], POSValue[i]);
    currentValue[i] = POSValue[i];
  }

  //  I2C ADDRESS
  uint8_t I2Caddress = 0x00;
  //  get address bit
  pinMode(I2C_ADDRESS_PIN, INPUT);
  if (digitalRead(I2C_ADDRESS_PIN) == HIGH) I2Caddress += 0x01;

  I2Caddress += I2C_BASE_ADDRESS;  //  0x30..0x31

  //  START AS SLAVE
  Wire.begin(I2Caddress);
  Wire.setClock(I2C_BASE_CLOCK);

  //  WATCHDOG
  wdt_enable(WDTO_2S);

  //  WAIT FOR COMMANDS
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}


void loop()
{
  //  watchdog
  wdt_reset();

  //  heartbeat
  uint32_t now = millis();
  if ((now - lastBlink) >= 1000)
  {
    lastBlink = now;
    digitalWrite(13, !digitalRead(13));
  }
}


/////////////////////////////////////////////////////
//
//  EVENT HANDLERS
//
void receiveEvent(int count)
{
  // catch no data call
  if (count == 0) return;
  int value = 0;
  //  read the "register"
  reg = Wire.read();
  switch (reg)
  {
    //  PWM set one
    case 0 ... 5:
      //  value missing?
      if (count < 2) return;
      value = Wire.read();
      currentValue[reg] = value;
      analogWrite(PWMpins[reg], value);
      break;

    //  PWM set all (experimental)
    case 0x20:
      value = 0;  //  default value
      if (count >= 2) value = Wire.read();
      for (int i = 0; i < 6; i++)
      {
        currentValue[reg] = value;
        analogWrite(PWMpins[reg], value);
      }
      break;

    //  PWM power on start (experimental)
    case 0x21:
      for (int i = 0; i < 6; i++)
      {
        analogWrite(PWMpins[i], POSValue[i]);
        currentValue[i] = POSValue[i];
      }
      break;

    default:  //  nothing
      break;
  }
}


//  experimental
void requestEvent()
{
  //  construct answer for current register.
  switch (reg)
  {
    case 0 ... 5:
      Wire.write(currentValue[reg]);
      break;
    default:
      //  return nothing.
      break;
  }
}


//  -- END OF FILE --
