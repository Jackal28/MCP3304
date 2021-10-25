//
//    FILE: MCP3304.h
//  AUTHOR: Brandon Blair
// VERSION: 0.0.3
//    DATE: 2021-10-05
// PURPOSE: Arduino library initial intended for Universal Battery Charger
//     URL: https://github.com/Jackal28/MCP3304
//
//

#ifndef MCP3304_H
#define MCP3304_H
//always call arduino.h
#include <Arduino.h>


class MCP3304
{
public:
MCP3304(uint8_t TX, uint8_t RX, uint8_t SCK, uint8_t CS);

int raw_MCP3304(int channel);

double volt_MCP3304(int channel);

double avg_MCP3304(int channel, int avgAmt, int delayTime); //delayTime is in Microseconds 1-999, and avgAmt is between 1 - 1000

double mV_MCP3304(int channel); //returns mV instead of volts 

double mVAvg_MCP3304(int channel, int avgAmt, int delayTime);// for mV delayTime is in Microseconds 1-999, and avgAmt is between 1 - 1000

private:

int rawValue, tempA, sumTemp;
uint8_t _TX;  	
uint8_t	_RX;
uint8_t	_SCK;
uint8_t	_CS;
double tempB, tempC;
};

#endif