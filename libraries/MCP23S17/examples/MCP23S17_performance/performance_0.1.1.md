

# Performance test  

Test sketch  MCP23S17_performance.ino

Max clock frequency 10 MHz, for an UNO this is 8 MHz (divider of CPU clock)

### Library version: 0.1.1

|  Action                       |  SW SPI | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz | notes     |
|:------------------------------|--------:|---------:|---------:|---------:|---------:|:---------:|
| TEST digitalWrite(0, value)   |  892.25 |   87.75  |  64.00   |  52.25   |  46.25   |
| TEST digitalWrite(pin, value) |  893.75 |   89.75  |  65.25   |  53.00   |  47.50   |
| TEST digitalRead(pin)         |  447.75 |   44.75  |  32.75   |  26.75   |  24.25   |
|                               |         |          |          |          |          |
| TEST write8(port, mask)       |  446.00 |   44.00  |  32.00   |  26.00   |  22.00   |
| TEST read8(port)              |  446.00 |   44.00  |  32.00   |  26.00   |  22.00   |
| TEST write16(mask)            |  446.00 |   46.00  |  34.00   |  28.00   |  22.00   | since 0.1.1
| TEST read16()                 |  446.00 |   44.00  |  32.00   |  26.00   |  22.00   | since 0.1.1



### Notes

Performance as expected. 


### Future

- test ESP32 and other platforms
- register based IO version for the SW SPI on AVR ?


