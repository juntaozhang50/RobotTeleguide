#include <Servo.h>

Servo mainservo;

void setup() {
  // put your setup code here, to run once:
mainservo.attach(6);
}

void loop() {
  // put your main code here, to run repeatedly:
mainservo.write(0);
}
