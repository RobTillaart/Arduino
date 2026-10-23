

Disclaimer: This is an indicative table.
Read datasheet of devices for details.


## Comparison table LTCxxxx Coulomb sensors

Comparison of LTCxxxx Battery charge and discharge (Coulomb) meters.


|                           |  2941  |  2942  |  2943  |  2944  |  4150  |
|:--------------------------|:------:|:------:|:------:|:------:|:------:|
|  library                  |    Y   |    Y   |    Y   |    Y   |    N   |
|  bits                     |    ?   |   14   |   14   |   14   |    -   |
|  Max Voltage              |    6V  |   6V   |   20V  |   60V  |   8V   |
|  Cells                    |    1   |   1    |   > 1  |   > 1  |    ?   |
|  Communication            |   I2C  |   I2C  |   I2C  |   I2C  | bit-IO |
|  Address                  |  0x64  |  0x64  |  0x64  |  0x64  |    -   |
|  Channels                 |    1   |    1   |    1   |    1   |    1   |
|                           |        |        |        |        |        |
|  setCharge                |    Y   |    Y   |    Y   |    Y   |    -   |
|  getCharge                |    Y   |    Y   |    Y   |    Y   |   IRQ  |
|  setChargeThresholdHigh   |    Y   |    Y   |    Y   |    Y   |    -   |
|  setChargeThresholdLow    |    Y   |    Y   |    Y   |    Y   |    -   |
|                           |        |        |        |        |        |
|  getVoltage               |    -   |    Y   |    Y   |    Y   |    -   |
|  setVoltageThresholdHigh  |    -   |    Y   |    Y   |    Y   |    -   |
|  setVoltageThresholdLow   |    -   |    Y   |    Y   |    Y   |    -   |
|                           |        |        |        |        |        |
|  getCurrent               |    -   |    -   |    Y   |    Y   |    -   |
|  setCurrentThresholdHigh  |    -   |    -   |    Y   |    Y   |    -   |
|  setCurrentThresholdLow   |    -   |    -   |    Y   |    Y   |    -   |
|                           |        |        |        |        |        |
|  getTemperature           |    -   |    Y   |    Y   |    Y   |    -   |
|  setTempThresholdHigh     |    -   |    Y   |    Y   |    Y   |    -   |
|  setTempThresholdLow      |    -   |    Y   |    Y   |    Y   |    -   |


The LTC2943 / LTC2944 has a superset of the LTC2941.

The LTC2942 has other register mapping.

The LTC4150 is a different type of device, mentioned for completeness.


## Other Charging devices

Devices that could be investigated in the future.
Some stand alone devices are quite simple e.g. LTC4058.


|  device     |  description  |
|:------------|:--------------|
|  LTC4000,   |  High Voltage High Current Controller for Battery Charging and Power Management
|  LTC4009,   |  High Efficiency, Multi-Chemistry Battery Charger
|  LTC4012    |  High Efficiency, Multi-Chemistry Battery Charger
|  LTC3652HV  |  Power Tracking 2A Battery Charger
|  LTC1732    |  Li-Ion Battery Charger
|             |
|  LTC1734    |  Lithium-Ion Battery Charger in ThinSOT™
|  LTC4002    |  Switch Mode Lithium-Ion Battery Charger
|  LTC4052    |  Monolithic Lithium-Ion Battery Pulse Charger
|  LTC4053    |  USB Compatible Monolithic Li-Ion Battery Charger
|  LTC4057    |  Lithium-Ion Linear Battery Charger
|  LTC4058    |  Stand alone 950mA Lithium-Ion Charger in DFN
|  LTC4059    |  900mA Linear Lithium-Ion Battery Charger
|  LTC4061    |  Stand alone Linear Li-Ion Battery Charger with Thermistor Input
|  LTC4063    |  Li-Ion Charger with Linear Regulator
|  LTC4080    |  500mA Stand alone Li-Ion Charger with Integrated 300mA Synchronous Buck
|  LTC4088    |  High Efficiency Battery Charger/USB Power Manager

Possibly there are more (source datasheets)


