# PCA9635

Arduino library for PCA9635 I2C 8 bit PWM LED driver

# Description

This library is to control the I2C PCA9635 PWM extender.
The 16 channels are independently configurable is steps of 1/256.
this allows for better than 1% finetuning of the duty-cycle
of the PWM signal. 

### interface

**begin()** initializes the library after startup. Mandatory.

**begin(sda, scl)** idem, ESP32 ESP8266 only. Library does not support 
multiple Wire instances (yet).

**reset()** resets the library to start up conditions.
----

**setLedDriverMode(channel, mode)** mode is 0..3 See datasheet for full details.

| LED mode | Value | Description |
|:----|:----:|:----|
| PCA9635_LEDOFF     | 0x00 | led is 100% off, default @startup
| PCA9635_LEDON      | 0x01 | led is 100% on. 
| PCA9635_LEDPWM     | 0x02 | set LED in PWM mode, 0..255
| PCA9635_LEDGRPPWM  | 0x03 | add LED to the GRPPWM*

\* all leds in the group GRPPWM can be set to the same PWM value in one set.
This is ideal to trigger e.g. multiple LEDS (servo's) at same time.

**getLedDriverMode(channel)** returns the current mode of the channel.

----
**write1(channel, value)** writes a single 8 bit PWM value.

**write3(channel, R, G, B)** writes three consecutive PWM registers.

**writeN(channel, array, count)** write count consecutive PWM registers. 
May return **PCA9635_ERR_WRITE** if array has too many elements 
(including channel as offset)

**writeMode(reg, mode)** configuration of one of the two configuration registers.
check datasheet for details.

**readMode(reg)** reads back the configured mode, useful to add or remove a 
single flag (bit masking)

----

**setGroupPWM(uint8_t value)** sets all channels that are part of the PWM group to value.

**getGroupPWM()** get the current PWM setting of the group.

**setGroupFREQ(value)** see datasheet for details. 

**getGroupFREQ()** returns the freq of the PWM group.

**lastError()** returns **PCA9635_OK** if all is OK, and other error codes otherwise.

| Error code | Value | Description |
|:----|:----:|:----|
| PCA9635_OK        | 0x00 | Everything went well
| PCA9635_ERROR     | 0xFF | Generic error
| PCA9635_ERR_WRITE | 0xFE | Tries to write more elements than PWM channels
| PCA9635_ERR_CHAN  | 0xFD | Channel out of range
| PCA9635_ERR_MODE  | 0xFC | Invalid mode
| PCA9635_ERR_REG   | 0xFB | Invalid register
| PCA9635_ERR_I2C   | 0xFA | PCA9635 I2C communication error


# Operation

See examples
