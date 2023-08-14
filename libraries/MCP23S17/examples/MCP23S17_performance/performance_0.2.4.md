

# Performance test  

Test sketch  MCP23S17_performance.ino

Max clock frequency 10 MHz, ESP32 WROVER Module

### Library version: 0.2.4

|  Action                       |  SW SPI | HW 1 MHz | HW 2 MHz | HW 4 MHz | HW 8 MHz | HW 10 MHz | notes     |
|:------------------------------|--------:|---------:|---------:|---------:|---------:|:---------:|:---------:|
| TEST digitalWrite(0, value)   |  48.560 |   85.12  |  57.00   |  43.69   |  36.81   |   35.38   |
| TEST digitalWrite(pin, value) |  47.750 |   84.50  |  41.94   |  42.69   |  26.62   |   25.62   |
| TEST digitalRead(pin)         |  31.940 |   43.75  |  29.31   |  22.37   |  18.75   |   18.06   |
|                               |         |          |          |          |          |           |
| TEST write8(port, mask)       |  34.000 |   45.00  |  30.50   |  23.50   |  20.00   |   19.50   |
| TEST read8(port)              |  34.500 |   46.00  |  31.50   |  24.50   |  21.00   |   20.50   |
| TEST write16(mask)            |  32.500 |   44.00  |  29.50   |  22.50   |  19.00   |   18.00   | since 0.1.1
| TEST read16()                 |  33.000 |   43.50  |  29.00   |  22.00   |  19.00   |   18.50   | since 0.1.1

### Notes

For this test I used the ESP32 WROVER Module (ESP32-WROVER-IE-N16R8), ESP32-DEVKITS-R and MCP23S17T-E/ML (28QFN)
Software SPI : D2, D4 and D5

See: https://github.com/RobTillaart/MCP23S17/pull/22

