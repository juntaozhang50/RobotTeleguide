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
  code empruté
  aide de Monsieur l'hereux et de Xavier l'heureux
*/
/*
   code adaptée pour moteur servo;
   voir aussi indication pour le code receveur
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
  // voir les fonctions qui agissent les broches Ao et A1
alaod(A0);
 Serial.println("\t");// exemple de trouble shooting
aload(A1);

  
}

void aload ( short pin ) { // cette fonction accepte les deux broches mentionnées ci-dessous
  int mean = 0; // valeur de la moyenne initiale

  String xstringmesure; // type de variable occupant moins d'espace
  int nbmesure = 5;
   int mesure;
   char xyData[32] = ""; // variable envoyé
  for (short i = 0; i < nbmesure; i++) {
    mesure = analogRead(pin); // lire les valeurs des broches
    mesure = map(mesure, 0, 1023, 0, 179); // convertir ces valeurs en valeur convenable au direction du cerveau
    mean += mesure; la valeur des mesurs prises sont ajoutés dans les moyennnes
   
    delay(5);
  }
   mean /= nbmesure; // puis ensuite divisé par le nombre de mesure //afin d'éviter les oscillation
    xstringmesure = mean;
    xstringmesure.toCharArray(xyData, 5); // convertion des valeurs
 radio.write(&xyData, sizeof(xyData)); // transmition des valeurs
Serial.print(xstringmesure); // imprimer les valeurs pour le trouble shooting


}

