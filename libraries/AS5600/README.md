
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

**Warning: experimental**

The sensor can measure a full rotation in 4096 steps.
The precision is therefore limited to 0.1°.
Noise levels unknown, but one might expect it to be effected by electric
and or magnetic signals in the environment.
Also unknown is the influence of metals near the sensor or an unstable 
or fluctuating power supply.


### I2C Address

The I2C address of the **AS5600** is always 0x36.

To use more than one **AS5600** on one I2C bus, see Multiplexing below.


### OUT pin

The sensor has an output pin named **OUT**.
This pin can be used for an analogue or PWM output signal.

See **Analogue Pin** and **PWM Pin** below.

Examples are added to show how to use this pin with **setOutputMode()**.


### PGO pin

Not tested.

PGO stands for Programming Option, it is used to calibrate / program the sensor.
As the sensor can be programmed only a few times one should
use this functionality with extreme care.
See datasheet for a detailed list of steps to be done.

See **Make configuration persistent** below.


## Hardware connection

The I2C address of the **AS5600** is always 0x36.

The AS5600 datasheet states it supports Fast-Mode == 400 KHz
and Fast-Mode-Plus == 1000 KHz. 

The sensor should connect the I2C lines SDA and SCL and the
VCC and GND to communicate with the processor.
The DIR (direction) pin of the sensor should be connected to:

- **GND** = fixed clockwise(\*)
- **VCC** = fixed counter clock wise
- a free IO pin of the processor = under library control.

In the latter setup the library can control the direction of 
counting by initializing this pin in **begin(directionPin)**, 
followed by **setDirection(direction)**. For the direction the 
library defines two constants named:

- **AS5600_CLOCK_WISE (0)**
- **AS5600_COUNTERCLOCK_WISE (1)**

(\*) if **begin()** is called without **directionPin** or with this 
parameter set to **255**, software direction control is enabled.

See Software Direction Control below for more information.


## Interface


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

- **AS5600(TwoWire \*wire = &Wire)** Constructor with optional Wire 
interface as parameter.
- **bool begin(uint8_t directionPin = 255)** set the value for the 
directionPin. 
If the pin is set to 255, the default value, there will be software 
direction control instead of hardware control.
See below.
- **bool begin(int sda, int scl, uint8_t directionPin = 255)** idem, 
for the ESP32 where one can choose the I2C pins.
If the pin is set to 255, the default value, there will be software 
direction control instead of hardware control.
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

- **bool setZPosition(uint16_t value)** set start position for limited range. Value = 0..4095.
Returns false if parameter is out of range.
- **uint16_t getZPosition()** get current start position.
- **bool setMPosition(uint16_t value)** set stop position for limited range. Value = 0..4095.
Returns false if parameter is out of range.
- **uint16_t getMPosition()** get current stop position.
- **bool setMaxAngle(uint16_t value)** set limited range.
Value = 0..4095.
Returns false if parameter is out of range.
See datasheet **Angle Programming**
- **uint16_t getMaxAngle()** get limited range.


- **bool setConfigure(uint16_t value)**
Value = 0..0x4000
Returns false if parameter is out of range.
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

The library has functions to address these fields directly.

- **bool setPowerMode(uint8_t powerMode)** 
returns false if parameter is out of range.
- **uint8_t getPowerMode()** returns the mode set.

See the .h file for the other get/set functions.


#### Hysteresis

- **bool setHysteresis(uint8_t hysteresis)** Suppresses "noise" on the output when the magnet is not moving.
In a way one is trading precision for stability.
returns false if parameter is out of range.


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

Normally one controls the direction of the sensor by connecting the DIR pin 
to one of the available IO pins of the processor. 
This IO pin is set in the library as parameter of the **begin(directionPin)** function.

The directionPin is default set to 255, which defines a software direction control.
To have this working one has to connect the DIR pin of the sensor to GND.
This puts the sensor in a hardware clock wise mode, so it is up to the library 
to do the additional math so the **readAngle()** and **rawAngle()** behave as 
if the DIR pin was connected to the processor IO pin.

The gain is that the user does not need an IO pin for this, 
which makes connecting the sensor a bit easier.

The user still calls **setDirection()** as before to change the direction.

TODO: measure performance impact.

TODO: investigate impact on functionality of other registers.


## Analogue OUT

(details datasheet - page 25)

The OUT pin can be configured with the function:

- **bool setOutputMode(uint8_t outputMode)**

When the analog OUT mode is set the OUT pin provides a voltage
which is linear with the angle. 

