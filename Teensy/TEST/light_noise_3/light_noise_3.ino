int num = 3; //This number is for below 3 forloops. Match this with number of 'light' array.

int lightA = 0; //PIN B0
int lightB = 5; //PIN D0

int val, val1;

int sigIn = 16; //PIN_F7 IS SIGNAL INPUT PIN 1
int sigIn1 = 17; //PIN_F6 IS SIGNAL INPUT PIN 2

void setup(){

    pinMode(lightA, OUTPUT);
    pinMode(lightB, OUTPUT);  

}

void loop(){
  
  val = digitalRead(sigIn); //read signal data
  
  //LIGHT GROUP A
  if(val == LOW){
    digitalWrite(lightA, HIGH);
  }else{
    digitalWrite(lightA, LOW);
  }
  
  
  val1 = digitalRead(sigIn1); //read signal data
  
  //LIGHT GROUP B
  if(val1 == LOW){
    digitalWrite(lightB, HIGH);
  }else{
    digitalWrite(lightB, LOW);
  }  
}
