# AnalogPin
Arduino library to add functionality on top of analogRead()

## Description
AnalogPin is an Arduino class that adds noise filtering and smoothing
to analogRead().
Furthermore it can speed up the analogRead() function by tuning the prescaler.
This latter is AVR only.

## Operation

**readLast()** returns the last read value without reading a new one.

**get/setPrescaler(prescale)** can be used to speed up analogRead().

The effect is that both the accuracy and precission are affected.
You should verify if this is acceptable for your project.
***Works only for AVR based boards***


**get/setNoiseThreshold(noise)** is used to set the noise threshold to be used by 
the **read()** function.

**read(twice)** implements an **analogRead()** that supresses small noise fluctuations.
The parameter twice is used to force analogRead() to be executed twice to reduce noise 
from the multiplexing.

Example: if the previous read has the value 300 and you
want to interpret all subsequent readings between 290
and 310 as 300 (the same) your code should look like:
```
    AP.setNoiseThreshold(10);
    AP.read();
```

**get/setSmoothWeight(alpha)** is used to set the weight factor for the **readSmoothed()** function.

The weight of the previous read is **alpha/32**.
A higher alpha will dampen the signal more, a lower alpha
will follow the actual signal better.
This can be used to suppress noise too.

```
    AP.setSmoothWeight(4);   // weight = 4/32 = 1/8 = 12.5%
    AP.readSmoothed();
```

**readSmoothed()** implements an analogRead with a running average build in.

Two functions that expose information that might sometimes be useful.
**readPrevious()** returns the previous value read.

**readLast()** returns the last value read.

