//
//    FILE: MultiSpeedI2CScanner.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.17
// PURPOSE: I2C scanner at different speeds
//    DATE: 2013-11-05
//     URL: https://github.com/RobTillaart/MultiSpeedI2CScanner
//     URL: http://forum.arduino.cc/index.php?topic=197360
//


#include <Arduino.h>
#include <Wire.h>

//  FOR INTERNAL I2C BUS NANO 33 BLE
//  #define WIRE_IMPLEMENT_WIRE1 1
//  extern TwoWire Wire1;

TwoWire *wire;

const char version[] = "0.1.16";


//  INTERFACE COUNT (TESTED TEENSY 3.5 AND ARDUINO DUE ONLY)
int wirePortCount = 1;
int selectedWirePort = 0;


//  scans devices from 50 to 800 KHz I2C speeds.
//  speed lower than 50 and above 400 can cause problems
long speed[10] = { 100, 200, 300, 400 };
int speeds;

int addressStart = 8;
int addressEnd = 119;


//  DELAY BETWEEN TESTS
//  for delay between tests of found devices.
#ifndef RESTORE_LATENCY
#define RESTORE_LATENCY       5
#endif

bool delayFlag = false;


//  MINIMIZE OUTPUT
bool printAll = true;
bool header = true;
bool disableIRQ = false;


//  STATE MACHINE
enum states {
  STOP, ONCE, CONT, HELP
};
states state = STOP;


//  TIMING
uint32_t startScan;
uint32_t stopScan;


///////////////////////////////////////////////////////////////////////////
//
// MAIN CODE
//
void setup()
{
  Serial.begin(115200);
  while (!Serial);

#if defined (ESP8266) || defined(ESP32)
  uint8_t sda = 14;  //  21
  uint8_t scl = 15;  //  22
  Wire.begin(sda, scl, 100000);  //  ESP32 - change config pins if needed.
#else
  Wire.begin();
#endif

#if defined WIRE_IMPLEMENT_WIRE1 || WIRE_INTERFACES_COUNT > 1
  Wire1.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE2 || WIRE_INTERFACES_COUNT > 2
  Wire2.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE3 || WIRE_INTERFACES_COUNT > 3
  Wire3.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE4 || WIRE_INTERFACES_COUNT > 4
  Wire4.begin();
  wirePortCount++;
#endif
#if defined WIRE_IMPLEMENT_WIRE5 || WIRE_INTERFACES_COUNT > 5
  Wire5.begin();
  wirePortCount++;
#endif

  wire = &Wire;

  Serial.println();
  reset();
}


