
## Parallel control of multiple DS1804

It is easy to control N DS1804 with N+2 lines.
Design wise it is very much like the SPI bus.

- all share GND (including processor).
- all share U/D pin
- all share INC pin
- all have **unique CS** pins

Note that the DS1804's need a **separate** power source.


### Schema

```
              +----------+                           +----------+
              |      INC |-----------------------+---| INC      |
              |          |                       |   |          |
              |      U/D |--------------------+------| U/D      |
              |          |                    |  |   |          |
              |       CS |-----+  +------------------| CS       |
              |          |     |  |           |  |   |          |
              |  DS1804  |     |  |           |  |   |  DS1804  |
              +----------+     |  |           |  |   +----------+
                               |  |           |  |
                               |  |           |  |
              +----------+     |  |           |  |   +----------+
              |      INC |-----------------------+---| INC      |
              |          |     |  |           |  |   |          |
              |      U/D |--------------------+------| U/D      |
              |          |     |  |           |  |   |          |
              |       CS |--+  |  |  +---------------| CS       |
              |          |  |  |  |  |        |  |   |          |
              |  DS1804  |  |  |  |  |        |  |   |  DS1804  |
              +----------+  |  |  |  |        |  |   +----------+
                            |  |  |  |        |  |
                            |  |  |  |        |  |
                            |  |  |  |        |  |
                            |  |  |  |        |  |
              +-------------------------------------------------+
              |             0  1  2  3        u  i              |
              |                                                 |
              |                                                 |
              |                                                 |
              |                                                 |
              |                     processor                   |
              +-------------------------------------------------+

              Note common GND is not in the schema.
```


### Code

in the code
- select the Up or DOWN mode with pin u.
- select the device with pin 0, 1, 2, 3, .... n
- set a HIGH LOW pulse train on pin i to move the number of steps.


### Parallelism

It is possible to select multiple devices and give them a number of pulses so they go up/down in parallel.
- left and right channel in stereo.
- set all (or subset) to zero.
- more complex patterns to increase parallelism (performance) but this is more difficult coding wise.



