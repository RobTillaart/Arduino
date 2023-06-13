Based upon output of **ADS_performance.ino**
UNO 16 MHz.
IDE 1.8.19


Synchronous calls  I2C **100 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12861340        |  7.78  |
|  1         |   6481396        |  15.4  |
|  2         |   3347512        |  29.9  |
|  3         |   1724380        |  58.0  |
|  4         |    941032        |  106   |
|  5         |    549204        |  182   |
|  6         |    381340        |  262   |
|  7         |    269448        |  371   |


Synchronous calls  I2C **400 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12872804        |  7.77  |
|  1         |   6402848        |  15.6  |
|  2         |   3234156        |  30.9  |
|  3         |   1649272        |  60.6  |
|  4         |    862188        |  116   |
|  5         |    468652        |  213   |
|  6         |    271552        |  368   |
|  7         |    173412        |  577   |


Synchronous calls  I2C **600 KHz**

|  DataRate  |  Time 100 calls  |  SPS   |
|:----------:|:----------------:|:------:|
|  0         |  12736788        |  7.85  |
|  1         |   6390104        |  15.7  |
|  2         |   3223568        |  31.0  |
|  3         |   1645768        |  60.8  |
|  4         |    852300        |  117   |
|  5         |    448520        |  223   |
|  6         |    261216        |  383   |
|  7         |    167660        |  596   |

These are maxima of the SPS feasible, they do not include further processing.
At least this test shows the effect of the I2C bus speed.

