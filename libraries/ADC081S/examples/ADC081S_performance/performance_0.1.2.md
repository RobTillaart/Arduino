

## Performance test  

Test sketch:  ADC081S_performance.ino


### Library version: 0.1.0

There is only a transfer of 2 bytes. Times in microseconds.
- UNO = 16 MHz
- ESP32 = 240 MHz


|  device  |  Test        | SW max speed  |  notes  |
|:---------|:-------------|--------------:|:--------|
|  UNO     |  adc.read()  |    238.2      |  UNO has relative slow digital IO
|  ESP32   |  adc.read()  |      6.9      |  faster than HW SPI as it has no transfer overhead.


ns = not supported.

|  SPI MHz  |  UNO adc.read()  |  ESP32 adc.read()  |  Notes  |
|:---------:|:----------------:|:------------------:|:-------:|
|     1     |      33.6        |        25.4        |
|     2     |      25.6        |        16.7        |
|     4     |      21.6        |        12.2        |
|     8     |      19.6        |        10.0        |
|     10    |       ns         |         9.6        |
|     12    |       ns         |         9.4        |
|     16    |       ns         |         8.9        |
|     32    |       ns         |         8.6        |
|     64    |       ns         |         8.3        |


### Notes


