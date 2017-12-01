
/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code
  by Dejan Nedelkovski, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
  Code emprunté
*/
// déclaration des variables et des librairies : Servo Moteur; communication sans fil
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address  [6] = "00001"; //  Adresse du tuyau de communication
char receivedData[32] = ""; // taille des données envoyées en array
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
  
  int yvalue;
  int xvalue;
  int invertyvalue;
  int left; 
  int right;
 // Serial.println(radio.getPayloadSize()); 

  if (radio.available()&&radio.getPayloadSize() >= sizeof(xvalue)+sizeof(yvalue) )  { // vérfier si la communication et établie


     radio.read(&receivedData, sizeof(receivedData));
xvalue = atoi(&receivedData[0]); // convertion des données en entier
delay(10);
 radio.read(&receivedData, sizeof(receivedData));
yvalue = atoi(&receivedData[0]);
  Serial.print((yvalue));
 Serial.print("\t");
Serial.println(xvalue);
delay(200);
  }
  invertyvalue = map(yvalue, 0, 180, 180, 0); // valeur inverse de yvalue ; puisque les roues sont inversés
 int moduleTourne = 179 / moduleTourne; // variable module pour scaler la  trajectoire
    if (yvalue > 90) { // la roue droite opposée à la roue gauche sera activé pour effectuer les mouvement de 0 à 180 degré
      if (xvalue >= 88 && xvalue <= 91 ) {
        leftservo.write(yvalue);
        rightservo.write(invertyvalue);
        // si la direction est droite donc le joystick est centré horizontalement
      }
      else {
      right = map(xvalue, 0, 179, moduleTourne, 0); le niveau de rotation est déterminer par module tourne
           rightservo.write(right);
      }
    }
    else if (yvalue < 90) {  // direction de rotation de 180 degré à 360 degréCode.transmi
        if (xvalue >= 88 && xvalue <= 91 ) {
        leftservo.write(yvalue);
        rightservo.write(invertyvalue);
      }
      else {
      left = map(xvalue, 0, 179, 0, moduleTourne);
      leftservo.write(left);
      }
    }
    // si le joystick est immobile la voiture ne bouge pas
    else if (yvalue == 90) {
  leftservo.write(90);
  rightservo.write(90);
    }
    



}

