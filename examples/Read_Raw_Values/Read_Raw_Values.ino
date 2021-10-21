/*
  Examples Sketch for MCP3304.h

  This example reads the voltage on CH0 through CH7 of a MCP3304 13bit ADC

  The circuit:
    CH0 through CH7 from Voltage Source  (best to use a rail-rail op amp w/ voltage divider(if needed))
    DGND and AGND to Ground
    VREF and VDD to +5V (stable 5v) (i used a tl431 to maintain consistant results from 12v)
    CS/SHDN - to digital (CS pin)
    DIN - to digital (TX pin)
    DOUT - to digital (RX pin)
    CLK - to digital  (SCK pin)
    MAX3377 - level shifter from 5V to 3.3V

  Thanks to walle86 for the SPI version of the libary and example portion for MCP3304
  Also thanks to the Arduino Reference for which this library is based on.
  written 9/3/2021

  by OuterGravity
*/
#include <MCP3304.h>
#define TX 15
#define RX 12
#define SCK 14
#define CS 13



int reading;
double voltage;

MCP3304 MCP(TX, RX, SCK, CS);  //create an instance using all the nessessary Pins

void setup()
{
  Serial.begin(115200);
}

void loop() {

  //quick listing of all raw results per channel
  Serial.print("All Raw Results:  ");
  Serial.print(MCP.raw_MCP3304(0));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(1));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(2));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(3));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(4));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(5));
  Serial.print("  ");
  Serial.print(MCP.raw_MCP3304(6));
  Serial.print("  ");
  Serial.println(MCP.raw_MCP3304(7));
  Serial.println();
  delay(1000);
  
  //readings converted to voltage based on an exact 5v reference, recommend measuring your exact vref from a good RMS multimeter
  reading = MCP.raw_MCP3304(0);   
  voltage = reading / 4096.0 * 5.0;    
  Serial.print("voltage CH0= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(1);      
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH1= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(2);  
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH2= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(3);   
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH3= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(4);      
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH4= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(5);   
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH5= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(6);   
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH6= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  reading = MCP.raw_MCP3304(7);   
  voltage = reading / 4096.0 * 5.0;
  Serial.print("voltage CH7= ");
  Serial.print(voltage, 2);
  Serial.println("V");
  Serial.println(" ");

  delay(1000);    
}
