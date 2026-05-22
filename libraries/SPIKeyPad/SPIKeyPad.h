#pragma once
//
//    FILE: SPIKeyPad.h
//  AUTHOR: Rob Tillaart, Chris0xdeadbeef
// VERSION: 0.1.2
//    DATE: 2026-04-09
// PURPOSE: Arduino library for 4x4 KeyPad using an SPI MCP23S08
//     URL: https://github.com/RobTillaart/SPIKeyPad


#include "Arduino.h"
#include "SPI.h"

#define SPI_KEYPAD_LIB_VERSION    (F("0.1.2"))

/// @brief Special keypad return values.
enum SPIKeyPadState : uint8_t
{
  /// @brief Returned when no key is pressed.
  SPI_KEYPAD_NOKEY = 16,

  /// @brief Returned when multiple keys are pressed or an error occurs.
  SPI_KEYPAD_FAIL = 17,

  /// @brief Returned when keypad is read too quickly.
  SPI_KEYPAD_THRESHOLD = 255
};


/// @brief Supported keypad layouts.
enum SPIKeyPadMode : uint8_t
{
  SPI_KEYPAD_INVALID = 0,
  SPI_KEYPAD_4x4 = 44,
  SPI_KEYPAD_5x3 = 53,
  SPI_KEYPAD_6x2 = 62,
  SPI_KEYPAD_8x1 = 81
};


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

  /**
   * @brief Construct a SPIKeyPad object using software SPI.
   * @param select Chip Select pin.
   * @param dataIn SPI MISO pin.
   * @param dataOut SPI MOSI pin.
   * @param clock SPI clock pin.
   * @param address MCP23S08 hardware address.
   */
  SPIKeyPad(
    uint8_t select,
    uint8_t dataIn,
    uint8_t dataOut,
    uint8_t clock,
    uint8_t address = 0x00
  );

  /**
   * @brief Construct a SPIKeyPad object using hardware SPI.
   * @param select Chip Select pin.
   * @param spi Pointer to SPI interface.
   */
  SPIKeyPad(
    uint8_t select,
    __SPI_CLASS__* spi
  );

  /**
   * @brief Construct a SPIKeyPad object using hardware SPI.
   * @param select Chip Select pin.
   * @param address MCP23S08 hardware address.
   * @param spi Pointer to SPI interface.
   */
  SPIKeyPad(
    uint8_t select,
    uint8_t address = 0x00,
    __SPI_CLASS__* spi = &SPI
  );


  /**
   * @brief Initialize keypad and MCP23S08.
   * @return true if initialization succeeded.
   */
  [[nodiscard]] bool begin();


  /**
   * @brief Get MCP23S08 address.
   * @return Device address.
   */
  [[nodiscard]] uint8_t getAddress() const;


  /**
   * @brief Get currently pressed key.
   * @return Key index or SPI_KEYPAD_NOKEY.
   */
  [[nodiscard]] uint8_t getKey();


  /**
   * @brief Get previously detected key.
   * @return Last key index.
   */
  [[nodiscard]] uint8_t getLastKey() const;


  /**
   * @brief Check if any key is currently pressed.
   * @return true if pressed.
   */
  [[nodiscard]] bool isPressed();


  /**
   * @brief Get translated character from keymap.
   * @return Character or SPI_KEYPAD_THRESHOLD.
   */
  [[nodiscard]] uint8_t getChar();


  /**
   * @brief Get previously translated character.
   * @return Character or SPI_KEYPAD_THRESHOLD.
   */
  [[nodiscard]] uint8_t getLastChar() const;


  /**
   * @brief Load key translation map.
   * @param keyMap Pointer to character map.
   *
   * Expected minimum size:
   * - 19 chars for 4x4
   * - user responsibility.
   */
  void loadKeyMap(const char * keyMap);


  /**
   * @brief Set keypad layout mode.
   * @param mode Keypad layout mode.
   */
  void setKeyPadMode(const SPIKeyPadMode mode = SPI_KEYPAD_4x4);


  /**
   * @brief Get current keypad mode.
   * @return Current keypad mode.
   */
  [[nodiscard]] SPIKeyPadMode getKeyPadMode() const;


  /**
   * @brief Set debounce threshold.
   * @param value Debounce time in milliseconds.
   */
  void setDebounceThreshold(const uint16_t value = 0);


  /**
   * @brief Get debounce threshold.
   * @return Debounce threshold in milliseconds.
   */
  [[nodiscard]] uint16_t getDebounceThreshold() const;


  /**
   * @brief Get last keypad read timestamp.
   * @return Timestamp in milliseconds.
   */
  [[nodiscard]] uint32_t getLastTimeRead() const;


  /**
   * @brief Set SPI bus speed.
   * @param speed SPI speed in Hz.
   */
  void setSPIspeed(uint32_t speed);


  /**
   * @brief Get SPI bus speed.
   * @return SPI speed in Hz.
   */
  [[nodiscard]] uint32_t getSPIspeed() const;


  /**
   * @brief Check if hardware SPI is used.
   * @return true if hardware SPI is enabled.
   */
  [[nodiscard]] bool usesHWSPI() const;


protected:

  /**
   * @brief Write MCP23S08 register.
   * @param reg Register address.
   * @param value Value to write.
   * @return true on success.
   */
  bool writeReg(uint8_t reg, uint8_t value);


  /**
   * @brief Read MCP23S08 register.
   * @param reg Register address.
   * @return Register value.
   */
  uint8_t readReg(uint8_t reg);


  /**
   * @brief Software SPI transfer.
   * @param val Byte to transfer.
   * @return Received byte.
   */
  uint8_t swSPI_transfer(uint8_t val);


  /**
   * @brief Internal keypad matrix read.
   * @param mask GPIO mask.
   * @return Key matrix state.
   */
  uint8_t _read(uint8_t mask);


  uint8_t _getKey4x4();
  uint8_t _getKey5x3();
  uint8_t _getKey6x2();
  uint8_t _getKey8x1();


  uint8_t _address = 0;
  uint8_t _select  = 0;
  uint8_t _dataOut = 0;
  uint8_t _dataIn  = 0;
  uint8_t _clock   = 0;

  bool _hwSPI = true;

  //  10 MHz is maximum for MCP23S08, 8 is a better clock divider on AVR.
  uint32_t _SPIspeed = 8000000;

  __SPI_CLASS__ * _mySPI;
  SPISettings _spi_settings;

  uint8_t  _lastKey;
  SPIKeyPadMode _mode;
  uint16_t _debounceThreshold;
  uint32_t _lastTimeRead;

  const char * _keyMap = nullptr;
};


//  -- END OF FILE --

