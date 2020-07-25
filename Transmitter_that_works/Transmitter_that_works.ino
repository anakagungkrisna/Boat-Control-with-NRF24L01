/* Transmit POT value through NRF24L01 using Arduino
*
* Pin Conections
* CE - 7
MISO-12
MOSI-11
SCK-13
CS-8
POT-A7
*/
#include <SPI.h>
#include "RF24.h"
RF24 myRadio (7, 8);

struct package {
  int msg = 0;
};

byte addresses [] [6] = {"0"};

typedef struct package Package;
  Package data;
  
void setup ()
{
Serial.begin (9600);
myRadio.begin ();
myRadio.setChannel (115); // 115 band above WIFI signals
myRadio.setPALevel (RF24_PA_MIN); // MIN power low rage
myRadio.setDataRate (RF24_250KBPS); // Minimum speed
delay (500);
Serial.print ("Setup Initialized");
}
void loop ()
{
int Read_ADC = analogRead (A0);
int servo_value = map (Read_ADC, 0, 1024, 0,180);
//if (servo_value> 1)
data.msg = servo_value;
WriteData ();
delay (50);
// ReadData ();
// delay (200);
}
void WriteData ()
{
myRadio.stopListening (); // Stop Receiving and start transminitng
myRadio.openWritingPipe (0xF0F0F0F0AA); // Sends data on this 40-bit address
myRadio.write (& data, sizeof (data));
Serial.print ("\ nSent:");
Serial.println (data.msg);
//delay (300);
}
void ReadData ()
{
myRadio.openReadingPipe (1, 0xF0F0F0F066); // Which pipe to read, 40 bit address
myRadio.startListening (); // Stop Transminting and start Reveicing
if (myRadio.available ())
{
while (myRadio.available ())
{
myRadio.read (& data, sizeof (data));
}
Serial.print ("\ nReceived:");
Serial.println (data.msg);
}
}
