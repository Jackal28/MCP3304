I created this file as a method to read the MCP3304 on the Raspberry Pico
as none of the SPI versions would compile correctly. With this library, the initial
pins are stated in the beginning instead of using a hardware SPI. It is based
off of the Arduino Reference MCP3208 example.