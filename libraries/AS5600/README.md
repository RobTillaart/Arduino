
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

Not tested.

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
- GND = fixed clockwise
- VCC = fixed counter clock wise
- a free IO pin of the processor = library control.

In the latter setup the library can control the direction of counting by initializing this pin in **begin(pin)**, followed by **setDirection(direction)**. For the direction the library defines two constants named:
- **AS5600_CLOCK_WISE (0)**
- **AS5600_COUNTERCLOCK_WISE (1)**


## Interface

The I2C address of the **AS5600** is always 0x36.


### Constants

**NOT** to be adjusted.

```cpp
//  setDirection
const uint8_t AS5600_CLOCK_WISE         = 0;  //  LOW
const uint8_t AS5600_COUNTERCLOCK_WISE  = 1;  //  HIGH

const float   AS5600_RAW_TO_DEGREES     = 360.0 / 4095.0;   //  0.0879120879120879121;
const float   AS5600_RAW_TO_RADIANS     = 2 * PI / 4095.0;  //  0.00153435538636864138630654133494;

//  getAngularSpeed
const uint8_t AS5600_MODE_DEGREES       = 0;
const uint8_t AS5600_MODE_RADIANS       = 1;

//  setOutputMode
const uint8_t AS5600_OUTMODE_ANALOG_100 = 0;
const uint8_t AS5600_OUTMODE_ANALOG_90  = 1;
const uint8_t AS5600_OUTMODE_PWM        = 2;

//  setPowerMode
const uint8_t AS5600_POWERMODE_NOMINAL  = 0;
const uint8_t AS5600_POWERMODE_LOW1     = 1;
const uint8_t AS5600_POWERMODE_LOW2     = 2;
const uint8_t AS5600_POWERMODE_LOW3     = 3;

//  setPWMFrequency
const uint8_t AS5600_PWM_115            = 0;
const uint8_t AS5600_PWM_230            = 1;
const uint8_t AS5600_PWM_460            = 2;
const uint8_t AS5600_PWM_920            = 3;

//  setWatchDog
const uint8_t AS5600_WATCHDOG_OFF       = 0;
const uint8_t AS5600_WATCHDOG_ON        = 1;
```


### Constructor + I2C

- **AS5600(TwoWire \*wire = &Wire)** Constructor with optional Wire interface as parameter.
- **bool begin(uint8_t directionPin = AS5600_CLOCK_WISE)** set the value for the directionPin.
- **bool begin(int sda, int scl, uint8_t directionPin = AS5600_CLOCK_WISE)** idem, for the ESP32 where one can choose the I2C pins.
- **bool isConnected()** checks if the fixed address 0x36 is on the I2C bus.
- **uint8_t getAddress()** returns the device address. 


### Direction

To define in which way the sensor counts up.

- **void setDirection(uint8_t direction = AS5600_CLOCK_WISE)**
- **uint8_t getDirection()**


### Configuration registers

Please read datasheet for details.

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

- **uint16_t rawAngle()** idem. returns 0 .. 4095. 
Conversion factor to degrees = 360 / 4095 = 0.0879121  
- **uint16_t readAngle()** read the angle from the sensor. 
This is the one most used.


### Angular Speed

- **getAngularSpeed(uint8_t mode = AS5600_MODE_DEGREES)** is an experimental function that returns 
an approximation of the angular speed in rotations per second.
The function needs to be called at least **four** times per rotation
to get a reasonably accuracy. 

(0.1.3 added mode parameter).
- mode == AS5600_MODE_RADIANS (1): radians /second
- mode == AS5600_MODE_DEGREES (0): degrees /second (default)
- mode other => degrees /second

Negative values indicate reverse rotation. 
What that means depends on the setup of your project.

Note: the first call will return an erroneous value as it has no
reference angle or time. Also if one stops calling this function 
for some time the first call after such delays will be incorrect.


### Status registers

- **uint8_t readStatus()** see below.
- **uint8_t readAGC()** returns the Automatic Gain Control.
0..255 in 5V mode, 0..128 in 3V3 mode.
- **uint16_t readMagnitude()** reads the current internal magnitude.
Meaning or scale is unclear. 
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


## Multiplexing

The I2C address of the **AS5600** is always 0x36.

To use more than one **AS5600** on one I2C bus, one needs an I2C multiplexer, 
e.g. https://github.com/RobTillaart/TCA9548.
Alternative could be the use of a AND port for the I2C clock line to prevent 
the sensor from listening to signals on the I2C bus. 

Finally the sensor has an analogue output **OUT**.
This output could be used to connect multiple sensors to different analog ports of the processor.

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


### high prio

- get hardware to test.
- improve documentation
- investigate PGO programming pin.
- investigate OUT output pin.
  - PWM, analog_90 and analog_100
- write examples
  - as5600_calibration.ino ?
- add constants for remaining configure functions
  - hysteresis, fast / slow filter
- investigate **magnetStrength()**  
  - combination of AGC and MD, ML and MH flags?


### low prio

- unit test
- error handling?
- test I2C speeds.