| VDD |  mode  | percentage | output    |  1° in V   |
|:---:|:------:|:----------:|:---------:|:----------:|
| 5V0 |   0    |  0 - 100%  | 0.0 - 5.0 | 0.01388889 |
| 5V0 |   1    |  10 - 90%  | 0.5 - 4.5 | 0.01111111 |
| 3V3 |   0    |  0 - 100%  | 0.0 - 3.3 | 0.00916667 |
| 3V3 |   1    |  10 - 90%  | 0.3 - 3.0 | 0.00750000 |

To measure these angles a 10 bit ADC or higher is needed.

When analog OUT is selected **readAngle()** will still return valid values.


## PWM OUT

(details datasheet - page 27)

The OUT pin can be configured with the function:

- **bool setOutputMode(uint8_t outputMode)** outputMode = 2 = PWM

When the PWM OUT mode is set the OUT pin provides a duty cycle which is linear 
with the angle. However they PWM has a lead in (HIGH) and a lead out (LOW).

The pulse width is 4351 units, 128 high, 4095 angle, 128 low.

|  Angle  |   HIGH  |  LOW   |  HIGH %  |  LOW %   |  Notes  |
|:-------:|:-------:|:------:|:--------:|:--------:|:--------|
|     0   |    128  |  4223  |   2,94%  |  97,06%  |
|    10   |    242  |  4109  |   5,56%  |  94,44%  |
|    20   |    356  |  3996  |   8,17%  |  91,83%  |
|    45   |    640  |  3711  |  14,71%  |  85,29%  |
|    90   |   1152  |  3199  |  26,47%  |  73,53%  |
|   135   |   1664  |  2687  |  38,24%  |  61,76%  |
|   180   |   2176  |  2176  |  50,00%  |  50,00%  |
|   225   |   2687  |  1664  |  61,76%  |  38,24%  |
|   270   |   3199  |  1152  |  73,53%  |  26,47%  |
|   315   |   3711  |   640  |  85,29%  |  14,71%  |
|   360   |   4223  |   128  |  97,06%  |   2,94%  | in fact 359.9 something as 360 == 0


#### Formula:

based upon the table above ```angle = map(dutyCycle, 2.94, 97.06, 0.0, 359.9);```

or in code ..
```cpp
t0 = micros();  // rising;
t1 = micros();  // falling;
t2 = micros();  // rising;  new t0

//  note that t2 - t0 should be a constant depending on frequency set.
//  however as there might be up to 5% variation it cannot be hard coded.
float dutyCycle = (1.0 * (t1 - t0)) / (t2 - t0);  
float angle     = (dutyCycle - 0.0294) * (359.9 / (0.9706 - 0.0294));

```


#### PWM frequency

The AS5600 allows one to set the PWM base frequency (~5%)
- **bool setPWMFrequency(uint8_t pwmFreq)**

| mode | pwmFreq | step in us | 1° in time |
|:----:|:-------:|:----------:|:----------:|
|   0  |  115 Hz |    2.123   |    24.15   |
|   1  |  230 Hz |    1.062   |    12.77   |
|   2  |  460 Hz |    0.531   |     6.39   |
|   3  |  920 Hz |    0.216   |     3.20   |

Note that at the higher frequencies the step size becomes smaller
and smaller and it becomes harder to measure.
You need a sub-micro second hardware timer to measure the pulse width 
with enough precision to get the max resolution.

When PWM OUT is selected **readAngle()** will still return valid values.


## Multiplexing

The I2C address of the **AS5600** is always 0x36.

To use more than one **AS5600** on one I2C bus, one needs an I2C multiplexer, 
e.g. https://github.com/RobTillaart/TCA9548.
Alternative could be the use of a AND port for the I2C clock line to prevent 
the sensor from listening to signals on the I2C bus. 

Finally the sensor has an analogue output **OUT**.
This output could be used to connect multiple sensors to different analogue ports of the processor.

**Warning**: If and how well this analog option works is not verified or tested.


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

#### med prio

- limit the **setOffset()** to -359.99 .. 359.99
- investigate **readMagnitude()**
  - combination of AGC and MD, ML and MH flags?
- investigate performance
  - basic performance per function
  - I2C improvements
  - software direction
- investigate OUT behavior in practice
  - analogue
  - PWM
- write examples:
  - as5600_calibration.ino (needs HW and lots of time)
  - different configuration options
- create **changeLog.md**

#### low prio

- add error handling
- investigate PGO programming pin.
- add mode parameter to offset functions.
  - see getAngularSpeed()


