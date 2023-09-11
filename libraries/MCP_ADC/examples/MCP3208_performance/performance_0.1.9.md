

# Performance test  

Test sketch  MCP3208_performance.ino

Max clock frequency tested 16 MHz, ESP32 WROVER Module

### Library version: 0.1.9

|  Action                       | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz  | HW 10 MHz | HW 12 MHz  | HW 14 MHz | HW 16 MHz | notes     |
|:------------------------------|---------:|---------:|---------:|----------:|----------:|-----------:|----------:|----------:|:----------|
| mcp28.analogRead()            |   397.0  |  243.0   |  188.0   |  158.00   |   153.0   |    209.0   |    208.0  |    147.0  |
| mcp28.analogReadMultiple()    |   271.0  |  154.0   |  99.00   |   70.00   |   64.00   |    61.00   |     59.0  |    55.00  |
| single / multiple ratio       |     1.0  |    1.0   |    1.0   |     2.0   |     2.0   |      3.0   |      3.0  |      2.0  |
|                               |          |          |          |           |           |            |           |           |
| mcp28.differentialRead()      |   359.0  |  241.0   |  186.0   |   157.0   |   151.0   |    148.0   |     146.0 |    142.0  |
| mcp28.deltaRead()             |   363.0  |  304.0   |  234.0   |   198.0   |   191.0   |    187.0   |     185.0 |    145.0  |

### Notes

For this test I used the ESP32 WROVER Module (ESP32-WROVER-IE-N16R8) with MCP3208-CI/SL (IC ADC 12BIT SAR 16SOIC)

A good compromise was the 12 MHz.
By running multiple tests I was able to see a difference in the reading value of 13-16 and it was easily fixed from the software side.
