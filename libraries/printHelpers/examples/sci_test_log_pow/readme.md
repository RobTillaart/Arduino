
# test scientific() vs sci()

See test sketch.

### sci()
- hand crafted version to print scientific format of floats
- more tested

### scientific()
- uses log10 and pow to get exponent
- less tested

### accuracy

- Both work pretty well
- however sci() is slightly (last digit) more accurate (minimal tests)
- when printing -1E-35 sci() held the correct format -9.99E-36
  where scientific went -0.99E-35

### performance
UNO test

| function   | micros |  prints           |  value  |
|:----------:|:------:|-------------------|:-------:|
| sci        |  740   |  1.00000071E+37   |  1E37
| scientific |  768   |  1.00000584E+37   |  1E37
| sci        |  960   |  -9.99999904E-36  |  -1E-35
| scientific |  816   |  -0.99999694E-35  |  -1E-35
| sci        |  364   |  1.23450005E+4    |  12345.0
| scientific |  780   |  1.23450028E+4    |  12345.0


- scientific is pretty constant ~800 micros()
- sci() is 2x faster for small numbers and equal to 20% slower for large numbers.


### footprint

Simple test with UNO
sci()      => 2706 PROGMEM + 340 RAM (larger shared internal buffer in printHelpers)
scientific => 4052 PROGMEM + 300 RAM


## Conclusion

(for now)

sci() is equal or better on all fronts.


## Todo

- test on esp32
- test with double

