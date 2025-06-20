
## Cascading Potentiometers

Some notes on cascading potentiometers to have a large range with higher precision.

Based upon - https://github.com/RobTillaart/AD524X/issues/26



### Cascaded voltage divider

Basic cascade to vary voltage connects:

- all B's to GND
- A of top level to 5V (or 3V3 whatever)
- wiper W  of one level to the A of next leve;
- last wiper W is final output


```
  5V ----A[  1000 K  ]B-----  GND
              W
              |
    +---------+  V1
    |
    +----A[   100 K  ]B-----  GND
              W
              |
    +---------+  V2
    |
    +----A[   10 K   ]B-----  GND
              W
              |
              |
              o  256 steps between GND and V2

```

Some math for a two potentiometer system see **cascading_voltage_divider.ino** example.


### Range voltage divider

The following setup has two potmeters, left and right, to define a range.
- X can be set between 0.0 and 5.0 Volt and 
- Y can be set between 0.0 and 5.0 volt.

The third range potentiometer has 256 positions within the defined range range.
E.g if left is set to 2.3 Volt and right is set to 2.5 Volt, 
the range potentiometer divides this 0.2 volt in 256 steps of about a single millivolt (in theory).


```
         left limit pot           right limit pot

  GND ----A[  100K  ]B----  5V  ----A[  100K  ]B---- GND
               W                         W
               |                         |
               |        range pot        |
               |                         |
             X +------A[  100 K  ]B------+ Y
                           W
                           |
                           |
                           o   voltage between (0..Vcc)

```


### Cascaded resistor

No dangling connectors give less noise as even a bad wiper will not break 
the resistance chain completely. (Preferred imho)


```
     ----A[  1000K  ]B----+----A[  100 K  ]B----+----A[  10 K  ]B----+---o
               W          |         W           |         W          |
               |          |         |           |         |          |
               +----------+         +-----------+         +----------+
```


Connected the AD524X as rheostats, saves a few connnections.

```
     ----A[  1000K  ]B    +----A[  100 K  ]B    +----A[  10 K  ]B    +---o
               W          |         W           |         W          |
               |          |         |           |         |          |
               +----------+         +-----------+         +----------+
```

Some math for a two potentiometer system see **cascading_potentiometers.ino** example.


### Zero switch

An additional option is to connect the first A with the last B with "zero" switch to get 0 Ohm.
This would solve the Wiper Resistance which is 60- 120 Ohm for the AD5422 (datasheet P3).
Note with three wipers in a cascade the Wiper Resistance adds up to 200-360 Ohm,
Optionally you can place a zero switch over every potentiometer.
Drawback is extra components, control lines and code.

```
                            "zero" switch
      +--------------------------o \o--------------------------------+
      |                                                              |
      |                                                              |
     -+--A[  1000K  ]B    +----A[  100 K  ]B    +----A[  10 K  ]B    +---o
               W          |         W           |         W          |
               |          |         |           |         |          |
               +----------+         +-----------+         +----------+
```

### 

