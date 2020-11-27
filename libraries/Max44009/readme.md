
# MAX44009 I2C LUX sensor

## Description
a.k.a. GY-49

The MAX44009 ambient light sensor is an I2C sensor, that has a 22 bit 
dynamic range from 0.045 lux to 188,000 lux.

## Examples

**Max44009\examples\max44009_test01**
- use for e.g. UNO (use voltage convertor!)

**Max44009\examples\max44009_test02**
- will **not** compile for UNO
- use for e.g. ESP32


## Schema breakout max44009 / GY-49

```

      +--------+
  VCC |o       |
  GND |o       |
  SCL |o      o| ADDRESS
  SDA |o      o| -INT
      +--------+

 ADDRESS:
 0 = 0x4A
 1 = 0x4B

 INT:
 Connect the INT pin to an pull up resistor
 0 = interrupt
 1 = no interrupt
 connect to an LED or an interrupt pin of an Arduino
```

## Notes
Please be aware this is a 3.3 Volt device so it should not be connected
to an Arduino or other 5 Volt device directly. Use a level convertor to 
solve this.

Do not forget to connect the address pin as you cannot read the sensor
in a reliable way. As the line will float it will sometimes have the
right address and sometimes not. (been there ;)
