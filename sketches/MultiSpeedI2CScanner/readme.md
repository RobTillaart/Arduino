
MultiSpeedI2CScanner is a menu driven I2C scanner, see below.

# Arduino MultiSpeed I2C Scanner - 0.1.9

```
I2C ports: 1
        @ = toggle Wire - Wire1 - Wire2 [TEENSY 3.5 or Arduino Due]
Scanmode:
        s = single scan
        c = continuous scan - 1 second delay
        q = quit continuous scan
        d = toggle latency delay between successful tests. 0 - 5 ms
Output:
        p = toggle printAll - printFound.
        h = toggle header - noHeader.
        a = toggle address range, 0..127 - 8..120
Speeds:
        0 = 50 - 800 Khz  (warning - can block!!)
        1 = 100 KHz only
        2 = 200 KHz only
        4 = 400 KHz only
        8 = 800 KHz only  (warning - can block!)
        9 = 50 - 400 Khz  <<< DEFAULT >>>

        ? = help - this page
```

TODO: explain menu options in more detail


