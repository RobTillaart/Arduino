
[![Arduino CI](https://github.com/RobTillaart/FRAM_I2C/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FRAM_I2C/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FRAM_I2C/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FRAM_I2C.svg?maxAge=3600)](https://github.com/RobTillaart/FRAM_I2C/releases)


# FRAM_I2C

Arduino library for I2C FRAM.


## Description

FRAM is a library to read from and write to (over I2C) an FRAM module.
The library has (since 0.5.0) four classes 
- **FRAM** 16 bit address.
- **FRAM32** 32 (17) bit address.
- **FRAM11** 11 bit address.
- **FRAM9** 9 bit address.

Currently only the **MB85RC1MT** is known to use 32 bit.
**FRAM32** can also address 16 bit devices although there is some overhead in footprint.

FRAM stands for Ferroelectric RAM - https://en.wikipedia.org/wiki/Ferroelectric_RAM

FRAM memory is much faster than EEPROM and almost as fast as (Arduino UNO) RAM.
Another important feature FRAM has in common with EEPROM is that FRAM keeps
its content after a reboot as it is non-volatile, even for years.
That makes it ideal to store configuration or logging data in a project.

Types of FRAM that should work with this library:

|  TYPE        |  SIZE    |  TESTED  |  NOTES                 |  uses    |  ref  |
|:------------:|---------:|:--------:|:-----------------------|:---------|:-----:|
|  MB85RC04    |    512   |    Y     |  no deviceID register  |  FRAM9   |  #35  |
|  MB85RC16    |    2 KB  |    Y     |  no deviceID register  |  FRAM11  |  #28  |
|  MB85RC64T   |    8 KB  |    Y     |                        |  FRAM    |       |
|  MB85RC128A  |   16 KB  |    N     |  no deviceID register  |  FRAM    |       |
|  MB85RC256V  |   32 KB  |    Y     |                        |  FRAM    |       |
|  MB85RC512T  |   64 KB  |    Y     |                        |  FRAM    |       |
|  MB85RC1MT   |  128 KB  |    Y     |                        |  FRAM32  |  #19  |


MB85RC128A has no size / deviceID, **clear()** will not work correctly, unless 
one calls **setSizeBytes(16 \* 1024)** to set the size manually.

For the FRAM9 and FRAM11 the size problem is solved (hard coded) in their class.


#### Notes

- Not all types of FRAM are tested. Please let me know if you have verified one that is not in the list.
- If there is no deviceID **getSize()** will not work correctly.
  - ==> fixed for FRAM9 and FRAM11
- Address = 0x50 (default) .. 0x57, depends on the lines A0..A2.
- **MB85RC1MT** uses even addresses only as it uses the next odd one internally.
So 0x50 uses 0x51 internally for the upper 64 KB block.
This latter will not be shown on an I2C scanner (to be tested).  
Not tested: expect the **MB85RC1MT** can be addressed with 2 instances of **FRAM**
too with adjacent addresses.


## Interface

```cpp
#include "FRAM.h"
```


### Constructors

- **FRAM(TwoWire \*wire = &Wire)** Constructor with optional Wire interface.
- **FRAM32(TwoWire \*wire = &Wire)** Constructor with optional Wire interface,
specific for **MB85RC1MT** type of device, 17 bit address.
- **FRAM11(TwoWire \*wire = &Wire)** Constructor with optional Wire interface,
specific for devices with 11 bit address e.g. **Cypress/Infineon 24CL16B**.
- **FRAM9(TwoWire \*wire = &Wire)** Constructor with optional Wire interface,
specific for devices with 9 bit address e.g. **MB85RC04**.


### Begin

- **int begin(uint8_t address = 0x50, int8_t writeProtectPin = -1)** address and writeProtectPin is optional.
Note the **MB85RC1MT** only uses even addresses.
- **int begin(int sda, int scl, uint8_t address = 0x50, int8_t writeProtectPin = -1)** idem for ESP32 a.o.
- **bool isConnected()** checks if the address set by begin() is visible on the I2C bus.


### Write & read

Support for basic types and two calls for generic objects, use casting if needed.  
In the **FRAM32** class these functions have an **uin32_t memaddr**.

- **void write8(uint16_t memaddr, uint8_t value)** uint8_t
- **void write16(uint16_t memaddr, uint16_t value)** uint16_t
- **void write32(uint16_t memaddr, uint32_t value)** uint32_t
- **void writeFloat(uint16_t memaddr, float value)** float
- **void writeDouble(uint16_t memaddr, double value)** double
  - For boards that have an 8 byte double.
- **void write(uint16_t memaddr, uint8_t \* obj, uint16_t size)** other types / sizes.
  - typical used for structs.
- **uint8_t read8(uint16_t memaddr)**
- **uint16_t read16(uint16_t memaddr)**
- **uint32_t read32(uint16_t memaddr)**
- **float readFloat(uint16_t memaddr)**
- **double readDouble(uint16_t memaddr)**
  - For board that have 8 byte double.
- **void read(uint16_t memaddr, uint8_t uint8_t \* obj, uint16_t size)**
  - One needs to allocate memory as the function won't.
- **uint32_t clear(uint8_t value = 0)** clears the whole FRAM by writing value to all addresses
  - default value is all zero's.
  - Returns the number of bytes written.
  - **clear()** does not work for **MB85RC128A** unless **setSizeBytes()** is used.


(Template functions, see issue #13)
- **uint16_t writeObject(uint16_t memaddr, T &obj)** writes an object to memaddr (and following bytes).
  - Returns memaddr + sizeof(obj) to get the next address to write to.
- **uint16_t readObject(uint16_t memaddr, T &obj)** reads an object from memaddr and next bytes.
  - Returns memaddr + sizeof(obj) to get the next address to read from.


(Experimental 0.5.1, see issue #30)
- **int32_t readUntil(uint16_t memaddr, char \*buf, uint16_t buflen, char separator)**
Reads FRAM from an address into **buf** until separator is encountered.
The separator is replaced by an '\0' - end of char array.
**ReadUntil()** returns the length of the buffer.
To get the address of the next "field" one must add ```memaddr += (length + 1)```.  
If the separator is not found after **buflen** characters the function returns -1.
However the buffer does contain the data read, which might be useful. 
Handle with care as buffer has probably no '\0' end char.
- **int32_t readLine(uint16_t memaddr, char \* buf, uint16_t buflen)**
Similar to **readUntil()**, reads a line from FRAM including the '\n'.
This '\n' is mandatory as end separator!.  
Note: The buffer needs one extra char for the delimiting '\0' end char.
To get the address of the next "field" one must add ```memaddr += length```.
This is an minor but important difference with **readUntil()**.
Note: the returning buffer contains the '\n' so one need to take care when
printing the buffer.


### ReadUntil

**readUntil()** can be used to read lines and/or fields from an FRAM filled with text.
For example logging written with the FRAM_logging.ino example.
Note: if memaddr + buflen >= size of FRAM, memory wrapping may occur.
The library does not check, so the user should.

Note: internally **readUntil()** reads buflen bytes to fill the buffer.
Then it searches for the separator. 
This is chosen to optimize performance for relative small buffers that are used most.
For large buffers this fetching of the whole buffer will take much time.
This can results in less responsiveness. 
Increasing the I2C bus speed might compensate this a bit.

Finally the **FRAM_readUntil.ino** sketch has a **readUntil()** implementation
that uses a per byte fetching.


### Write-protect

Will work only if a writeProtectPin was defined in **begin()** 

- **bool setWriteProtect(bool b)** make the FRAM write-protected by pulling the WP line HIGH or LOW.
  - Returns true if a writeProtectPin was defined in **begin()**.
    Otherwise the FRAM cannot be write protected.
- **bool getWriteProtect()** get current write protect status.
  - returns status (true/false).
  - Returns false if the writeProtectPin was not defined.



### Metadata

These may not work for devices that have no **deviceID** register.  
So use with care.

- **uint16_t getManufacturerID()** see table below.
- **uint16_t getProductID()** idem. Proprietary.
- **uint16_t getSize()** returns the size in kiloBYTE.
If the FRAM has no device ID register, the size cannot be read.
  - FRAM9 will return 0 as it is less than 1 KB. use GetSizeBytes() instead.
- **uint32_t getSizeBytes()** returns the size in BYTES.
  - Useful for iterating over the whole memory,
or testing the upper boundary.
- **void setSizeBytes(uint32_t value)** sets the size in bytes for **getSizeBytes()**.
To be used only if **getSize()** cannot determine the size.
As far as known this is for the **MB85RC128A** only.
See also remark in Future section below.
Can also be used to "virtually" reduce the size, e.g. to speed up **clear()**
if the FRAM is used only partial.


### Manufacturers ID

|  Name                 |  ID     |
|:----------------------|:-------:|
|  Fujitsu              |  0x00A  |
|  Ramtron              |  0x004  |

Additions are welcome.


### Sleep

(0.3.6 added - experimental)
- **void sleep()** puts the FRAM in sleep mode so it uses less power.
Still needs a power test for several types of FRAM.
- **bool wakeup(uint32_t trec = 400)** tries to wake up the device with a default recovery time of 400 microseconds.
Returns true if connected after the call.

According to the data sheets there are only three FRAM devices support the sleep command.
So use with care.

|  TYPE        |  SIZE  | SLEEP (datasheet)  |  CURRENT  |  CONFIRMED  |   NOTES   |
|:------------:|-------:|:------------------:|:---------:|:-----------:|:----------|
|  MB85RC04    |   512  |  not supported     |  -        |      N      |           |
|  MB85RC16    |   2 KB |  not supported     |  -        |      N      |           |
|  MB85RC64T   |   8 KB |  Y  Page 11        |  4.0 uA*  |      N      |           |
|  MB85RC128A  |  16 KB |  not supported     |  -        |      N      |           |
|  MB85RC256V  |  32 KB |  not supported     |  -        |      Y      |           |
|  MB85RC512T  |  64 KB |  Y  Page 12        |  4.0 uA*  |      N      |           |
|  MB85RC1MT   | 128 KB |  Y  Page 12        |  3.6 uA   |      Y      |  See #17  |

_current with \* are from datasheet_


### Current

Indicative power usage in uA in three modi (if supported).


|  TYPE      | SIZE   | STANDBY  | WRITE     | SLEEP     | NOTES   |
|:----------:|-------:|:--------:|:---------:|:---------:|:--------|
| MB85RC04   |   512  |          |           |  -        |         |
| MB85RC16   |   2 KB |          |           |  -        |         |
| MB85RC64T  |   8 KB |          |           |  4.0 uA   |         |
| MB85RC128A |  16 KB |          |           |  -        |         |
| MB85RC256V |  32 KB | 10.22 uA | 93.48 uA  |  -        |         |
| MB85RC512T |  64 KB |          |           |  4.0 uA   |         |
| MB85RC1MT  | 128 KB | 11.7 uA  | 46-721 uA |  3.6 uA   | See #17 |

_TODO: fill the table_


## FRAM_RINGBUFFER

Since version 0.4.2 a separate class **FRAM_RINGBUFFER** is added to this repo.
Its interface is straightforward and described in **FRAM_RINGBUFFER.md**.
The FRAM_ringbuffer.ino examples shows how the class can be used.


## FRAM_MULTILANGUAGE

Since version 0.5.2 the **FRAM_ML** class is added.
Its purpose is to store tables of strings in FRAM.
Its interface is described in **FRAM_MULTILANGUAGE.md**.

See examples.


## FRAM11 + FRAM9

- 0.5.0 added, see issue #28
- 0.5.3 redo FRAM9 and FRAM11, see #35

Experimental support for smaller FRAM's with 11 and 9 bits addresses.

- FRAM11 e.g. Cypress/Infineon 24CL16B (see #28)
- FRAM9 e.g. MB85RC04  (see #35)
Note **getSize()** will return 0 as it is only 0.5 KB and rounded down.
Use **getSizeBytes()** to get 512.


## Future

#### Must

- improve documentation
- test more types of FRAM 
  - FRAM11 / FRAM9
  - other people might help.


#### Should

- Improve **getSize()** to have **clear()** working properly. 
  - **MB85RC128A** only (hard code fall back?).
  - **getSize()** scanning FRAM like EEPROM library?
- investigate a faster strategy for **readUntil()**
  - search for separator per block (e.g. 16 bytes) read.
- Investigate **getManufacturerID()** and **getProductID()** for FRAM9/11.
  - need hardware + data sheets.


#### Could

- improve **FRAM32** that can write over the 64 KB border without problems.
  - Would need extra checking ==> overhead.
  - now it is responsibility of the user.
  - do we want/need this?
- **write()** and **writeBlock()** might write beyond the end of FRAM
  - now it is responsibility of the user.
  - range check would degrade performance
  - error flag ?
- extend examples
  - FRAM (8x) concatenated as one continuous memory.
    - a wrapper class?
- fill power usage table (documentation)
  - is in data sheet.
- refactor for readability
  - improve / add comments where needed.
  - memaddr ==> memoryAddress or memAddr (camelCase)
  - buf ==> buffer, 
  - buflen ==> bufferLength / bufferSize
  - obj ==> object 
  - use SDA/SCL as name


#### Wont

- extend current **clear()** with partial **clear(begin, end, value)**?
  - can be done by **writeBlock()** calls by user too
  - would need more complex end checking
  - ==> wont for now
- **dump(stream)** or printable interface?
  - Print interface? expensive in performance per char..
  - see example **FRAM_hexdump.ino**
- remember last written address? why?
- do we need a **write(memaddr, char \* buf)** for completeness?
  - it is just a wrapper

