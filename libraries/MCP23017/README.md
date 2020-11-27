# MCP23017_RT

Arduino library for I2C MCP23017 16 channel port expander

## Description

Short discription of the interface

* **MCP23017(address)**         constructor
* **begin()**
* **begin(sda, scl)**           for ESP32

single pin interface
* **pinMode(pin, value)**       pin = 0..16  value = INPUT,OUTPUT
* **digitalWrite(pin, value)**  pin = 0..16  value = LOW(0) HIGH (!0)
* **digitalRead(pin)**          pin = 0..16

8 pins interface
* **pinMode8(port, value)**     port = 0, 1  value = 
* **write8(port, value)**       port = 0, 1  value =
* **read8(port)**               port = 0, 1

## Operation

See examples

