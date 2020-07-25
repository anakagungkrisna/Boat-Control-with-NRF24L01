/* CE - 7
MISO-12
MOSI-11
SCK-13
CS-8
Recently tested with nano
*/
#include <SPI.h>
#include "RF24.h"
#include <Servo.h>
Servo myservo;
RF24 myRadio (7, 8);
struct package {
  int msg;
};
typedef struct package Package;
Package data[10];

byte addresses [] [6] = {"0"};
void setup ()  {
  Serial.begin (9600);
  myRadio.begin ();
  myRadio.setChannel (115); // 115 band above WIFI signals
  myRadio.setPALevel (RF24_PA_MIN); // MIN power low rage
  myRadio.setDataRate (RF24_250KBPS); // Minimum speed
  myservo.attach (3);
  Serial.print ("Setup Initialized");
  delay (500);
}

int Servo_value;
int Pev_servo_value;

void loop () {
  ReadData ();
  //delay (50);
  
  //Pev_servo_value = Servo_value;
  Servo_value = data[0].msg;
  //while (Pev_servo_value <Servo_value) {
    myservo.write(Servo_value);
    //myservo.write (Pev_servo_value);
    //Pev_servo_value ++;
    //delay (2);
  //}
  //while (Pev_servo_value> Servo_value) {
    //myservo.write (Pev_servo_value);
    //Pev_servo_value--;
    //delay (2);
  //}
//data.msg = "nothing to send";
// WriteData ();
// delay (50);
}
void ReadData () {
  myRadio.openReadingPipe (1, 0xF0F0F0F0AA); // Which pipe to read, 40 bit address
  myRadio.startListening (); // Stop Transminting and start Reveicing
  if (myRadio.available ()) {
    while (myRadio.available ()) {
      myRadio.read (& data, sizeof (data));
    }
    for (byte i=0; i<5; i++){
      Serial.println(data[i].msg);
    }
  //Serial.print ("\ nReceived:");
  //Serial.println (data.msg);
  Serial.println();
  }
  }
 /* 
void WriteData ()
{
myRadio.stopListening (); // Stop Receiving and start transminitng
myRadio.openWritingPipe (0xF0F0F066); // Sends data on this 40-bit address
myRadio.write (& data, sizeof (data));
Serial.print ("\ nSent:");
Serial.println (data.msg);
delay (300);
}*/
