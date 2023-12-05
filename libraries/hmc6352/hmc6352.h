#pragma once
//
//    FILE: hmc6352.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
// PURPOSE: HMC6352 library for Arduino


#include "Wire.h"
#include "Arduino.h"


#define HMC6352_LIB_VERSION                    (F("0.4.0"))

//  status function calls
#define HMC6532_OK                               0
#define HMC6352_ERROR_PARAM1                   -20
#define HMC6352_ERROR_PARAM2                   -21

//  I2C related errors
#define HMC6532_I2C_OK                          0
#define HMC6532_I2C_ERROR_BUFFEROVERFLOW       -1
#define HMC6532_I2C_ERROR_ADDR_NACK            -2
#define HMC6532_I2C_ERROR_DATA_NACK            -3
#define HMC6532_I2C_ERROR_OTHER                -4
#define HMC6352_I2C_ERROR_REQ_FROM             -10


enum hmcMode
{
  STANDBY = 0, QUERY = 1, CONT = 2, ERROR
};


enum hmcOutputMode
{
  HEADING = 0, RAWMAGX = 1, RAWMAGY= 2, MAGX = 3, MAGY = 4
};


class hmc6352
{
public:
  hmc6352(uint8_t address, TwoWire *wire = &Wire);

  bool begin();
  bool isConnected();


  //  BASIC CALLS FOR STANDBY MODE
  int getHeading(void);   //  short for askHeading() & readHeading()
  int askHeading(void);
  int readHeading(void);

  int wakeUp(void);
  int sleep(void);


  //  EXPERT CALLS
  int factoryReset();

  int setOperationalModus(hmcMode mode, uint8_t frequency, bool periodicReset);
  int getOperationalModus();

  int setOutputModus(uint8_t om);
  int getOutputModus();

  int callibrationOn();
  int callibrationOff();

  //  to change the start up address.
  int setI2CAddress(uint8_t address);
  int getI2CAddress();

  int writeEEPROM(uint8_t address, uint8_t data);
  int readEEPROM(uint8_t address);

  int writeRAM(uint8_t address, uint8_t data);
  int readRAM(uint8_t address);

  //  allow power users to set operational mode flags
  int saveOpMode(byte OpMode);

  //  NOT TESTED
  int setTimeDelay(uint8_t milliSeconds);
  int getTimeDelay();

  //  nosm = NumberOfSummedMeasurements 1..16
  int setMeasurementSumming(uint8_t nosm);
  int getMeasurementSumming();
  int updateOffsets();

  int getSWVersionNumber();

private:
  int cmd(uint8_t c);
  int readCmd(uint8_t c, uint8_t address);
  int writeCmd(uint8_t c, uint8_t address, uint8_t data);

  uint8_t   _address;
  TwoWire*  _wire;
};


//  -- END OF FILE --

