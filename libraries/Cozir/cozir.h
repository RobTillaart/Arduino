#pragma once
//
//    FILE: Cozir.h
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.2.6
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: https://github.com/RobTillaart/Cozir
//          http://forum.arduino.cc/index.php?topic=91467.0
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//

#include "Arduino.h"

#define COZIR_LIB_VERSION   (F("0.2.6"))

// OUTPUTFIELDS
// See datasheet for details.
// These defines can be OR-ed for the SetOutputFields command
#define CZR_LIGHT           0x2000
#define CZR_HUMIDITY        0x1000
#define CZR_FILTLED         0x0800
#define CZR_RAWLED          0x0400
#define CZR_MAXLED          0x0200
#define CZR_ZEROPOINT       0x0100
#define CZR_RAWTEMP         0x0080
#define CZR_FILTTEMP        0x0040
#define CZR_FILTLEDSIGNAL   0x0020
#define CZR_RAWLEDSIGNAL    0x0010
#define CZR_SENSTEMP        0x0008
#define CZR_FILTCO2         0x0004
#define CZR_RAWCO2          0x0002

#define CZR_NONE            0x0001

// easy default setting for streaming
#define CZR_HTC             (CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
// not in datasheet for debug only
#define CZR_ALL             0x3FFE

// OPERATING MODES
#define CZR_COMMAND         0x00
#define CZR_STREAMING       0x01
#define CZR_POLLING         0x02

// EEPROM ADRESSES
// P 11-12 manual - maybe some deserve a function?
//      Name        Address     Default value/ notes
#define AHHI        0x00     // reserved
#define ANLO        0x01     // reserved
#define ANSOURCE    0x02     // reserved
#define ACINITHI    0x03     // 87
#define ACINITLO    0x04     // 192
#define ACHI        0x05     // 94
#define ACLO        0x06     // 128
#define ACONOFF     0x07     // 0
#define ACPPMHI     0x08     // 1
#define ACPPMLO     0x09     // 194
#define AMBHI       0x0A     // 1
#define AMBLO       0x0B     // 194
#define BCHI        0x0C     // 0
#define BCLO        0x0D     // 8


class COZIR
{
public:
    COZIR(Stream *);
    void     init();      // sets operatingMode to CZR_POLLING

    // warning: CZR_STREAMING is experimental, minimal tested.
    void     SetOperatingMode(uint8_t mode);

    float    Celsius();
    float    Fahrenheit() { return (Celsius() * 1.8) + 32; };
    float    Humidity();
    float    Light();
    uint32_t CO2();
    uint16_t getPPMFactor();   // P14 . command  return 1, 10 or 100

    // Callibration function, read datasheet before use
    uint16_t FineTuneZeroPoint(uint16_t v1, uint16_t v2);
    uint16_t CalibrateFreshAir();
    uint16_t CalibrateNitrogen();
    uint16_t CalibrateKnownGas(uint16_t value);

    // WARNING: following 3 functions are NOT RECOMMENDED, 
    //          read datasheet before use
    // uint16_t CalibrateManual(uint16_t value);
    // uint16_t SetSpanCalibrate(uint16_t value);
    // uint16_t GetSpanCalibrate();

    // DIGIFILTER, use with care, read datasheet before use
    //     32 = default value = 32,
    //      1 = fast (noisy) 
    //    255 = slow (smoothed)
    //      0 = special. details see datasheet
    void     SetDigiFilter(uint8_t value);
    uint8_t  GetDigiFilter();

    // STREAMING MODE - needs testing...
    void     SetOutputFields(uint16_t fields);
    void     ClrOutputFields() { SetOutputFields(CZR_NONE); };
    // WARNING:
    // After a call to GetRecentFields() you must read the serial port yourself as
    // the internal buffer of this Class cannot handle the possible large output.
    // It can be over 100 bytes long lines!
    void     GetRecentFields();

    // EEPROM
    // TODO some specific wrappers? in the end it are only 6 different calls?
    void     SetEEPROM(uint8_t address, uint8_t value);
    uint8_t  GetEEPROM(uint8_t address);

    void     GetVersionSerial();
    void     GetConfiguration();

private:
    Stream   *ser;
    char     buffer[20];
    uint16_t _ppmFactor = 1;

    void     Command(const char* str);
    uint32_t Request(const char* str);
};

// -- END OF FILE --
