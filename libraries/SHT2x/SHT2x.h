#pragma once
//
//    FILE: SHT2x.h
//  AUTHOR: Rob Tillaart, Viktor Balint, JensB, morfeus02
// VERSION: 0.5.1
//    DATE: 2023-11-25
// PURPOSE: Arduino library for the SHT2x temperature and humidity sensor
//     URL: https://github.com/RobTillaart/SHT2x
//


#include "Arduino.h"
#include "Wire.h"


#define SHT2x_LIB_VERSION             (F("0.5.1"))


//  fields getStatus
#define SHT2x_STATUS_OPEN_CIRCUIT     0x00
#define SHT2x_STATUS_TEMPERATURE      0x00  //  only bit 1
#define SHT2x_STATUS_HUMIDITY         0x02  //  only bit 1
#define SHT2x_STATUS_CLOSED_CIRCUIT   0x03


//  Error codes
//  Error codes are kept somewhat in sync with SHT31 library for consistency where applicable.
#define SHT2x_OK                      0x00  //  Default success value, no error.
#define SHT2x_ERR_WRITECMD            0x81  //  Error during I2C write command.
#define SHT2x_ERR_READBYTES           0x82  //  Error during I2C read bytes.
#define SHT2x_ERR_HEATER_OFF          0x83  //  Failed to switch off the internal heater.
#define SHT2x_ERR_NOT_CONNECT         0x84  //  Sensor not connected or does not acknowledge on the I2C bus.
#define SHT2x_ERR_CRC_TEMP            0x85  //  CRC check failed for the temperature reading.
#define SHT2x_ERR_CRC_HUM             0x86  //  CRC check failed for the humidity reading.
#define SHT2x_ERR_CRC_STATUS          0x87  //  CRC check failed for the status register (currently not actively used for status validation within library).
#define SHT2x_ERR_HEATER_COOLDOWN     0x88  //  Heater is in its mandatory cool-down period and cannot be re-enabled yet.
#define SHT2x_ERR_HEATER_ON           0x89  //  Failed to switch on the internal heater.
#define SHT2x_ERR_RESOLUTION          0x8A  //  Invalid resolution parameter provided (since 0.2.0).
// Consider adding SHT2x_ERR_UNEXPECTED_STATUS for status check failures in readTemperature/readHumidity.
// Currently, these failures reuse SHT2x_ERR_READBYTES.

//  Asynchronous request types
#define SHT2x_REQ_NONE                0x00  //  No active asynchronous request.
#define SHT2x_REQ_TEMPERATURE         0x01  //  Asynchronous temperature request is currently active.
#define SHT2x_REQ_HUMIDITY            0x02  //  Asynchronous humidity request is currently active.
#define SHT2x_REQ_FAIL                0xFF  //  Asynchronous humidity request is currently active.


class SHT2x
{
public:
  SHT2x(TwoWire *wire = &Wire); // Constructor, accepts a TwoWire pointer for I2C communication.

  //  Core functions
  bool begin();           // Initializes the sensor (checks connection, performs a reset).
  bool isConnected();     // Checks if the sensor acknowledges its address on the I2C bus.
  bool reset();           // Performs a soft reset on the sensor. Takes up to 15ms to complete.

  //  Synchronous measurement
  //  This function blocks program execution while reading temperature and then humidity.
  //  It must be called before getTemperature() or getHumidity() to update sensor readings.
  bool read();

  //  Getters for sensor values
  //  These functions return values based on the last successful read() or asynchronous read operation.
  float    getTemperature();    // Returns the temperature in degrees Celsius (°C).
  float    getHumidity();       // Returns the relative humidity in percent (%).
  uint16_t getRawTemperature(); // Returns the raw 16-bit sensor data for temperature.
  uint16_t getRawHumidity();    // Returns the raw 16-bit sensor data for humidity.

  //  Status and timing related functions
  //  getStatus() returns the 2 status bits from the user register, which indicate the
  //  type of measurement stored in the sensor's memory (e.g., temperature or humidity).
  //  See SHT2x_STATUS_* defines for interpreting the return value.
  uint8_t  getStatus();
  uint32_t lastRead();          // Returns the timestamp (from millis()) of the last successful synchronous read() operation.

