#pragma once
//
//    FILE: SPIKeyPad.h
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef
// VERSION: 0.1.1
//    DATE: 2026-04-09
// PURPOSE: Arduino library for 4x4 KeyPad using an SPI MCP23S08
//     URL: https://github.com/RobTillaart/SPIKeyPad


#include "Arduino.h"
#include "SPI.h"


#define SPI_KEYPAD_LIB_VERSION    (F("0.1.1"))

//  KEYPAD SPECIAL "KEY VALUES"
/// @brief Returned when no key is pressed
constexpr uint8_t SPI_KEYPAD_NOKEY     = 16;
/// @brief Returned when multiple keys are pressed or other error
constexpr uint8_t SPI_KEYPAD_FAIL      = 17;
/// @brief Returned when requested a key too fast
constexpr uint8_t SPI_KEYPAD_THRESHOLD = 255;


//  KEYPAD LAYOUTS
constexpr uint8_t SPI_KEYPAD_4x4 = 44;
constexpr uint8_t SPI_KEYPAD_5x3 = 53;
constexpr uint8_t SPI_KEYPAD_6x2 = 62;
constexpr uint8_t SPI_KEYPAD_8x1 = 81;


#ifndef __SPI_CLASS__
  //  MBED must be tested before RP2040
  #if defined(ARDUINO_ARCH_MBED)
  #define __SPI_CLASS__   SPIClass
  #elif defined(ARDUINO_ARCH_RP2040)
  #define __SPI_CLASS__   SPIClassRP2040
  #else
  #define __SPI_CLASS__   SPIClass
  #endif
#endif


/// @brief SPI based 4x4 (et al) keypad driver using an MCP23S08
class SPIKeyPad
{
public:
  /// @brief Construct a SPIKeyPad object using software SPI.
  /// @param select = Chip Select pin used for MCP23S08
  SPIKeyPad(uint8_t select, uint8_t dataIn, uint8_t dataOut, uint8_t clock, uint8_t address = 0x00);
  /// @brief Construct a SPIKeyPad object using hardware SPI.
  /// @param select = Chip Select pin used for MCP23S08
  SPIKeyPad(int select, __SPI_CLASS__* spi);
  /// @brief Construct a SPIKeyPad object using hardware SPI.
  /// @param select = Chip Select pin used for MCP23S08
  SPIKeyPad(int select, int address = 0x00, __SPI_CLASS__* spi = &SPI);

  //  call SPI.begin() first if HW SPI is used
  /// @brief Initialize keypad and underlying MCP23S08
  /// @return true if initialization succeeded
  [[nodiscard]] bool     begin();
  [[nodiscard]] uint8_t  getAddress();

  //  get raw key's 0..15
  /// @brief Get the currently pressed key
  /// @return key index (0–15) or (16) NO_KEY
  [[nodiscard]] uint8_t  getKey();
  [[nodiscard]] uint8_t  getLastKey();
  /// @brief Check if any key is currently pressed
  /// @return true if a key is pressed
  [[nodiscard]] bool     isPressed();

  //  get 'translated' keys
  //  user must load KeyMap, there is no check.
  [[nodiscard]] uint8_t  getChar();
  [[nodiscard]] uint8_t  getLastChar();
  void     loadKeyMap(char * keyMap);   //  char[19]

  //  mode functions - experimental
  void     setKeyPadMode(uint8_t mode = SPI_KEYPAD_4x4);
  [[nodiscard]] uint8_t  getKeyPadMode();

  //  value in milliseconds, max 65535 ms
  void     setDebounceThreshold(uint16_t value = 0);
  [[nodiscard]] uint16_t getDebounceThreshold();
  [[nodiscard]] uint32_t getLastTimeRead();

  //       SPI
  //       speed in Hz
  void     setSPIspeed(uint32_t speed);
  [[nodiscard]] uint32_t getSPIspeed() { return _SPIspeed; };
  [[nodiscard]] bool     usesHWSPI()   { return _hwSPI; };


protected:
  bool     writeReg(uint8_t reg, uint8_t value);
  uint8_t  readReg(uint8_t reg);

  uint8_t  _address = 0;
  uint8_t  _select  = 0;
  uint8_t  _dataOut = 0;
  uint8_t  _dataIn  = 0;
  uint8_t  _clock   = 0;

  bool     _hwSPI = true;
  //       10 MHz is maximum, 8 is a better clock divider on AVR.
  uint32_t    _SPIspeed = 8000000;
  __SPI_CLASS__ * _mySPI;
  SPISettings     _spi_settings;
  uint8_t  swSPI_transfer(uint8_t val);

  uint8_t  _lastKey;
  uint8_t  _mode;
  uint8_t  _read(uint8_t mask);
  uint16_t _debounceThreshold;
  uint32_t _lastTimeRead;

  uint8_t  _getKey4x4();
  uint8_t  _getKey5x3();
  uint8_t  _getKey6x2();
  uint8_t  _getKey8x1();


  char *  _keyMap = NULL;
};


//  -- END OF FILE --

