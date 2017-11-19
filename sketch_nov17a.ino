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
const byte address  [6] = "00001";
char receivedData[32] = "";
Servo leftservo;
Servo rightservo;

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
  int yvalue, xvalue;
  int left, right;
 // Serial.println(radio.getPayloadSize());

  if (radio.available()&&radio.getPayloadSize() >= sizeof(xvalue)+sizeof(yvalue) )  {


     radio.read(&receivedData, sizeof(receivedData));
xvalue = atoi(&receivedData[0]);
delay(10);
 radio.read(&receivedData, sizeof(receivedData));
yvalue = atoi(&receivedData[0]);
  Serial.print((yvalue));
 Serial.print("\t");
Serial.println(xvalue);
delay(400);
  }
 int moduleTourne = 179 / moduleTourne;
    if (yvalue > 90) {
      right = map(xvalue, 0, 179, moduleTourne, 0);
      advance(xvalue, right);
    }
    else if (yvalue < 90) {
      
      left = map(xvalue, 0, 179, 0, moduleTourne);
      advance(left, xvalue);
    }
    else if (yvalue == 90) {
      left = 90;
      right = 90;
      advance(left, right);
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
    */
    


}
void advance(int left, int right) {
  leftservo.write(left);
  rightservo.write(right);
}
