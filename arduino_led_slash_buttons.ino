//a new beggining
// declaration  of variables
const int levelButton = 9; // physical variable of the intensity of the led
const int positionButton =8; // physical variable of the position of the led
int pinNumber; // pinMode\
int  pinNumber[]= {3,4,5,6,7}; // array defining the pins
int ledlevel =0; // brightness
int ledPos =3; // led Positionning based on the value of the button
int val; // uptaing the  state of the Led's button
int oldval;
int posval; // updatint the state of the Led's position
int posoldval;
void setup() {
  Serial.begin(9600);
  for(pinNumber =7; pinNumber>2; pinNumber--) {
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, HIGH); // see if led is on 
  delay(500);
  digitalWrite(pinNumber, LOW);
  }
  pinMode(levelButton, INPUT);
  pinMode(positionButton, INPUT);

}
int getledLevel() { //function getting the value of brightness of the led
  val= digitalRead(levelButton); 
  if ((val== HIGH&&(oldval == LOW))) { // value being updated
    ledlevel = ledlevel+51; // plus 51 cuz max value of led =255;  
    delay(10);
    if(ledlevel>255) {
      ledlevel =0;
    }
  }
  oldval =val; // value gettung updated
  return ledlevel; // return the brightness
}

// same sh**TT
int getledPos() {
  

  posval= digitalRead(positionButton);
  if ((posval== HIGH&&(posoldval == LOW))) {
 
    ledPos = ledPos+1;
    delay(10);
    if(ledPos>7) {
      ledPos = 3;
    }
  }
  posoldval =posval;
  return ledPos;
}

void loop() {
                                                                                                                                                     
  // put your main code here, to run repeatedly:
    for(pinNumber =7; pinNumber>2; pinNumber--) {
      if( pinNumber ==  getledPos()){
        analogWrite(pinNumber, getledLevel());
    }
    else {
      digitalWrite(pinNumber, LOW);
    }
    }

}
