
[![Arduino CI](https://github.com/RobTillaart/AS5600/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/AS5600/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/AS5600/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/AS5600/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/AS5600/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AS5600/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AS5600.svg?maxAge=3600)](https://github.com/RobTillaart/AS5600/releases)


# AS5600

Arduino library for AS5600 magnetic rotation meter.


## Description

### AS5600

**AS5600** is a library for an AS5600 based magnetic rotation meter.

**Warning: experimental - not tested**

The sensor can measure a full rotation in 4096 steps.
The precision is therefore limited to 0.1°.
Noise levels unknown, but one might expect it to be effected by electric
and or magnetic signals in the environment.
Also unknown is the influence of metals near the sensor or an unstable or fluctuating power supply.

TODO: buy hardware to test the library and get hands on experience with the sensor.


### I2C Address

The I2C address of the **AS5600** is always 0x36.
To use more than one **AS5600** on one I2C bus, see Multiplexing below.


### OUT pin

The sensor has an output pin named **OUT**.
This pin can be used for an analogue or PWM output signal. 
Examples are added to show how to use this pin with **setOutputMode()**.


### PGO pin

Not tested.

PGO stand for Programming Option, it is used to calibrate / program the sensor.
As the sensor can be programmed only a few times one should
use this functionality with extreme care.
See datasheet for a detailed list of steps to be done.

See also **Make configuration persistent** below.


## Hardware connection

The sensor should connect the I2C lines SDA and SCL and the
VCC and GND to communicate with the processor.
The DIR (direction) pin of the sensor should be connected to:
- **GND** = fixed clockwise(\*)
- **VCC** = fixed counter clock wise
- a free IO pin of the processor = library control.

In the latter setup the library can control the direction of counting by initializing this pin in **begin(directionPin)**, followed by **setDirection(direction)**. For the direction the library defines two constants named:
- **AS5600_CLOCK_WISE (0)**
- **AS5600_COUNTERCLOCK_WISE (1)**

(\*) if **begin()** is called without **directionPin** or with this parameter set to **255**, software direction control is enabled.
See below for more information.


## Interface

The I2C address of the **AS5600** is always 0x36.


### Constants

Most important are:

```cpp
//  setDirection
const uint8_t AS5600_CLOCK_WISE         = 0;  //  LOW
const uint8_t AS5600_COUNTERCLOCK_WISE  = 1;  //  HIGH

//  0.087890625;
const float   AS5600_RAW_TO_DEGREES     = 360.0 / 4096;
//  0.00153398078788564122971808758949;
const float   AS5600_RAW_TO_RADIANS     = PI * 2.0 / 4096;

//  getAngularSpeed
const uint8_t AS5600_MODE_DEGREES       = 0;
const uint8_t AS5600_MODE_RADIANS       = 1;
```

See AS5600.h file (and datasheet) for all constants.
Also Configuration bits below for configuration related ones.


### Constructor + I2C

- **AS5600(TwoWire \*wire = &Wire)** Constructor with optional Wire interface as parameter.
- **bool begin(uint8_t directionPin = 255)** set the value for the directionPin. 
If the pin is set to 255, the default value, there will be software direction control instead of hardware control.
See below.
- **bool begin(int sda, int scl, uint8_t directionPin = 255)** idem, for the ESP32 where one can choose the I2C pins.
If the pin is set to 255, the default value, there will be software direction control instead of hardware control.
See below.
- **bool isConnected()** checks if the address 0x36 is on the I2C bus.
- **uint8_t getAddress()** returns the fixed device address 0x36. 


### Direction

To define in which way the sensor counts up.

- **void setDirection(uint8_t direction = AS5600_CLOCK_WISE)** idem.
- **uint8_t getDirection()** returns AS5600_CLOCK_WISE (0) or
AS5600_COUNTERCLOCK_WISE (1).


### Configuration registers

Please read the datasheet for details.

- **void setZPosition(uint16_t value)** set start position for limited range.
- **uint16_t getZPosition()** get current start position.
- **void setMPosition(uint16_t value)** set stop position for limited range.
- **uint16_t getMPosition()** get current stop position.
- **void setMaxAngle(uint16_t value)** set limited range.
See datasheet **Angle Programming**
- **uint16_t getMaxAngle()** get limited range.


- **void setConfigure(uint16_t value)**
- **uint16_t getConfigure()**


#### Configuration bits

Please read datasheet for details.

| Bit   | short | Description   | Values                                                | 
|:-----:|:------|:-------------:|:------------------------------------------------------|
| 0-1   |  PM   | Power mode    | 00 = NOM, 01 = LPM1, 10 = LPM2, 11 = LPM3             |
| 2-3   |  HYST | Hysteresis    | 00 = OFF, 01 = 1 LSB, 10 = 2 LSB, 11 = 3 LSB          |
| 4-5   |  OUTS | Output Stage  | 00 = analog (0-100%), 01 = analog (10-90%), 10 = PWM  |
| 6-7   |  PWMF | PWM frequency | 00 = 115, 01 = 230, 10 = 460, 11 = 920 (Hz)           |
| 8-9   |  SF   | Slow Filter   | 00 = 16x, 01 = 8x, 10 = 4x, 11 = 2x                   |
| 10-12 |  FTH  | Fast Filter   | Threshold 000 - 111 check datasheet                   |
| 13    |  WD   | Watch Dog     | 0 = OFF, 1 = ON                                       |
| 15-14 |       | not used      |


### Read Angle

- **uint16_t rawAngle()** idem. returns 0 .. 4095. (12 bits) 
Conversion factor AS5600_RAW_TO_DEGREES = 360 / 4096 = 0.087890625 
or use AS5600_RAW_TO_RADIANS if needed. 
- **uint16_t readAngle()** read the angle from the sensor. 
This is the one most used.
- **void setOffset(float degrees)** sets an offset in degrees,
e.g. to calibrate the sensor after mounting.
Typical values are -359.99 - 359.99 probably smaller. 
Larger values will be mapped back to this interval.
Be aware that larger values will affect / decrease the precision of the measurements as floats have only 7 significant digits.
Verify this for your application.
- **float getOffset()** returns offset in degrees.

In #14 there is a discussion about **setOffset()**.
A possible implementation is to ignore all values outside the
-359.99 - 359.99 range.
This would help to keep the precision high.


### Angular Speed

- **float getAngularSpeed(uint8_t mode = AS5600_MODE_DEGREES)** is an experimental function that returns 
an approximation of the angular speed in rotations per second.
The function needs to be called at least **four** times per rotation
or once per second to get a reasonably precision. 

- mode == AS5600_MODE_RADIANS (1): radians /second
- mode == AS5600_MODE_DEGREES (0): degrees /second (default)
- mode other => degrees /second

Negative values indicate reverse rotation. 
What that means depends on the setup of your project.

Note: the first call will return an erroneous value as it has no
reference angle or time. 
Also if one stops calling this function 
for some time the first call after such delays will be incorrect.

Note: the frequency of calling this function of the sensor depends on the application. 
The faster the magnet rotates, the faster it may be called.
Also if one wants to detect minute movements, calling it more often is the way to go.


### Status registers

- **uint8_t readStatus()** see Status bits below.
- **uint8_t readAGC()** returns the Automatic Gain Control.
0..255 in 5V mode, 0..128 in 3V3 mode.
- **uint16_t readMagnitude()** reads the current internal magnitude.
(page 9 datasheet)
Scale is unclear, can be used as relative scale.
- **bool detectMagnet()** returns true if device sees a magnet.


#### Status bits

Please read datasheet for details.

| Bit   | short | Description   | Values                | 
|:-----:|:------|:-------------:|:----------------------|
| 0-2   |       | not used      |                       |
| 3     |  MH   | overflow      | 1 = magnet too strong |
| 4     |  ML   | overflow      | 1 = magnet too weak   |
| 5     |  MD   | magnet detect | 1 = magnet detected   |
| 6-7   |       | not used      |                       |


### Make configuration persistent.

**USE AT OWN RISK**

Please read datasheet twice.

The burn functions are used to make settings persistent. 
As these functions can only be called one or three times, 
they are highly permanent, therefore they are commented in the library.

The risk is that you make your as5600 **USELESS**.

**USE AT OWN RISK**

- **uint8_t getZMCO()** reads back how many times the ZPOS and MPOS 
registers are written to permanent memory. 
You can only burn a new Angle 3 times to the AS5600.
- **void burnAngle()** writes the ZPOS and MPOS registers to permanent memory. 
You can only burn a new Angle maximum **THREE** times to the AS5600.
- **void burnSetting()** writes the MANG register to permanent memory. 
You can write this only **ONE** time to the AS5600.


## Software Direction Control

Experimental 0.2.0

Normally one controls the direction of the sensor by connecting the DIR pin to one of the available IO pins of the processor. This IO pin is set in the library as parameter of the **begin(directionPin)** function.

The directionPin is default set to 255, which defines a software direction control.
To have this working one has to connect the DIR pin of the sensor to GND.
This puts the sensor in a hardware clock wise mode, so it is up to the library to do the additional math so the **readAngle()** and **rawAngle()** behave as if the DIR pin was connected to the processor IO pin.

The gain is that the user does not need an IO pin for this, which makes connecting the sensor a bit easier.

In terms of the interface, the user call **setDirection()** as before to change the direction.

TODO: measure performance impact.

TODO: investigate impact on functionality of other registers.


## Multiplexing

The I2C address of the **AS5600** is always 0x36.

To use more than one **AS5600** on one I2C bus, one needs an I2C multiplexer, 
e.g. https://github.com/RobTillaart/TCA9548.
Alternative could be the use of a AND port for the I2C clock line to prevent 
the sensor from listening to signals on the I2C bus. 

Finally the sensor has an analogue output **OUT**.
This output could be used to connect multiple sensors to different analogue ports of the processor.

**Warning**: If and how well this analog option works is not verified or tested. (TODO)


## Operational

The base functions are:

```cpp
AS5600 as5600;

void setup()
{
  Serial.begin(115200);
  ...
  as5900.begin(4);     //  set the direction pin
  as5600.setDirection(AS5600_CLOCK_WISE);
  ...
}

void loop()
{
...
  Serial.println(as5600.readAngle());
  delay(1000);
...
}
```

See examples.


## Future

Some ideas are kept here so they won't get lost.
priority is relative


#### high prio

- get hardware to test.
- improve documentation.
- investigate OUT output pin.
  - PWM, analog_90 and analog_100

#### med prio

- investigate **readMagnitude()**
  - combination of AGC and MD, ML and MH flags?
- investigate performance
  - basic performance per function
  - I2C improvements
  - software direction
- write examples:
  - as5600_calibration.ino (needs HW and lots of time)
  - different configuration options
- create **changeLog.md**

#### low prio

- add error handling
- investigate PGO programming pin.
- add mode parameter to offset functions.
  - see getAngularSpeed()


