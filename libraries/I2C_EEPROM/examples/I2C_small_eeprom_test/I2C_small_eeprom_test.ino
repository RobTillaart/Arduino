//
//    FILE: I2C_small_eeprom_test.ino
//  AUTHOR: Tyler Freeman
// VERSION: 0.1.1
// PURPOSE: show/test I2C_EEPROM library with small EEPROMS
//     URL: https://github.com/RobTillaart/I2C_EEPROM
// HISTORY
// 0.1.0    2014-05-xx initial version
// 0.1.1    2020-07-14 fix #1 compile for ESP; fix author


#include <Wire.h>
#include <I2C_eeprom.h>


// it's only 1Kbit!!!
#define EE24LC01MAXBYTES 1024/8

// the address of your EEPROM
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define SHORT_BUFFER_LEN 4

// this tests multi-page writes
#define LONG_BUFFER_LEN 64
// make sure it's aligned on a page boundary
#define LONG_TEST_PAGE_ADDR (max(16, TEST_PAGE_ADDR + SHORT_BUFFER_LEN))


// this tests multi-page writes that don't start on a boundary
#define UNALIGNED_BUFFER_LEN 35
#define UNALIGNED_TEST_PAGE_ADDR (LONG_TEST_PAGE_ADDR + LONG_BUFFER_LEN + 5)

// #define SERIAL_DEBUG SerialUSB
#define SERIAL_DEBUG Serial

I2C_eeprom eeprom(DEVICEADDRESS, EE24LC01MAXBYTES);


void readAndWriteVar() {
    SERIAL_DEBUG.println("----------------------------------------------");
    SERIAL_DEBUG.print("SINGLE BYTE: writing and retreiving EEPROM on I2C at address ");
    SERIAL_DEBUG.println(DEVICEADDRESS);
    SERIAL_DEBUG.println("----------------------------------------------");

    byte curval = eeprom.readByte(TEST_ADDR);

    SERIAL_DEBUG.print("last value: ");
    SERIAL_DEBUG.println(curval);


    curval += 1;
    eeprom.writeByte(TEST_ADDR, curval);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println(curval);
    delay(10);

    curval = eeprom.readByte(TEST_ADDR);
    SERIAL_DEBUG.print("new value: ");
    SERIAL_DEBUG.println(curval);
}


void readAndWritePage(unsigned int pageAddress, int bufferLen) {
    // always make the maximum size, just don't use all of it.
    byte testBuffer[LONG_BUFFER_LEN + 1];

    // null-terminate for printing!
    testBuffer[bufferLen] = '\0';

    eeprom.readBlock(pageAddress, testBuffer, bufferLen);


    SERIAL_DEBUG.print("last value:  ");
    SERIAL_DEBUG.println((char*)testBuffer);

    for (int i = 0; i < bufferLen; i++) {
      // use max to init to all AAAA's on first run.
      testBuffer[i] = 'A';
      char c = (testBuffer[i] + ((i % 4) + 1) % 'z');
      if (testBuffer[i] < c) testBuffer[i] = c;
    }

    eeprom.writeBlock(pageAddress, testBuffer, bufferLen);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println((char*)testBuffer);
    delay(10);

    eeprom.readBlock(pageAddress, testBuffer, bufferLen);
    SERIAL_DEBUG.print("new value:   ");
    SERIAL_DEBUG.println((char*)testBuffer);
}


void setup()
{
  SERIAL_DEBUG.begin(57600);
  while (!SERIAL_DEBUG); // wait for SERIAL_DEBUG port to connect. Needed for Leonardo only

  SERIAL_DEBUG.println("IT IS BEGINNING");
  SERIAL_DEBUG.println("WAIT FOR IT");

  Wire.begin();

  eeprom.begin();

  readAndWriteVar();

  SERIAL_DEBUG.println("----------------------------------------------");
  SERIAL_DEBUG.println("PAGE:");
  SERIAL_DEBUG.print(" writing and retrieving EEPROM Page on I2C at address ");
  SERIAL_DEBUG.println(DEVICEADDRESS);
  SERIAL_DEBUG.println("----------------------------------------------");

  readAndWritePage(TEST_PAGE_ADDR, SHORT_BUFFER_LEN);


  SERIAL_DEBUG.println("----------------------------------------------");
  SERIAL_DEBUG.println("MULTI-PAGE:");
  SERIAL_DEBUG.print("writing and retrieving EEPROM Pages on I2C at address ");
  SERIAL_DEBUG.println(DEVICEADDRESS);
  SERIAL_DEBUG.println("----------------------------------------------");

  readAndWritePage(LONG_TEST_PAGE_ADDR, LONG_BUFFER_LEN);


  SERIAL_DEBUG.println("----------------------------------------------");
  SERIAL_DEBUG.println("MULTI-PAGE UNALINGED: ");
  SERIAL_DEBUG.print("writing and retrieving EEPROM Pages on I2C at address ");
  SERIAL_DEBUG.println(DEVICEADDRESS);
  SERIAL_DEBUG.println("----------------------------------------------");

  readAndWritePage(UNALIGNED_TEST_PAGE_ADDR, UNALIGNED_BUFFER_LEN);

  SERIAL_DEBUG.println("\nDone...");
}


void loop()
{
  // Nothing to do during loop
}

