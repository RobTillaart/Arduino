

# Performance test  

Test sketch  MCP23S17_performance.ino

Max clock frequency 10 MHz, for an UNO this is 8 MHz (divider of CPU clock)

### Library version: 0.2.2

|  Action                       |  SW SPI | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz | notes     |
|:------------------------------|--------:|---------:|---------:|---------:|---------:|:---------:|
| TEST digitalWrite(0, value)   |  676.75 |   67.00  |  48.75   |  39.75   |  35.25   |  Optimized!
| TEST digitalWrite(pin, value) |  678.00 |   68.25  |  50.00   |  41.25   |  36.50   |  Optimized!
| TEST digitalRead(pin)         |  452.00 |   45.00  |  32.50   |  27.25   |  23.75   |
|                               |         |          |          |          |          |
| TEST write8(port, mask)       |  450.00 |   44.00  |  32.00   |  26.00   |  24.00   |
| TEST read8(port)              |  450.00 |   44.00  |  32.00   |  26.00   |  24.00   |
| TEST write16(mask)            |  452.00 |   48.00  |  32.00   |  26.00   |  22.00   | since 0.1.1
| TEST read16()                 |  452.00 |   44.00  |  32.00   |  26.00   |  22.00   | since 0.1.1


### Notes

Performance as expected. 

0.2.2 has optimized digitalWrite(pin, value) when value is same as in IO register.


### Future

- test ESP32 and other platforms
- register based IO version for the SW SPI on AVR ?


