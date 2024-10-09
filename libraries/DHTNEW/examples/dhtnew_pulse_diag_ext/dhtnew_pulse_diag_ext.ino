//
//    FILE: dhtnew_pulse_diag_ext.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DHTNEW library pulse measurement tool - diagnostics
//     URL: https://github.com/RobTillaart/DHTNew

//  DHT PIN layout from left to right
//  =================================
//  FRONT : DESCRIPTION
//  pin 1 : VCC
//  pin 2 : DATA
//  pin 3 : Not Connected
//  pin 4 : GND


#include "Arduino.h"

#define DHTLIB_DHT11_WAKEUP        18
#define DHTLIB_DHT_WAKEUP          1

#define BIT_THRESHOLD              50


uint8_t   _dataPin = 5;
uint8_t   _wakeupDelay = DHTLIB_DHT_WAKEUP;

uint16_t  count = 0;
uint32_t  times[100], t = 0;
uint8_t   idx = 0;
uint32_t  value;

void setup()
{
  while (!Serial);       //  MKR1010 needs this

  Serial.begin(115200);
  Serial.println("dhtnew_pulse_diag_ext.ino");
  Serial.println();

  //  default should be HIGH
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, HIGH);
}


void loop()
{
  measure();
  dump();
  delay(5000);
}


void dump()
{
  int i = 1;
  Serial.println();
  Serial.print("RUN:\t"); Serial.println(count);
  Serial.print("IDX:\t"); Serial.println(idx);

  Serial.println("WAKEUP");
  for (int n = 0; n < 6; n++)
  {
    Serial.print("\t");
    Serial.print(times[i++]);
  }
  Serial.println();

  Serial.println("HUM");
  uint16_t raw_humidity = 0;
  for (int n = 0; n < 32; n++)
  {
    Serial.print("\t");
    if (n % 2)
    {
      raw_humidity <<= 1;
      if (times[i] > BIT_THRESHOLD) raw_humidity |= 1;
    }
    Serial.print(times[i++]);
    if ((n & 15) == 15) Serial.println();
  }
  Serial.print("RAW H:\t0b");
  Serial.print(raw_humidity, BIN);
  Serial.print(" = 0x");
  Serial.print(raw_humidity, HEX);
  Serial.print(" = ");
  Serial.print(raw_humidity, DEC);
  Serial.print(" = ");
  Serial.print(raw_humidity * 0.1, 1);
  Serial.print("%");
  Serial.println();
  Serial.println();

  Serial.println("TEMP");
  uint16_t raw_temperature = 0;
  for (int n = 0; n < 32; n++)
  {
    Serial.print("\t");
    if (n % 2)
    {
      raw_temperature <<= 1;
      if (times[i] > BIT_THRESHOLD) raw_temperature |= 1;
    }
    Serial.print(times[i++]);
    if ((n & 15) == 15) Serial.println();
  }
  Serial.print("RAW T:\t0b");
  Serial.print(raw_temperature, BIN);
  Serial.print(" = 0x");
  Serial.print(raw_temperature, HEX);
  Serial.print(" = ");
  Serial.print(raw_temperature, DEC);
  Serial.print(" = ");
  Serial.print(raw_temperature * 0.1, 1);
  Serial.print("C");
  Serial.println();
  Serial.println();

  Serial.println("CRC");
  uint8_t raw_CRC = 0;
  for (int n = 0; n < 16; n++)
  {
    Serial.print("\t");
    if (n % 2)
    {
      raw_CRC <<= 1;
      if (times[i] > BIT_THRESHOLD) raw_CRC |= 1;
    }
    Serial.print(times[i++]);
    if ((n & 7) == 7) Serial.println();
  }
  Serial.print("CRC:\t0b");
  Serial.print(raw_CRC, BIN);
  Serial.print(" = ");
  Serial.print(raw_CRC, DEC);
  Serial.print(" <=> ");
  uint8_t calc_crc = 0;
  calc_crc += (raw_humidity >> 8) + (raw_humidity & 0xFF);
  calc_crc += (raw_temperature >> 8) + (raw_temperature & 0xFF);
  Serial.print(calc_crc, DEC);
  Serial.println();
  Serial.println();
  Serial.println();

  Serial.println("BYE");
  for (int n = 0; n < 2; n++)
  {
    Serial.print("\t");
    Serial.print(times[i++]);
  }
  Serial.println();
  Serial.println();
}


void measure()
{
  Serial.print(F("\n===================================\n"));

  count++;
  //  yield(); // handle pending interrupts

  //  reset measurements table
  idx = 0;
  t = micros();
  for (int i = 0; i < 100; i++) times[i] = 0;

  times[idx++] = micros();
  //  REQUEST SAMPLE - SEND WAKEUP TO SENSOR
  pinMode(_dataPin, OUTPUT);
  digitalWrite(_dataPin, LOW);
  //  add 10% extra for timing inaccuracies in sensor.
  delayMicroseconds(_wakeupDelay * 1100UL);

  Serial.print("awake ");

  times[idx++] = micros();
  //  HOST GIVES CONTROL TO SENSOR
  pinMode(_dataPin, INPUT_PULLUP);

  //  DISABLE INTERRUPTS when clock in the bits
  //  noInterrupts();      // gives problems on AVR


  times[idx++] = micros();
  //  SENSOR PULLS LOW after 20-40 us  => if stays HIGH ==> device not ready
  while (digitalRead(_dataPin) == HIGH);

  Serial.print("2 ");

  times[idx++] = micros();
  //  SENSOR STAYS LOW for ~80 us => or TIMEOUT
  while (digitalRead(_dataPin) == LOW);

  Serial.print("3 ");


  times[idx++] = micros();
  //  SENSOR STAYS HIGH for ~80 us => or TIMEOUT
  while (digitalRead(_dataPin) == HIGH);
  times[idx++] = micros();

  Serial.print("4 ");


  //  SENSOR HAS NOW SEND ACKNOWLEDGE ON WAKEUP
  //  NOW IT SENDS THE BITS

  //  READ THE OUTPUT - 40 BITS => 5 BYTES
  uint32_t start = micros();
  uint8_t i = 40;
  for (i = 40; i != 0; i--)
  {
    times[idx++] = micros();
    //  EACH BIT START WITH ~50 us LOW
    while (digitalRead(_dataPin) == LOW)
    {
      if (micros() - start > 10000)
      {
        Serial.print(" <");
        Serial.println(i);
        Serial.println("> ");
        break;
      }
    }

    times[idx++] = micros();
    //  DURATION OF HIGH DETERMINES 0 or 1
    //  26-28 us ==> 0
    //     70 us ==> 1
    while (digitalRead(_dataPin) == HIGH)
    {
      if (micros() - start > 10000)
      {
        Serial.println(i);
        break;
      }
    }
  }

  Serial.print("5 ");

  times[idx++] = micros();
  //  After 40 bits the sensor pulls the line LOW for 50 us
  //  TODO: should we wait?
  while (digitalRead(_dataPin) == LOW);

  Serial.print("6 ");

  times[idx++] = micros();
  times[idx++] = micros();

  for (int n = 100; n > 0; n--)
  {
    times[n] -= times[n - 1];
  }

  Serial.println("7 ");
}


//  -- END OF FILE --
