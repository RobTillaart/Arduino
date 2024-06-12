

# Performance test  

Test sketch  MCP23S17_performance.ino

Max clock frequency 8 MHz, Arduino UNO, IDE 1.8.19

### Library version: 0.5.3

|  Action                       |  SW SPI | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz | HW 10 MHz | notes     |
|:------------------------------|--------:|---------:|---------:|---------:|---------:|:---------:|:---------:|
| TEST digitalWrite(0, value)   |  677.25 |   65.75  |  48.25   |  39.25   |  34.25   |    n.a.   |
| TEST digitalWrite(pin, value) |  678.75 |   67.25  |  49.50   |  40.25   |  35.25   |    n.a.   |
| TEST digitalRead(pin)         |  452.00 |   44.50  |  32.00   |  26.25   |  23.50   |    n.a.   |
|                               |         |          |          |          |          |           |
| TEST write8(port, mask)       |  450.00 |   44.00  |  32.00   |  26.00   |  24.00   |    n.a.   |
| TEST read8(port)              |  452.00 |   46.00  |  30.00   |  24.00   |  24.00   |    n.a.   |
| TEST write16(mask)            |  300.00 |   26.00  |  18.00   |  16.00   |  14.00   |    n.a.   | since 0.1.1
| TEST read16()                 |  298.00 |   28.00  |  18.00   |  16.00   |  14.00   |    n.a.   | since 0.1.1


### Notes

