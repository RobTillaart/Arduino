# MultiMap

Arduino library for fast non-linear mapping or interpolation of values

## Description

In Arduino applications often the value of a sensor is mapped upon a more
usable value. E.g. the value of analogRead() is mapped onto 0 .. 5.0 Volt.
This is done by the map function which does a linear interpolation. This means
```
    output = C1 + input * C2
```
As C1 and C2 are to be calculated Arduino has the **map()** that calculates the 
two variables runtime from two given mappings.
```
    output = map(input, I1, I2, O1, O2):
```

In many cases when there is no linear mapping possible, as the 'points' are not on a single line,
one needs non-linear math to calculate the output. **Multimap()** just does that.

**Multimap()** needs two equal sized arrays of 'points', **input\[\]** and **output\[\]**, it looks up the 
input value in the input\[\] array and if needed it linear interpolates between two
points of the output\[\] array. 

The **input\[\]** array must have increasing values,
there is no such restriction for the **output\[\]** array.

**Multimap()** automatically constrains the output to the first and last 
value in the **output\[\]** array.

## Operation

See examples

Please note the fail example as this shows that in the intern math overflow can happen.

## TODO

Investigate class implementation for performance.