  //  Heater functions
  //  WARNING: The internal heater can affect sensor accuracy or even damage the sensor if used improperly.
  //  The datasheet recommends using it for short periods (e.g., for functionality checks or to drive off condensation).
  //  The library enforces a cool-down period (SHT2x_HEATER_TIMEOUT in .cpp, default 180s) after use.
  //  The user MUST call heatOff() manually or ensure isHeaterOn() is called periodically,
  //  as isHeaterOn() will also turn the heater off if the configured timeout has expired.
  void    setHeatTimeout(uint8_t seconds); // Sets the heater active duration (max 180 seconds).
  uint8_t getHeatTimeout();                // Returns the configured heater timeout in seconds.
  bool    heatOn();                        // Turns the heater on, if not in cool-down. Returns false on failure.
  bool    heatOff();                       // Turns the heater off. Returns false on failure.
  bool    isHeaterOn();                    // Checks if the heater is currently active. Also turns off heater if timeout has passed.

  //  Heater level control (values 0-15). Refer to the sensor datasheet for specific effects.
  //  Note: Not all SHT2x variants might support this feature robustly or document it clearly.
  bool setHeaterLevel(uint8_t level);      // Sets the heater power level.
  bool getHeaterLevel(uint8_t &level);   // Reads the current heater power level (passed by reference).

  //  Error handling
  //  Returns the last error code (see SHT2x_ERR_* defines) and clears the internal error flag to SHT2x_OK.
  //  It's important to check for errors after operations that return bool, or if unexpected values are read.
  int getError();

  //  Electronic Identification Code (EIC)
  //  Functions to read the unique ID and firmware version from the sensor.
  //  Details can be found in the Sensirion EIC documentation. Primarily tested on Si7021.
  uint32_t getEIDA(); // Returns Part A of the Electronic ID.
  uint32_t getEIDB(); // Returns Part B of the Electronic ID.
  uint8_t  getFirmwareVersion(); // Returns the firmware version code.

  //  Measurement Resolution Control
  //  This feature is marked as experimental (since 0.2.0) and requires thorough testing.
  //  Consult the specific sensor's datasheet for supported resolutions and their impact on measurement time and accuracy.
  //  Resolution Table (from SHT20 datasheet, other sensors may vary):
  //  RES | Humidity | Temperature
  //  -----------------------------
  //   0  |  12 bit  |   14 bit  (default for SHT2x class)
  //   1  |  08 bit  |   12 bit
  //   2  |  10 bit  |   13 bit
  //   3  |  11 bit  |   11 bit
  bool    setResolution(uint8_t res = 0); // Sets resolution (res = 0..3). Returns false for invalid values.
  uint8_t getResolution();                // Returns the currently configured resolution (cached value).

  //  Asynchronous Interface (experimental)
  //  Provides non-blocking calls to initiate sensor readings.
  //  The user must then periodically check if the measurement is ready before reading the data.
  bool requestTemperature(); // Initiates a temperature measurement. Sensor will start conversion.
  bool requestHumidity();    // Initiates a humidity measurement. Sensor will start conversion.

  //  Check if data is ready after an asynchronous request.
  //  The time required for measurement depends on the configured resolution (see datasheet or implementation of reqHumReady/reqTempReady in .cpp).
  bool reqTempReady();       // Returns true if temperature data is ready to be read.
  bool reqHumReady();        // Returns true if humidity data is ready to be read.
  bool requestReady();       // Returns true if either temperature or humidity data is ready.

  //  Read data from the sensor after reqTempReady() or reqHumReady() has indicated data is available.
  bool readTemperature();    // Reads the previously requested temperature data. Updates getTemperature().
  bool readHumidity();       // Reads the previously requested humidity data. Updates getHumidity().

  uint32_t lastRequest();    // Returns the timestamp (from millis()) of the last asynchronous request.
  uint8_t  getRequestType(); // Returns the type of the current or last asynchronous request (see SHT2x_REQ_* defines).

