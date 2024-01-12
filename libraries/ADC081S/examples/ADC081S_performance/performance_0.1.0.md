

## Performance test  

Test sketch:  ADC081S_performance.ino


### Library version: 0.1.0

There is only a transfer of 2 bytes. Times in microseconds.


|  device    |  Test        | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz  | HW 10 MHz | HW 12 MHz | HW 14 MHz | HW 16 MHz |
|:-----------|:-------------|:--------:|:--------:|:--------:|:---------:|:---------:|:---------:|:---------:|:---------:|
|  UNO       |  adc.read()  |   33.6   |   25.6   |   21.6   |   19.6    |     -     |     -     |     -     |     -     |
|  ESP32     |  adc.read()  |   25.4   |   16.7   |   12.2   |   10.0    |    9.6    |    9.4    |    9.2    |    8.9    |



|  device  |  Test        | SW max speed  |  notes  |
|:---------|:-------------|--------------:|:--------|
|  UNO     |  adc.read()  |    238.2      |  UNO has relative slow digital IO
|  ESP32   |  adc.read()  |      6.9      |  faster than HW SPI as it has no transfer overhead.



### Notes


