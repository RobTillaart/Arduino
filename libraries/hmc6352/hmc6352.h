#pragma once
//
//    FILE: hmc6352.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: HMC6352 library for Arduino
//
// HISTORY: see cpp file

#include "Wire.h"
#include "Arduino.h"

#define HMC6352_LIB_VERSION     "0.2.0"

/* ERROR CODES ALL FUNCTIONS
//
// * twi_writeTo codes (== endTransmission  commands)
//   0 .. OK
//  -1 .. length to long for buffer
//  -2 .. address send, NACK received
//  -3 .. data send, NACK received
//  -4 .. other twi error (lost bus arbitration, bus error, ..)
//
// * requestFrom
// -10 .. not enough values returned
//
// * function calls
//   0 .. OK
// -20 .. error param1
// -21 .. error param2
// -22 .. error param3
//
*/

enum hmcMode { STANDBY=0, QUERY=1, CONT=2, ERROR};

class hmc6352
{
public:
  hmc6352(uint8_t device);

#if defined (ESP8266) || defined(ESP32)
  void begin(uint8_t sda, uint8_t scl);
#endif
  void begin();
  
  // BASIC CALLS FOR STANDBY MODE
  int getHeading(void); // just a merge of ask & read
  int askHeading(void);
  int readHeading(void);

  int wakeUp(void);
  int sleep(void);

  // EXPERT CALLS
  int factoryReset();

  int setOperationalModus(hmcMode m, uint8_t freq, bool periodicReset);
  int getOperationalModus();

  int setOutputModus(uint8_t om);
  int getOutputModus();

  int callibrationOn(void);
  int callibrationOff(void);

  int setI2CAddress(uint8_t address);
  int getI2CAddress();

  int writeEEPROM(uint8_t address, uint8_t data);
  int readEEPROM(uint8_t address);

  int writeRAM(uint8_t address, uint8_t data);
  int readRAM(uint8_t address);

  // allow power users to set operational mode flags
  int saveOpMode(byte OpMode);

  // NOT TESTED / UNKNOWN
  int setTimeDelay(uint8_t msec);
  int getTimeDelay();
  int setMeasurementSumming(uint8_t ms);
  int getMeasurementSumming();
  int updateOffsets(void);

private:
  int cmd(uint8_t c);
  int readCmd(uint8_t c, uint8_t address);
  int writeCmd(uint8_t c, uint8_t address, uint8_t data);

  uint8_t _device;
};

// -- END OF FILE -- 
