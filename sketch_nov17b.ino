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
const byte address  [6] =  "00001";
const int xpin = A0;
const int ypin = A1;
//char xpin  [1] ;
//char ypin  [2] ;
int xvalue;
int yvalue;
//char xyData[64] = "";

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
//xpin[1] = analogRead(A0);
//ypin [2] = analogRead(A1);
aload(A0);
aload(A1);

  
}

void aload ( short pin ) {
  int mean = 0; 

  String xstringmesure;
  int nbmesure = 10;
   int mesure;
   char xyData[32] = "";
  for (short i = 0; i < nbmesure; i++) {
    mesure = analogRead(pin);
    mesure = map(mesure, 0, 1023, 0, 179);
    mean += mesure;
   
    delay(5);
  }
   mean /= nbmesure;
    xstringmesure = mean;
    xstringmesure.toCharArray(xyData, 5);
 radio.write(&xyData, sizeof(xyData));
Serial.println(xstringmesure);

}