  //  Other sensor features
  //  Checks the battery status bit in the user register (indicates VDD < ~2.25V).
  //  Note: Not all SHT2x compatible sensors may reliably support or implement this feature.
  bool batteryOK();

protected:
  //  Calculates CRC8 checksum for data integrity using the polynomial specified in the SHT2x datasheet.
  //  Polynomial: x^8 + x^5 + x^4 + 1 (0x131, which is 0x31 as the MSB is implicit in the algorithm).
  uint8_t  crc8(const uint8_t *data, uint8_t len);

  //  I2C communication helper functions
  bool     writeCmd(uint8_t cmd); // Writes a single command byte to the sensor.
  bool     writeCmd(uint8_t cmd, uint8_t value); // Writes a command byte followed by a value byte.
  //  Reads 'n' bytes into the 'val' buffer, with a 'maxDuration' timeout (in milliseconds).
  bool     readBytes(uint8_t n, uint8_t *val, uint8_t maxDuration);

  //  Specific to Si70xx series sensors (and compatible ones like HTU2x):
  //  Reads the temperature value that was measured by the sensor during the last humidity acquisition.
  //  This can be called after getHumidity() or (requestHumidity() followed by readHumidity()).
  bool     readCachedTemperature();

  TwoWire* _wire;  // Pointer to the TwoWire interface (e.g., &Wire, &Wire1)

  //  Cached sensor readings and state variables
  uint32_t _lastRead;       // Timestamp of the last successful synchronous read operation.
  uint16_t _rawTemperature; // Last raw temperature reading from the sensor.
  uint16_t _rawHumidity;    // Last raw humidity reading from the sensor.
  uint8_t  _status;         // Sensor status bits from the user register.
  uint8_t  _error;          // Stores the last error code encountered (see SHT2x_ERR_*).
  uint8_t  _resolution;     // Currently configured measurement resolution (0-3).

  //  Variables for asynchronous operation management
  uint32_t _lastRequest;    // Timestamp of the last asynchronous request made.
  uint8_t  _requestType;    // Type of current async request (SHT2x_REQ_NONE, SHT2x_REQ_TEMPERATURE, SHT2x_REQ_HUMIDITY).

  //  Variables for internal heater control
  uint8_t  _heatTimeout;    // Configured heater timeout duration in seconds.
  uint32_t _heaterStart;    // Timestamp (millis) when the heater was last turned on.
  uint32_t _heaterStop;     // Timestamp (millis) when the heater was last turned off.
  bool     _heaterOn;       // Current state of the heater (true if on, false if off).
};


//  Derived classes for specific sensor models.
//  These primarily serve to provide a named class for better code readability
//  and user convenience, inheriting all core functionality from the SHT2x base class.
//  For the Si70xx series, they also explicitly bring the protected `readCachedTemperature`
//  method into the public scope using 'using SHT2x::readCachedTemperature;'.

class SHT20 : public SHT2x
{
public:
  SHT20(TwoWire *wire = &Wire);
};


class SHT21 : public SHT2x
{
public:
  SHT21(TwoWire *wire = &Wire);
};


class SHT25 : public SHT2x
{
public:
  SHT25(TwoWire *wire = &Wire);
};


//  HTU2x series are often compatible with SHT2x commands.
class HTU20 : public SHT2x
{
public:
  HTU20(TwoWire *wire = &Wire);
};


class HTU21 : public SHT2x
{
public:
  HTU21(TwoWire *wire = &Wire);
};


//  Si70xx series sensors. These have a command to read temperature
//  measured during humidity acquisition.
class Si7013 : public SHT2x
{
public:
  Si7013(TwoWire *wire = &Wire);
  using SHT2x::readCachedTemperature; // Make protected base method public for this derived class.
};


class Si7020 : public SHT2x
{
public:
  Si7020(TwoWire *wire = &Wire);
  using SHT2x::readCachedTemperature;
};


class Si7021 : public SHT2x
{
public:
  Si7021(TwoWire *wire = &Wire);
  using SHT2x::readCachedTemperature;
};


//  GY21 is a common module name that often uses SHT2x or Si7021 compatible sensors.
class GY21 : public SHT2x
{
public:
  GY21(TwoWire *wire = &Wire);
};


//  -- END OF FILE --

