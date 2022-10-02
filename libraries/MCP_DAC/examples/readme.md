

Note that some examples are ESP32 specific as they use e.g. VSPI() 

|  example                      |  UNO  | ESP32 | RP2040 |
|:-----------------------------:|:-----:|:-----:|:------:|
| MCP4911_test                  |   Y   |   Y   |    Y   |
| MCP4921_standalone            |   Y   |   Y   |    Y   |
| MCP4921_test                  |   Y   |   Y   |    Y   |
| MCP4921_VSPI                  |   N   |   Y   |    N   |
| MCP4921_wave_generator        |   Y   |   Y   |    Y   |
| MCP4921_wave_generator_ESP32  |   N   |   Y   |    N   |
| MCP4921_wave_generator_RP2040 |   N   |   N   |    Y   |

