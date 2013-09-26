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
//const int A =  12;
//const int AA =  13;
//const int B =  14;
//const int BB =  15;

const int A =  11;
const int AA =  12;
const int B =  13;
const int BB =  14;

const int A_2 =  8;
const int AA_2 =  7;
const int B_2 =  6;
const int BB_2 =  5;

// Light signal pins
const int light_A = 19;
const int light_B = 18;

// Variables
boolean butVals[4];
int potVals[2];

int currentStep = 0;
byte tVal = 0;
boolean cwFlag = true;
int rate_A = 0; // rate for motor A
int rate_B = 0; // rate for motor B
const int kMultiA = 10;
const int kMultiB = 100;

void beatAndLight_B(int idx, int dt) //normally dt is rate_B/2
{
  digitalWrite(light_B, HIGH);
  half_step2(idx); delay(dt);
  digitalWrite(light_B, LOW); delay(dt);
}

void beat_B_1()
{
  int ht = rate_B/2;
  int htl = (rate_B + 100) / 2;
  beatAndLight_B(1, ht);
  beatAndLight_B(2, ht);
  beatAndLight_B(3, ht);
  beatAndLight_B(4, ht);
  beatAndLight_B(5, ht);
  beatAndLight_B(6, ht);
  beatAndLight_B(7, ht);
  beatAndLight_B(8, htl);  

  
}

//void beat_2()
//{
//  half_step(3); delay(rate);
//  half_step(4); delay(rate + 100);
//  half_step(3); delay(rate);
//  half_step(4); delay(rate);
//  half_step(5); delay(rate);
//  half_step(6); delay(rate + 100);
//  half_step(1); delay(rate);
//  half_step(2); delay(rate + 100);
//}
//
//void beat_3()
//{
//  half_step(6); delay(rate);
//  half_step(7); delay(rate);
//  half_step(3); delay(rate);
//  half_step(4); delay(rate);
//  half_step(5); delay(rate);
//  half_step(6); delay(rate);
//  half_step(2); delay(rate);
//  half_step(3); delay(rate);
//  half_step(4); delay(rate);
//  half_step(6); delay(rate);
//  half_step(7); delay(rate);
//  half_step(5); delay(rate);
//  half_step(6); delay(rate);
//}
//
//void beat_4()
//{
//  half_step(8); delay(rate);
//  half_step(7); delay(rate);
//  half_step(6); delay(rate);
//  half_step(5); delay(rate);
//  half_step(4); delay(rate);
//  half_step(3); delay(rate);
//  half_step(2); delay(rate);
//  half_step(1); delay(rate);
//}

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
//  rate = potVals[0] * map(potVals[1], 0, 1023, 1, 16);  
  
  rate_A = map(potVals[0], 0, 1023, 1, 32) * kMultiA;  
  rate_B = map(potVals[1], 0, 1023, 1, 32) * kMultiB;    
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

  pinMode(A_2, OUTPUT);
  pinMode(AA_2, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(BB_2, OUTPUT);
  
  // Ligit pin mode setup.
  pinMode(light_A, OUTPUT);
  pinMode(light_B, OUTPUT);
  


  // Init value
  digitalWrite(A, HIGH);
  digitalWrite(AA, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(BB, HIGH);  

  digitalWrite(A_2, HIGH);
  digitalWrite(AA_2, HIGH);
  digitalWrite(B_2, HIGH);
  digitalWrite(BB_2, HIGH);  

  
  // TEST CODE
//  for(int j = 0; j < 3000; j++){  
//    for(int i = 1; i <= 8; i++){
////      half_step(i);
//      half_step2(i);
////      digitalWrite(light_B, HIGH);
//      delay(300);      
//      delayMicroseconds(200000);
////      digitalWrite(light_B, LOW);
//    }
//  }


}

void loop()
{ 
  if(butVals[0]) beat_B_1();
//  if(butVals[1]) beat_2();
//  if(butVals[2]) beat_3();
//  if(butVals[3]) beat_4();
  delayMicroseconds(10);
  
//  noInterrupts();
//  Serial.println(rate);
//  interrupts();
  
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


void half_step(int highInput) //2-1-2 sequenceß
{
  switch(highInput){
    case 1:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 1");
      digitalWrite(light_A, LOW);
      break;

    case 2:
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 2");      
      digitalWrite(light_A, HIGH);
      break;
    
    case 3:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 3");

      digitalWrite(light_A, LOW);
      break;

    case 4:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   HIGH);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 4");

      digitalWrite(light_A, LOW);
      break;

    case 5:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  LOW);
//      Serial.println("pahse 5");

      digitalWrite(light_A, LOW);
      break;
    
    case 6:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   LOW);
      digitalWrite(AA,  HIGH);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 6");

      digitalWrite(light_A, LOW);
      break;
    
    case 7:
      digitalWrite(light_A, HIGH);
    
      digitalWrite(A,   LOW);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 7");

      digitalWrite(light_A, LOW);
      break;

    case 8:
      digitalWrite(light_A, HIGH);
      
      digitalWrite(A,   HIGH);
      digitalWrite(AA,  LOW);
      digitalWrite(B,   LOW);
      digitalWrite(BB,  HIGH);
//      Serial.println("pahse 8");

      digitalWrite(light_A, LOW);
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

void half_step2(int highInput) //2-1-2 sequenceß
{
  switch(highInput){
    case 1:
//      digitalWrite(light_B, HIGH);
//      Serial.println("h");

      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 1");

//      digitalWrite(light_B, LOW);
//      Serial.println("l");
      
      break;

    case 2:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);   
//      Serial.println("pahse 2");      

//      digitalWrite(light_B, LOW);
      break;
    
    case 3:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 3");      

//      digitalWrite(light_B, LOW);
      break;

    case 4:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 4");      

//      digitalWrite(light_B, LOW);
      break;

    case 5:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 5");      

//      digitalWrite(light_B, LOW);
      break;
    
    case 6:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 6");      

//      digitalWrite(light_B, LOW);
      break;
    
    case 7:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 7");      

//      digitalWrite(light_B, LOW);
      break;

    case 8:
//      digitalWrite(light_B, HIGH);
    
      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 8");      

//      digitalWrite(light_B, LOW);
      break;


    default:
      digitalWrite(A_2, HIGH);
      digitalWrite(AA_2, HIGH);
      digitalWrite(B_2, HIGH);
      digitalWrite(BB_2, HIGH);  
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
