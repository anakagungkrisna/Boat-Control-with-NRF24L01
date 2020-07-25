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
  int msg[10] = {0};
};

byte addresses [] [6] = {"0"};

typedef struct package Package;
  Package data;

//input dari toggle kiri kanan
#define toglKnA 3
#define toglKnB 6
#define toglKrA 2
#define toglKrB 5
int KnAvalue, KnBvalue, KrAvalue, KrBvalue;

//ini buzzer
#define buzzer 4

//input dari push button
#define btnKanan 9
//#define btnKiri 10
int btnKananValue;// btnKiriValue;
  
void setup () {
  Serial.begin (9600);
  myRadio.begin ();
  myRadio.setChannel (115); // 115 band above WIFI signals
  myRadio.setPALevel (RF24_PA_MIN); // MIN power low rage
  myRadio.setDataRate (RF24_250KBPS); // Minimum speed
  delay (500);
  Serial.print ("Setup Initialized");

  pinMode(toglKnA, INPUT);
  pinMode(toglKnB, INPUT);
  pinMode(toglKrA, INPUT);
  pinMode(toglKrB, INPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(btnKanan, INPUT);
  //pinMode(btnKiri, INPUT); KENAPA KALO INI DIPAKE JADI GAJALAN!?


}
void loop () {
  
  int Read_ADC = analogRead (A0);
  int Read_ADC2 = analogRead (A1);
  int Read_ADC3 = analogRead(A3);
  int Read_ADC4 = analogRead(A2);
  int servo_value = map (Read_ADC, 0, 1024, 0,180);
  int servo_value2 = map (Read_ADC2, 0, 1024, 0,180);
  int servo_value3 = map (Read_ADC3, 0, 1024, 0,180);
  int servo_value4 = map (Read_ADC4, 0, 1024, 0,180);

  KnAvalue = digitalRead(toglKnA);
  KnBvalue = digitalRead(toglKnB);
  KrAvalue = digitalRead(toglKrA);
  KrBvalue = digitalRead(toglKrB);

  btnKananValue = digitalRead(btnKanan);
  
  //Data
  data.msg[0] = servo_value;
  data.msg[1] = servo_value2;
  data.msg[2] = servo_value3;
  data.msg[3] = servo_value4;
  data.msg[4] = KnAvalue;
  data.msg[5] = KnBvalue;
  data.msg[6] = KrAvalue;
  data.msg[7] = KrBvalue;
  data.msg[8] = btnKananValue;
  WriteData ();
  delay (50);
  // ReadData ();
  // delay (200);
}
void WriteData () {
  myRadio.stopListening (); // Stop Receiving and start transminitng
  myRadio.openWritingPipe (0xF0F0F0F0AA); // Sends data on this 40-bit address
  myRadio.write (& data, sizeof (data));
  Serial.print ("\ nSent:");
  Serial.print (data.msg[0]);
  Serial.print (" ");
  Serial.println (data.msg[1]);
  //delay (300);
}
/*
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
*/
