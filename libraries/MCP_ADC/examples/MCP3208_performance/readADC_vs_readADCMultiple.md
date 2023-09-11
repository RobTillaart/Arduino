
### Comparing multiple **readADC()** calls with one **readADCMultiple()** call

- ESP32
- source https://github.com/RobTillaart/MCP_ADC/pull/11#issuecomment-1676461195
- figures are indicative and platform dependent.

|  function            |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |  <- channels  |
|:--------------------:|------:|------:|------:|------:|------:|------:|------:|------:|:-------------:|
|  analogRead          |       |   42  |   59  |   78  |   98  |  118  |  137  |  157  |  (us)
|  analogReadMultiple  |       |   27  |   34  |   41  |   49  |   55  |   62  |   70  |  (us)
|  ratio               |       |  1.56 |  1.73 |  1.90 |  2.00 |  2.15 |  2.21 |  2.24 |


TODO AVR UNO

