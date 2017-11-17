/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
int xvalue;
int yvalue;
int xrturn;
int yrturn;
Servo leftservo;
Servo rightservo;
int xturn;
int moduleTourne;
int yturn;
int ymap;
int xmap;
int yloadmap;
int xloadmap;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  leftservo.attach(9);
  rightservo.attach(10);
}
void loop() {
  if (radio.available()) {

    radio.read(&xmap, sizeof(xmap));
    radio.read(&ymap, sizeof(ymap));

  }
  //Serial.println ("x "+xvalue+"y "+yvalue);




  if (ymap >= 90) {
    Serial.println("a");
    /*
      moduleTourne = map(yvalue,600,1023,1,5);
      moduleTourne = 179/moduleTourne;
      xturn = map(xvalue, 0, 1023, 0, 179);
      xrturn = map(xvalue, 0, 1023, moduleTourne, 0);
    */

  }
  else if (ymap <= 90) {
    Serial.println("y");
    /*
      moduleTourne = map(yvalue,0,400,5,1);
      moduleTourne = 179/moduleTourne;
      xturn = map(xvalue, 0, 1023, 0, moduleTourne);
      xrturn = map(xvalue, 0, 1023, 179, 0);
    */

  }
  else {
    xturn = map(xvalue, 0, 1023, 0, 179);
    xrturn = map(xvalue, 0, 1023, 179, 0);
  }
  /*
    Serial.print ("yval  ");
    Serial.print (yvalue);

    Serial.print (" xval  ");
    Serial.print (xvalue);
    Serial.print (" xturn  ");
    Serial.print (xturn);
    Serial.print ("  xrturn  ");
    Serial.print (xrturn);
    Serial.print ("   module  ");
    Serial.println (moduleTourne);
    delay(10);
    leftservo.write(xturn);
    rightservo.write(xrturn);

  */
}

