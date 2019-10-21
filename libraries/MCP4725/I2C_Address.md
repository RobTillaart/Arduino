**MCP4725 ADDRESS NOTES**

The address of the MCP4725 in the demo sketches is set to 0x62 as that 
was the address of the sensor I had during writing. 
According to the datasheet the address has the following bit pattern: 

      011000FFU   (so 0x6?)

      ***F = Factory set bit***
      ***U = User configurable bit***

This means you can have at most 8 MCP4725 in one I2C bus (without multiplexing).
You have to specify the factory bits in your order, but not all shops might
provide all versions.

MCP4725A0T-E/CH:  0110 000U   0x60 - 0x61
MCP4725A1T-E/CH:  0110 001U   0x62 - 0x63
MCP4725A2T-E/CH:  0110 010U   0x64 - 0x65
MCP4725A3T-E/CH:  0110 011U   0x66 - 0x67
