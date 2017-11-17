#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <math.h>
/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
/*
   code adaptée pour moteur servo;

  \|\|\|\/\||

*/
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
const int x = A0;
const int y = A1;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}
void loop() {
  // xvalue = round(analogRead(A0));
  // yvalue = round(analogRead(A1));

  //  Serial.print(xvalue);
  //  Serial.print("\t");
  //  Serial.println (yvalue);

  // radio.write(&xvalue, sizeof(xvalue));
  // radio.write(&yvalue, sizeof(yvalue));

  load(x); // envoie x entre 0 et 180
  load(y); // envoie y entre 0 et 180

  Serial.println("=============");
}

void load (short pin) {
  int mean = 0, mesure;
  int nbmesure = 10;
   
  for (short i = 0; i < nbmesure; i++) {
    mesure = analogRead(pin);
    mesure = map(mesure, 0, 1023, 0, 179);
    mean += mesure;
    
    delay(5);
  }
  mean /= nbmesure;
  radio.write(&mean, sizeof(mean));
  Serial.println(mean);
}
