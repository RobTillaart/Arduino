Based upon output of **ADS_performance.ino** (indicative).
UNO 16 MHz.
IDE 1.8.19

ADS1X15_LIB_VERSION: 0.4.4

Synchronous calls  I2C **100 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12931840        |  7.73  |
|  1         |   6481444        |  15.4  |
|  2         |   3347556        |  29.9  |
|  3         |   1724492        |  58.0  |
|  4         |    940984        |  106   |
|  5         |    549268        |  182   |
|  6         |    381328        |  262   |
|  7         |    269400        |  371   |


Synchronous calls  I2C **400 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12824560        |  7.80  |
|  1         |   6377516        |  15.7  |
|  2         |   3224972        |  31.0  |
|  3         |   1649100        |  60.6  |
|  4         |    862148        |  116   |
|  5         |    468488        |  213   |
|  6         |    271568        |  368   |
|  7         |    173424        |  577   |


Synchronous calls  I2C **600 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12816404        |  7.80  |
|  1         |   6374432        |  15.7  |
|  2         |   3216720        |  31.1  |
|  3         |   1630428        |  61.3  |
|  4         |    852332        |  117   |
|  5         |    448396        |  223   |
|  6         |    261288        |  383   |
|  7         |    165688        |  603   |

These are maxima of the SPS feasible, they do not include further processing.
At least this test shows the effect of the I2C bus speed.

