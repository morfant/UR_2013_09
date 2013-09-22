#include <TimerOne.h>


// Control pins
const int BUT_1 =  0;
const int BUT_2 =  1;
const int BUT_3 =  2;
const int BUT_4 =  3;
const int POT_1 =  21;
const int POT_2 =  20;
const int LED_PIN = 11;

// Motor control pins
const int A =  12;
const int AA =  13;
const int B =  14;
const int BB =  15;

// Variables
boolean butVals[4];
int potVals[2];

int currentStep = 0;
byte tVal = 0;
boolean cwFlag = true;
int rate = 0;

void beat_1()
{  
  half_step(1); delay(rate);
  half_step(2); delay(rate);
  half_step(3); delay(rate);
  half_step(4); delay(rate);
  half_step(5); delay(rate);
  half_step(6); delay(rate);
  half_step(7); delay(rate);
  half_step(8); delay(rate + 100);
}

void beat_2()
{
  half_step(3); delay(rate);
  half_step(4); delay(rate + 100);
  half_step(3); delay(rate);
  half_step(4); delay(rate);
  half_step(5); delay(rate);
  half_step(6); delay(rate + 100);
  half_step(1); delay(rate);
  half_step(2); delay(rate + 100);
}

void beat_3()
{
  half_step(6); delay(rate);
  half_step(7); delay(rate);
  half_step(3); delay(rate);
  half_step(4); delay(rate);
  half_step(5); delay(rate);
  half_step(6); delay(rate);
  half_step(2); delay(rate);
  half_step(3); delay(rate);
  half_step(4); delay(rate);
  half_step(6); delay(rate);
  half_step(7); delay(rate);
  half_step(5); delay(rate);
  half_step(6); delay(rate);
}

void beat_4()
{
  half_step(8); delay(rate);
  half_step(7); delay(rate);
  half_step(6); delay(rate);
  half_step(5); delay(rate);
  half_step(4); delay(rate);
  half_step(3); delay(rate);
  half_step(2); delay(rate);
  half_step(1); delay(rate);
}

void readButtonAndPot()
{
  // Read buttons
  for(int i = 0; i < 4; i++){
    butVals[i] = digitalRead(i);
//    Serial.print("Digital ");
//    Serial.print(i);
//    Serial.print(" : ");
//    Serial.println(butVals[i]);
  }
  
  // Read pots
  for(int i = 0; i < 2; i++){
    potVals[i] = analogRead(20 + i);
//    Serial.print("Analog ");
//    Serial.print(20 + i);
//    Serial.print(" : ");
//    Serial.println(potVals[i]);
  }
  
  // Update rate
  rate = potVals[0] * map(potVals[1], 0, 1023, 1, 16);  
}

