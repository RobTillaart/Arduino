//
//    FILE: MultiSpeedI2CScanner.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.06
// PURPOSE: I2C scanner @different speeds
//    DATE: 2013-11-05
//     URL: http://forum.arduino.cc/index.php?topic=197360
//
// Released to the public domain
//

#include <Wire.h>
#include <Arduino.h>

const char version[] = "0.1.06";

// scans devices from 50 to 800KHz I2C speeds.
// lower than 50 is not possible
// DS3231 RTC works on 800 KHz. TWBR = 2; (?)
const long allSpeed[] = {
  50, 100, 200, 250, 400, 500, 800
};
long speed[sizeof(allSpeed) / sizeof(allSpeed[0])];
int speeds;

int addressStart = 0;
int addressEnd = 127;

// DELAY BETWEEN TESTS
#define RESTORE_LATENCY  5    // for delay between tests of found devices.
bool delayFlag = false;

// MINIMIZE OUTPUT
bool printAll = true;
bool header = true;

// STATE MACHINE
enum states {
  STOP, ONCE, CONT, HELP
};
states state = STOP;

uint32_t startScan;
uint32_t stopScan;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  setSpeed('0');
  displayHelp();
}


void loop()
{
  char command = getCommand();
  switch (command)
  {
    case 's':
      state = ONCE;
      break;
    case 'c':
      state = CONT;
      break;
    case 'd':
      delayFlag = !delayFlag;
      Serial.print(F("<delay="));
      Serial.println(delayFlag ? F("5>") : F("0>"));
      break;

    case 'e':
      // eeprom test TODO
      break;

    case 'h':
      header = !header;
      Serial.print(F("<header="));
      Serial.println(header ? F("yes>") : F("no>"));
      break;
    case 'p':
      printAll = !printAll;
      Serial.print(F("<print="));
      Serial.println(printAll ? F("all>") : F("found>"));
      break;

    case '0':
    case '1':
    case '2':
    case '4':
    case '8':
      setSpeed(command);
      break;

    case 'a':
      setAddress();
      break;

    case 'q':
    case '?':
      state = HELP;
      break;
    default:
      break;
  }

  switch (state)
  {
    case ONCE:
      I2Cscan();
      state = HELP;
      break;
    case CONT:
      I2Cscan();
      delay(1000);
      break;
    case HELP:
      displayHelp();
      state = STOP;
      break;
    case STOP:
      break;
    default: // ignore all non commands
      break;
  }
}


void setAddress()
{
  if (addressStart == 0)
  {
    addressStart = 8;
    addressEnd = 120;
  }
  else
  {
    addressStart = 0;
    addressEnd = 127;
  }
  Serial.print(F("<address Range = "));
  Serial.print(addressStart);
  Serial.print(F(".."));
  Serial.print(addressEnd);
  Serial.println(F(">"));

}

void setSpeed(char sp)
{
  switch (sp)
  {
    case '1':
      speed[0] = 100;
      speeds = 1;
      break;
    case '2':
      speed[0] = 200;
      speeds = 1;
      break;
    case '4':
      speed[0] = 400;
      speeds = 1;
      break;
    case '8':
      speed[0] = 800;
      speeds = 1;
      break;
    case '0':  // reset
      speeds = sizeof(allSpeed) / sizeof(allSpeed[0]);
      for (int i = 0; i < speeds; i++)
      {
        speed[i] = allSpeed[i];
      }
      break;
  }
}

char getCommand()
{
  char c = '\0';
  if (Serial.available())
  {
    c = Serial.read();
  }
  return c;
}

void displayHelp()
{
  Serial.print(F("\nArduino I2C Scanner - "));
  Serial.println(version);
  Serial.println();
  Serial.println(F("Scanmode:"));
  Serial.println(F("\ts = single scan"));
  Serial.println(F("\tc = continuous scan - 1 second delay"));
  Serial.println(F("\tq = quit continuous scan"));
  Serial.println(F("\td = toggle latency delay between successful tests. 0 - 5 ms"));
  Serial.println(F("Output:"));
  Serial.println(F("\tp = toggle printAll - printFound."));
  Serial.println(F("\th = toggle header - noHeader."));
  Serial.println(F("\ta = toggle address range, 0..127 - 8..120"));
  Serial.println(F("Speeds:"));
  Serial.println(F("\t0 = 50 - 800 Khz"));
  Serial.println(F("\t1 = 100 KHz only"));
  Serial.println(F("\t2 = 200 KHz only"));
  Serial.println(F("\t4 = 400 KHz only"));
  Serial.println(F("\t8 = 800 KHz only"));
  Serial.println(F("\n\t? = help - this page"));
  Serial.println();
}


void I2Cscan()
{
  startScan = millis();
  uint8_t count = 0;

  if (header)
  {
    Serial.print(F("TIME\tDEC\tHEX\t"));
    for (uint8_t s = 0; s < speeds; s++)
    {
      Serial.print(F("\t"));
      Serial.print(speed[s]);
    }
    Serial.println(F("\t[KHz]"));
    for (uint8_t s = 0; s < speeds + 5; s++)
    {
      Serial.print(F("--------"));
    }
    Serial.println();
  }

  // TEST
  // 0.1.04: tests only address range 8..120
  // --------------------------------------------
  // Address	R/W Bit	Description
  // 0000 000   0	General call address
  // 0000 000   1	START byte
  // 0000 001   X	CBUS address
  // 0000 010   X	reserved - different bus format
  // 0000 011   X	reserved - future purposes
  // 0000 1XX   X	High Speed master code
  // 1111 1XX   X	reserved - future purposes
  // 1111 0XX   X	10-bit slave addressing
  for (uint8_t address = addressStart; address <= addressEnd; address++)
  {
    bool printLine = printAll;
    bool found[speeds];
    bool fnd = false;

    for (uint8_t s = 0; s < speeds ; s++)
    {
#if ARDUINO >= 158
      Wire.setClock(speed[s] * 1000);
#else
      TWBR = (F_CPU / (speed[s] * 1000) - 16) / 2;
#endif
      Wire.beginTransmission (address);
      found[s] = (Wire.endTransmission () == 0);
      fnd |= found[s];
      // give device 5 millis
      if (fnd && delayFlag) delay(RESTORE_LATENCY);
    }

    if (fnd) count++;
    printLine |= fnd;

    if (printLine)
    {
      Serial.print(millis());
      Serial.print(F("\t"));
      Serial.print(address, DEC);
      Serial.print(F("\t0x"));
      if (address < 0x10) Serial.print(0, HEX);
      Serial.print(address, HEX);
      Serial.print(F("\t"));

      for (uint8_t s = 0; s < speeds ; s++)
      {
        Serial.print(F("\t"));
        Serial.print(found[s] ? F("V") : F("."));
      }
      Serial.println();
    }
  }

  stopScan = millis();
  if (header)
  {
    Serial.println();
    Serial.print(count);
    Serial.print(F(" devices found in "));
    Serial.print(stopScan - startScan);
    Serial.println(F(" milliseconds."));
  }
}