void loop()
{
  yield();
  char command = getCommand();
  switch (command)
  {
    case '@':
      selectedWirePort = (selectedWirePort + 1) % wirePortCount;
      Serial.print(F("<I2C PORT=Wire"));
      Serial.print(selectedWirePort);
      Serial.println(F(">"));
      switch (selectedWirePort)
      {
        case 0:
          wire = &Wire;
          break;
#if defined WIRE_IMPLEMENT_WIRE1 || WIRE_INTERFACES_COUNT > 1
        case 1:
          wire = &Wire1;
          break;
#endif
#if defined WIRE_IMPLEMENT_WIRE2 || WIRE_INTERFACES_COUNT > 2
        case 2:
          wire = &Wire2;
          break;
#endif
#if defined WIRE_IMPLEMENT_WIRE3 || WIRE_INTERFACES_COUNT > 3
        case 3:
          wire = &Wire3;
          break;
#endif
#if defined WIRE_IMPLEMENT_WIRE4 || WIRE_INTERFACES_COUNT > 4
        case 4:
          wire = &Wire4;
          break;
#endif
#if defined WIRE_IMPLEMENT_WIRE5 || WIRE_INTERFACES_COUNT > 5
        case 5:
          wire = &Wire5;
          break;
#endif
      }
      break;

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
    case 'i':
      disableIRQ = !disableIRQ;
      Serial.print(F("<irq="));
      Serial.println(disableIRQ ? F("diabled>") : F("enabled>"));
      break;

    case '0':
    case '1':
    case '2':
    case '4':
    case '8':
    case '9':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
      setSpeed(command);
      break;

    case 'r':
      reset();
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

//////////////////////////////////////////////////////////////////////

void reset()
{
  setSpeed('9');
  selectedWirePort = 0;
  addressStart     = 8;
  addressEnd       = 119;
  
  delayFlag  = false;
  printAll   = true;
  header     = true;
  disableIRQ = false;

  state = STOP;

  displayHelp();
}


void setAddress()
{
  if (addressStart == 0)
  {
    addressStart = 8;
    addressEnd = 119;
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
    case '9':  // limited to 400 KHz
      speeds = 8;
      for (int i = 1; i <= speeds; i++) speed[i - 1] = i * 50;
      break;
    case '0':  // limited to 800 KHz
      speeds = 8;
      for (int i = 1; i <= speeds; i++) speed[i - 1] = i * 100;
      break;

    // new in 0.1.10 - experimental
    case 'M':
      speed[0] = 1000;
      speeds = 1;
      break;
    case 'N':
      speed[0] = 3400;
      speeds = 1;
      break;
    case 'O':
      speed[0] = 5000;
      speeds = 1;
      break;
    case 'P':
      speed[0] = 100;
      speed[1] = 400;
      speed[2] = 1000;
      speed[3] = 3400;
      speed[4] = 5000;
      speeds = 5;
      break;
  }
  Serial.print("<speeds =");
  for (int i = 0; i < speeds; i++)
  {
    Serial.print(' ');
    Serial.print(speed[i]);
  }
  Serial.println(" >");
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
  Serial.print(F("\nArduino MultiSpeed I2C Scanner - "));
  Serial.println(version);
  Serial.println();
  Serial.print(F("I2C ports: "));
  Serial.print(wirePortCount);
  Serial.print(F("  Current: Wire"));
  Serial.println(selectedWirePort);
  Serial.println(F("\t@ = toggle Wire - Wire1 .. Wire5 [e.g. TEENSY or Arduino Due]"));

  Serial.println(F("Scan mode:"));
  Serial.println(F("\ts = single scan"));
  Serial.println(F("\tc = continuous scan - 1 second delay"));
  Serial.println(F("\tq = quit continuous scan"));
  Serial.println(F("\td = toggle latency delay between successful tests. 0 - 5 ms"));
  Serial.println(F("\ti = toggle enable/disable interrupts"));

  Serial.println(F("Output:"));
  Serial.println(F("\tp = toggle printAll - printFound."));
  Serial.println(F("\th = toggle header - noHeader."));
  Serial.println(F("\ta = toggle address range, 0..127 - 8..119 (default)"));

  Serial.println(F("Speeds:"));
  Serial.println(F("\t0 = 100..800 KHz - step 100  (warning - can block!!)"));
  Serial.println(F("\t1 = 100 KHz"));
  Serial.println(F("\t2 = 200 KHz"));
  Serial.println(F("\t4 = 400 KHz"));
  Serial.println(F("\t9 = 50..400 KHz - step 50     < DEFAULT >"));
  Serial.println();
  Serial.println(F("\t!! HIGH SPEEDS - WARNING - can block - not applicable for UNO"));
  Serial.println(F("\t8 =  800 KHz"));
  Serial.println(F("\tM = 1000 KHz"));
  Serial.println(F("\tN = 3400 KHz"));
  Serial.println(F("\tO = 5000 KHz"));
  Serial.println(F("\tP = 100 400 1000 3400 5000 KHz (standards)"));
  Serial.println(F("\n\tr = reset to startup defaults."));
  Serial.println(F("\t? = help - this page"));
  Serial.println();
}


void I2Cscan()
{
  startScan = millis();
  uint8_t count = 0;

  if (disableIRQ)
  {
    noInterrupts();
  }

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
    delay(100);
  }

  for (uint8_t address = addressStart; address <= addressEnd; address++)
  {
    bool printLine = printAll;
    bool found[speeds];
    bool fnd = false;

    for (uint8_t s = 0; s < speeds ; s++)
    {
      yield();    // keep ESP happy

#if ARDUINO < 158 && defined (TWBR)
      uint16_t PREV_TWBR = TWBR;
      TWBR = (F_CPU / (speed[s] * 1000) - 16) / 2;
      if (TWBR < 2)
      {
        Serial.println("ERROR: not supported speed");
        TWBR = PREV_TWBR;
        return;
      }
#else
      wire->setClock(speed[s] * 1000UL);
#endif
      wire->beginTransmission (address);
      found[s] = (wire->endTransmission () == 0);
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

/*
  //  FOOTER
  if (header)
  {
    for (uint8_t s = 0; s < speeds + 5; s++)
    {
      Serial.print(F("--------"));
    }
    Serial.println();

    Serial.print(F("TIME\tDEC\tHEX\t"));
    for (uint8_t s = 0; s < speeds; s++)
    {
      Serial.print(F("\t"));
      Serial.print(speed[s]);
    }
    Serial.println(F("\t[KHz]"));
  }
*/

  stopScan = millis();
  if (header)
  {
    Serial.println();
    Serial.print(count);
    Serial.print(F(" devices found in "));
    Serial.print(stopScan - startScan);
    Serial.println(F(" milliseconds."));
  }

  interrupts();
}


// -- END OF FILE --