void setup()   {                
  Serial.begin(9600);
  Timer1.initialize(50000);
  Timer1.attachInterrupt(readButtonAndPot); // blinkLED to run every 0.15 seconds
  
  // Init button array
  for(int i = 3; i != 0; i--){
    butVals[i] = 0;
  }
  
  // Init pot array
  for(int i = 1; i != 0; i--){
    potVals[i] = 0;
  }
  
  // Pin mode setup
  pinMode(LED_PIN, OUTPUT);

  pinMode(BUT_1, INPUT);
  pinMode(BUT_2, INPUT);
  pinMode(BUT_3, INPUT);
  pinMode(BUT_4, INPUT);

  pinMode(POT_1, INPUT);
  pinMode(POT_2, INPUT);
  
  pinMode(A, OUTPUT);
  pinMode(AA, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BB, OUTPUT);

  // Init value
  digitalWrite(A, HIGH);
  digitalWrite(AA, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(BB, HIGH);  

  
  // TEST CODE
//  for(int j = 0; j < 3000; j++){  
//    for(int i = 0; i < 1; i++){
//      moveOneDegree();
//      delayMicroseconds(200000);
//    }
//    delay(300);
//  }


}

void loop()
{ 
  if(butVals[0]) beat_1();
  if(butVals[1]) beat_2();
  if(butVals[2]) beat_3();
  if(butVals[3]) beat_4();
  delayMicroseconds(10);
  
  // Step idx
//  if(cwFlag){
//    // half-step cw
//    if(currentStep <= 8) currentStep++;
//    else currentStep = 1;
//  }else{
//    // half-step ccw
//    if(currentStep > 1) currentStep--;
//    else currentStep = 8;
//  }

//  potVal = map(analogRead(POT_PIN), 0, 255, 0, 2000000);
//  potVal = map(analogRead(POT_PIN), 0, 255, 0, 1000);
//  half_step(currentStep);
  
    
//  delayMicroseconds(potVal);
//    delay(potVal);



// Just spinning
// CW
//  for(int i = 1; i <= 8; i++){
//    half_step(i);
//    delayMicroseconds(500);
//  }

//// CCW
//  for(int i = 8; i >= 1; i--){
//    half_step(i);
//    delayMicroseconds(2000);
//  }
//}

}

void moveOneDegree()
{
  switch(currentStep % 8){
    case 0:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 1");
      break;

    case 1:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 2");      
      break;
    
    case 2:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 3");      
      break;

    case 3:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 4");      
      break;

    case 4:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 5");      
      break;
    
    case 5:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 6");      
      break;
    
    case 6:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 7");      
      break;

    case 7:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 8");      
      break;
  }

  currentStep++;
  Serial.println(currentStep%8);
}

void moveOneDegreeCCW()
{
  switch(currentStep % 8){
    case 7:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 1");
      break;

    case 6:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 2");      
      break;
    
    case 5:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 3");      
      break;

    case 4:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 4");      
      break;

    case 3:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 5");      
      break;
    
    case 2:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 6");      
      break;
    
    case 1:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 7");      
      break;

    case 0:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 8");      
      break;
  }

  currentStep++;
  Serial.println(currentStep%8);
}

void waveDrive(int highInput)
{
  switch(highInput){
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(AA, LOW);
      digitalWrite(B, LOW);
      digitalWrite(BB, LOW);
//      Serial.println("pahse 1");
      break;

    case 2:
      digitalWrite(A, LOW);
      digitalWrite(AA, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(BB, LOW);
//      Serial.println("pahse 2");      
      break;
    
    case 3:
      digitalWrite(A, LOW);
      digitalWrite(AA, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(BB, LOW);
//      Serial.println("pahse 3");      
      break;

    case 4:
      digitalWrite(A, LOW);
      digitalWrite(AA, LOW);
      digitalWrite(B, LOW);
      digitalWrite(BB, HIGH);
//      Serial.println("pahse 4");      
      break;
    
    default:
      digitalWrite(A, HIGH);
      digitalWrite(AA, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(BB, HIGH);  
//      Serial.println("Not in pahse");    
      break;
  }
}

void two_phase(int highInput)
{
  switch(highInput){
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(AA, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(BB, LOW);
//      Serial.println("pahse 1");
      break;

    case 2:
      digitalWrite(A, LOW);
      digitalWrite(AA, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(BB, LOW);
//      Serial.println("pahse 2");      
      break;
    
    case 3:
      digitalWrite(A, LOW);
      digitalWrite(AA, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(BB, HIGH);
//      Serial.println("pahse 3");      
      break;

    case 4:
      digitalWrite(A, HIGH);
      digitalWrite(AA, LOW);
      digitalWrite(B, LOW);
      digitalWrite(BB, HIGH);
//      Serial.println("pahse 4");      
      break;
    
    default:
      digitalWrite(A, HIGH);
      digitalWrite(AA, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(BB, HIGH);  
//      Serial.println("Not in pahse");    
      break;
  }
}

void half_step(int highInput) //2-1-2 sequenceß
{
  switch(highInput){
    case 1:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 1");
      break;

    case 2:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 2");      
      break;
    
    case 3:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 3");      
      break;

    case 4:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 4");      
      break;

    case 5:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 5");      
      break;
    
    case 6:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 6");      
      break;
    
    case 7:
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 7");      
      break;

    case 8:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 8");      
      break;


    default:
      digitalWrite(A, HIGH);
      digitalWrite(AA, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(BB, HIGH);  
//      Serial.println("Not in pahse");    
      break;
  }
}


void allHigh()
{
    digitalWrite(A, HIGH);
    digitalWrite(AA, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(BB, HIGH);  
}
