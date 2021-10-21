/*
  Examples Sketch for MCP3304.h

  This example reads the voltage on CH0 and CH7 by an average amount of reads with a specified delay between each read in microseconds from a MCP3304 13bit ADC

  The circuit:
    CH0 through CH7 from Voltage Source  (best to use a rail-rail op amp w/ voltage divider(if needed))
    DGND and AGND to Ground
    VREF and VDD to +5V (stable 5v) (i used a tl431 to maintain consistant results from 12v)
    CS/SHDN - to digital (CS pin)
    DIN - to digital (TX pin)
    DOUT - to digital (RX pin)
    CLK - to digital  (SCK pin)
    MAX3377 - level shifter from 5V to 3.3V

  Thanks to the Arduino Reference for which this library is based on.
  written 10/20/2021

  by OuterGravity
*/
#include <MCP3304.h>
#define TX 15
#define RX 12
#define SCK 14
#define CS 13

const int avgAmt = 100, delayTime = 100; //100 cycles with a delay between each of 100 microseconds
int channel;

MCP3304 MCP(TX, RX, SCK, CS);  //create an instance using all the nessessary Pins

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  //quick listing of all raw results per channel
  Serial.println("All Voltage Results:  ");
  Serial.println();
  
  Serial.print("Channel 0: ");
  channel = 0;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 1: ");
  channel = 1;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 2: ");
  channel = 2;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 3: ");
  channel = 3;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 4: ");
  channel = 4;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 5: ");
  channel = 5;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 6: ");
  channel = 6;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");

  Serial.print("Channel 7: ");
  channel = 7;
  Serial.print(MCP.mVAvg_MCP3304(channel, avgAmt, delayTime));
  Serial.println("mV");
  
  Serial.println();
  Serial.println();
  delay(1000);
}
