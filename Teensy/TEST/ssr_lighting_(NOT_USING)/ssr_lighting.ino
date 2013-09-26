#include <TimerOne.h>

int light_A = 0; //PIN B0
int light_B = 1; 
int light_C = 2;   
int light_D = 3; 

int sigIn_A = 21;
int sigIn_B = 20;
int sigIn_C = 19; 
int sigIn_D = 18;

int inputVal_A; // sigIn value
int inputVal_B; // sigIn value
int inputVal_C; // sigIn value
int inputVal_D; // sigIn value

void setup(){
  Serial.begin(9600);
  
//  Timer1.initialize(50000);
//  Timer1.attachInterrupt(readInputSignal); // blinkLED to run every 0.15 seconds

    pinMode(light_A, OUTPUT);
    pinMode(light_B, OUTPUT);  
    pinMode(light_C, OUTPUT);
    pinMode(light_D, OUTPUT);  

    pinMode(sigIn_A, INPUT);
    pinMode(sigIn_B, INPUT);  
    pinMode(sigIn_C, INPUT);
    pinMode(sigIn_D, INPUT);  


}

void loop(){
  
  readInputSignal();
  
  if(inputVal_A) digitalWrite(light_A, HIGH);
  else digitalWrite(light_A, LOW);

  if(inputVal_B) digitalWrite(light_B, HIGH);
  else digitalWrite(light_B, LOW);

  if(inputVal_C) digitalWrite(light_C, HIGH);
  else digitalWrite(light_C, LOW);

  if(inputVal_D) digitalWrite(light_D, HIGH);
  else digitalWrite(light_D, LOW);
  
  delayMicroseconds(100);


}

void readInputSignal()
{
  // Read 4 sigIn digital
    inputVal_A = digitalRead(sigIn_A);
//    Serial.print("SIG_A: ");
//    Serial.println(inputVal_A);
    inputVal_B = digitalRead(sigIn_B);
    inputVal_C = digitalRead(sigIn_C);
    inputVal_D = digitalRead(sigIn_D);

  // Read 4 sigIn analog    
//    inputVal_A = analogRead(sigIn_A);
//    Serial.print("SIG_A: ");
//    Serial.println(inputVal_A);
//    inputVal_B = analogRead(sigIn_B);
//    inputVal_C = analogRead(sigIn_C);
//    inputVal_D = analogRead(sigIn_D);
    
}
