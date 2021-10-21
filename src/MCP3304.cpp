//MIT License
//
//Copyright (c) [2021] [Brandon Blair]

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include "MCP3304.h"
#include <Arduino.h>


MCP3304::MCP3304(uint8_t TX, uint8_t RX, uint8_t SCK, uint8_t CS)
{
  pinMode(TX, OUTPUT);
  pinMode(RX, INPUT);
  pinMode(SCK, OUTPUT);
  pinMode(CS, OUTPUT);
  _TX = TX;
  _RX = RX;
  _SCK = SCK;
  _CS = CS;

}


int MCP3304::raw_MCP3304(int channel)
{
  int rawValue = 0;
  byte commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3) also the next MSB is configuration 1 for single, 0 for psuedo-differential (this start bit chooses single mode)

  //allow channel selection
  commandbits |= ((channel) << 3);

  digitalWrite(_CS, LOW); //Select and initialize adc

  for (int i = 7; i >= 3; i--) // setup bits to be written
  {
    digitalWrite(_TX, commandbits & 1 << i);
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_SCK, HIGH);   //ignores 2 null bits
  digitalWrite(_SCK, LOW);
  digitalWrite(_SCK, HIGH);
  digitalWrite(_SCK, LOW);

  //read bits from adc
  for (int i = 13; i >= 0; i--)
  {
    rawValue += digitalRead(_RX) << i;
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_CS, HIGH); //turn off device
  return rawValue;
}

double MCP3304::volt_MCP3304(int channel)
{
  int tempA = 0, rawValue = 0;
  double tempB = 0.00;
  byte commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3) also the next MSB is configuration 1 for single, 0 for psuedo-differential (this start bit chooses single mode)

  //allow channel selection
  commandbits |= ((channel) << 3);

  digitalWrite(_CS, LOW); //Select and initialize adc

  for (int i = 7; i >= 3; i--) // setup bits to be written
  {
    digitalWrite(_TX, commandbits & 1 << i);
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_SCK, HIGH);   //ignores 2 null bits
  digitalWrite(_SCK, LOW);
  digitalWrite(_SCK, HIGH);
  digitalWrite(_SCK, LOW);

  //read bits from adc
  for (int i = 13; i >= 0; i--)
  {
    rawValue += digitalRead(_RX) << i;
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_CS, HIGH); //turn off device
  //quick calculation to voltage
  tempA = rawValue * 5000;
  tempB = tempA / 4096;
  tempB /= 1000;
  return tempB;
}

double MCP3304::mV_MCP3304(int channel)
{
  int tempA = 0, rawValue = 0;
  double tempB = 0.00;
  byte commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3) also the next MSB is configuration 1 for single, 0 for psuedo-differential (this start bit chooses single mode)

  //allow channel selection
  commandbits |= ((channel) << 3);

  digitalWrite(_CS, LOW); //Select and initialize adc

  for (int i = 7; i >= 3; i--) // setup bits to be written
  {
    digitalWrite(_TX, commandbits & 1 << i);
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_SCK, HIGH);   //ignores 2 null bits
  digitalWrite(_SCK, LOW);
  digitalWrite(_SCK, HIGH);
  digitalWrite(_SCK, LOW);

  //read bits from adc
  for (int i = 13; i >= 0; i--)
  {
    rawValue += digitalRead(_RX) << i;
    //cycle clock
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);
  }
  digitalWrite(_CS, HIGH); //turn off device
  //quick calculation to voltage
  tempA = rawValue * 5000;
  tempB = tempA / 4096;
  
  return tempB;
}

double MCP3304::avg_MCP3304(int channel, int avgAmt, int delayTime)
{
	int tempA = 0, sumTemp = 0;
	double tempB = 0.00, tempC = 0.00;
	
  if (delayTime <= 1)
  {
    delayTime = 1;
  }
  if (delayTime >= 999)
  {
    delayTime = 999;
  }
  if (avgAmt <= 1)
  {
    avgAmt = 1;
  }
  if (avgAmt >= 1000)
  {
    avgAmt = 1000;
  }
  for (int i = 0; i < avgAmt; i++)
  {
    int rawValue = 0;
    
    byte commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3) also the next MSB is configuration 1 for single, 0 for psuedo-differential (this start bit chooses single mode)

    //allow channel selection
    commandbits |= ((channel) << 3);

    digitalWrite(_CS, LOW); //Select and initialize adc

    for (int i = 7; i >= 3; i--) // setup bits to be written
    {
      digitalWrite(_TX, commandbits & 1 << i);
      //cycle clock
      digitalWrite(_SCK, HIGH);
      digitalWrite(_SCK, LOW);
    }
    digitalWrite(_SCK, HIGH);   //ignores 2 null bits
    digitalWrite(_SCK, LOW);
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);

    //read bits from adc
    for (int i = 13; i >= 0; i--)
    {
      rawValue += digitalRead(_RX) << i;
      //cycle clock
      digitalWrite(_SCK, HIGH);
      digitalWrite(_SCK, LOW);
    }
    digitalWrite(_CS, HIGH); //turn off device
    //quick calculation to voltage
    sumTemp += rawValue;
    delayMicroseconds(delayTime);
  }

  tempA = sumTemp / avgAmt;
  tempB = tempA * 5000;
  tempC = tempB / 4096;
  tempC /= 1000;
  return tempC;
}

double MCP3304::mVAvg_MCP3304(int channel, int avgAmt, int delayTime)
{
	int tempA = 0, sumTemp = 0;
	double tempB = 0.00, tempC = 0.00;
	
  if (delayTime <= 1)
  {
    delayTime = 1;
  }
  if (delayTime >= 999)
  {
    delayTime = 999;
  }
  if (avgAmt <= 1)
  {
    avgAmt = 1;
  }
  if (avgAmt >= 1000)
  {
    avgAmt = 1000;
  }
  for (int i = 0; i < avgAmt; i++)
  {
    int rawValue = 0;
    
    byte commandbits = 0b11000000; //command bits - start, mode, chn (3), dont care (3) also the next MSB is configuration 1 for single, 0 for psuedo-differential (this start bit chooses single mode)

    //allow channel selection
    commandbits |= ((channel) << 3);

    digitalWrite(_CS, LOW); //Select and initialize adc

    for (int i = 7; i >= 3; i--) // setup bits to be written
    {
      digitalWrite(_TX, commandbits & 1 << i);
      //cycle clock
      digitalWrite(_SCK, HIGH);
      digitalWrite(_SCK, LOW);
    }
    digitalWrite(_SCK, HIGH);   //ignores 2 null bits
    digitalWrite(_SCK, LOW);
    digitalWrite(_SCK, HIGH);
    digitalWrite(_SCK, LOW);

    //read bits from adc
    for (int i = 13; i >= 0; i--)
    {
      rawValue += digitalRead(_RX) << i;
      //cycle clock
      digitalWrite(_SCK, HIGH);
      digitalWrite(_SCK, LOW);
    }
    digitalWrite(_CS, HIGH); //turn off device
    //quick calculation to voltage
    sumTemp += rawValue;
    delayMicroseconds(delayTime);
  }

  tempA = sumTemp / avgAmt;
  tempB = tempA * 5000;
  tempC = tempB / 4096;
  
  return tempC;
}