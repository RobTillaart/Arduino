#pragma once
//
//    FILE: Cozir.h
//  AUTHOR: DirtGambit & Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: library for COZIR range of sensors for Arduino
//          Polling Mode
//     URL: https://github.com/RobTillaart/Cozir
//			http://forum.arduino.cc/index.php?topic=91467.0
//
// READ DATASHEET BEFORE USE OF THIS LIB !
//

#include "Arduino.h"
#include "SoftwareSerial.h"

#define COZIR_LIB_VERSION "0.2.1"

// OUTPUTFIELDS
// See datasheet for details.
// These defines can be OR-ed for the SetOutputFields command
#define CZR_LIGHT 			  0x2000
#define CZR_HUMIDITY		  0x1000
#define CZR_FILTLED			  0x0800
#define CZR_RAWLED			  0x0400
#define CZR_MAXLED			  0x0200
#define CZR_ZEROPOINT		  0x0100
#define CZR_RAWTEMP			  0x0080
#define CZR_FILTTEMP		  0x0040
#define CZR_FILTLEDSIGNAL	  0x0020
#define CZR_RAWLEDSIGNAL	  0x0010
#define CZR_SENSTEMP		  0x0008
#define CZR_FILTCO2			  0x0004
#define CZR_RAWCO2			  0x0002

#define CZR_NONE			  0x0001

// easy default setting for streaming
#define CZR_HTC			      (CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
// not in datasheet for debug only
#define CZR_ALL				  0x3FFE

// OPERATING MODES
#define CZR_COMMAND			  0x00
#define CZR_STREAMING		  0x01
#define CZR_POLLING			  0x02


class COZIR
{
public:
    COZIR(Stream *);
    void init();  		// sets operatingMode to CZR_POLLING

    // warning: CZR_STREAMING is experimental, minimal tested.
    void SetOperatingMode(uint8_t mode);

    float Celsius();
    float Fahrenheit() { return (Celsius() * 1.8) + 32; };
    float Humidity();
    float Light();
    uint32_t CO2();

    // Callibration function, read datasheet before use
    uint16_t FineTuneZeroPoint(uint16_t , uint16_t);
    uint16_t CalibrateFreshAir();
    uint16_t CalibrateNitrogen();
    uint16_t CalibrateKnownGas(uint16_t );

	// following 3 functions are NOT RECOMMENDED, read datasheet before use
    // uint16_t CalibrateManual(uint16_t );
    // uint16_t SetSpanCalibrate(uint16_t );
    // uint16_t GetSpanCalibrate();

    // DIGIFILTER, use with care, read datasheet before use
    // default value = 32,
    // 1 = fast (noisy) 255 = slow (smoothed)
    // 0 = special. details see datasheet
    void SetDigiFilter(uint8_t value);
    uint8_t GetDigiFilter();

    // STREAMING MODE - needs testing...
    void SetOutputFields(uint16_t fields);  
    // void ClrOutputFields(); { SetOutputFields(CZR_NONE); } ; // TODO test
    void GetRecentFields();   // TODO test;

    void SetEEPROM(uint8_t address, uint8_t value);
    uint8_t GetEEPROM(uint8_t address);

    void GetVersionSerial();
    void GetConfiguration();

private:
    Stream *ser;
    char buffer[20];

    void Command(const char* str);
    uint32_t Request(const char* str);
};

// -- END OF FILE --
