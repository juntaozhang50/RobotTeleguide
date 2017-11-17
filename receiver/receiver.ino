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
  int x, y;
  int left, right;
  Serial.println(radio.getPayloadSize());
  if (radio.available() && radio.getPayloadSize() >= sizeof(x)+sizeof(y)) {
    radio.read(&x, sizeof(x));
    delay(10);
    radio.read(&y, sizeof(y));
    delay(10);
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);

    int moduleTourne = 179 / moduleTourne;
    if (y > 90) {
      Serial.println("a");
      right = map(x, 0, 179, moduleTourne, 0);
      advance(x, right);
    }
    else if (y < 90) {
      Serial.println("y");
      left = map(x, 0, 179, 0, moduleTourne);
      advance(left, x);
    }
    else if (y == 90) {
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
}

void advance(int left, int right) {
  leftservo.write(left);
  rightservo.write(right);
}

