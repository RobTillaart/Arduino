
[![Arduino CI](https://github.com/RobTillaart/MCP4725/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/MCP4725/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/MCP4725.svg?maxAge=3600)](https://github.com/RobTillaart/MCP4725/releases)

# MCP4725

Arduino library for 12 bit I2C DAC - MCP4725 


## Description

The MCP4725 is an I2C 12 bit Digital to Analog Converter (DAC). It is possible to have
up to 8 MCP4725 on one bus. The MCP4725 supports 100KHz 400KHz and 3.4MHz bus speeds.

The output of the MCP4725 depends on the voltage supplied, which is in the range 
of 2.7V .. 5.5V. Check datasheet for the details.


## Interface

### Constructor

- **MCP4725(deviceAddress, TwoWire \*wire = &Wire);)** Constructor, needs I2C address, optional set Wire bus
- **begin(dataPin, clockPin)** for ESP32. Returns true if connected.
- **begin()** for UNO and other boards with hard wired I2C pins. Returns true if connected.
Only suppport for Wire so not for Wire1 or Wire2 etc
- **isConnected()** returns true if device (address) can be seen on the I2C bus.


### base

- **setValue(value)** value = 0 .. 4095  
Uses writeFastMode and does not write to EEPROM.
Therfore it does not update the lastWriteEEPROM timestamp.
- **getValue()** returns last value set from cache, this is much faster than readDAC().  
This latter gives the real value from the MCP4725. A difference can be caused by power
outage a reset etc.
- **setPercentage(perc)** perc = 0..100.0% Convenience wrapper around setValue().
- **getPercentage()** returns percentage. Wrapper around getValue().
- **writeDAC(value, const bool EEPROM = false)** Writes to DAC and conditionally to EEPROM.  
This latter is for startup / reset behavior. Check datasheet for the detail behavior.
- **ready()** returns true if a new value can be written to the MCP4725.  
Return false if recently was written to EEPROM.
- **readDAC()** reads the current value set in the MCP4725.
- **readEEPROM()** reads the current value in the EEPROM of the MCP4725.
- **getLastWriteEEPROM()** returns time in millis() when last value was written to EEPROM.  
Page 3 of datasheet states it takes **25 - 50 ms** before values are written to EEPROM. 
So the exact timing of a sensor can differ a lot. 
When writing to EEPROM with **writeDAC()** one should check it is at least 50 ms ago.
If one know the specific timing of a sensor one can tune this or even make it adaptive.  


## Experimental

Check datasheet for these functions, (not tested enough yet).

- **writePowerDownMode(PDM, const bool EEPROM = false)**
- **readPowerDownModeEEPROM()**
- **readPowerDownModeDAC()**
- **powerOnReset()**
- **powerOnWakeUp()**

More investigations needed for:
- Writing to EEPROM, **ready()** and **getLastWriteEEPROM()**  
checking when and how long the sensor blocks needs to be verified in detail in practice. 


## Address Notes

The address of the MCP4725 in the demo sketches is set to 0x62 as that 
was the address of the sensor I had during writing. 
According to the datasheet the address has the following bit pattern: 

address  011000FFU   (so 0x6?)

         F = Factory set bit
         U = User configurable bit

This means you can have at most 8 MCP4725 in one I2C bus (without multiplexing).
You have to specify the factory bits in your order, but not all shops might
provide all versions of the MCP4725.

```
MCP4725A0T-E/CH:  0110 000U   0x60 - 0x61
MCP4725A1T-E/CH:  0110 001U   0x62 - 0x63
MCP4725A2T-E/CH:  0110 010U   0x64 - 0x65
MCP4725A3T-E/CH:  0110 011U   0x66 - 0x67
```

If one need more DAC's one might have a look at the MCP4728
It has 4 channels per chip (no experience /library yet)


## Operation

See examples
