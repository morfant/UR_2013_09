#include <TimerOne.h>


// Control pins
const int BUT_1 =  0;
const int BUT_2 =  1;
const int BUT_3 =  2;
const int BUT_4 =  3;
const int POT_1 =  21;
const int POT_2 =  20;

// Motor control pin A
const int A =  11;
const int AA =  12;
const int B =  13;
const int BB =  14;

// Motor control pin B
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
int rate = 0;


// ********** Setup **********
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
  
  // Pin mode setup ------------------------------
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

  // Init Pin value ------------------------------
  digitalWrite(A, HIGH);
  digitalWrite(AA, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(BB, HIGH);  

  digitalWrite(A_2, HIGH);
  digitalWrite(AA_2, HIGH);
  digitalWrite(B_2, HIGH);
  digitalWrite(BB_2, HIGH);  

  
  // TEST CODE ------------------------------
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

// ********** Main Loop **********
void loop()
{ 
  if(butVals[0]) beat_1();
  if(butVals[1]) beat_2();
  if(butVals[2]) beat_3();
  if(butVals[3]) beat_4();
  delayMicroseconds(10);
  
//  noInterrupts();
//  Serial.println(rate);
//  interrupts();
}


// Motor control ------------------------------
void half_step_A(int highInput) //2-1-2 sequenceß
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

void half_step_B(int highInput) //2-1-2 sequenceß
{
  switch(highInput){
    case 1:
      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 1");      
      break;

    case 2:
      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);   
//      Serial.println("pahse 2");      
      break;
    
    case 3:
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 3");      
      break;

    case 4:
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   HIGH);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 4");      
      break;

    case 5:
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  LOW);
//      Serial.println("pahse 5");      
      break;
    
    case 6:
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  HIGH);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 6");      
      break;
    
    case 7:
      digitalWrite(A_2,   LOW);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 7");      
      break;

    case 8:
      digitalWrite(A_2,   HIGH);
      digitalWrite(AA_2,  LOW);
      digitalWrite(B_2,   LOW);
      digitalWrite(BB_2,  HIGH);
//      Serial.println("pahse 8");      
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

// read Buttons and Pots ------------------------------
void readButtonAndPot()
{
  // Read buttons
  for(int i = 0; i < 4; i++){
    butVals[i] = digitalRead(i);
  }
  
  // Read pots
  for(int i = 0; i < 2; i++){
    potVals[i] = analogRead(20 + i);
  }
  
  // Update rate
  rate = potVals[0] * map(potVals[1], 0, 1023, 1, 16);    
//  rate_A = map(potVals[0], 0, 1023, 1, 32) * kMultiA;  
//  rate_B = map(potVals[1], 0, 1023, 1, 32) * kMultiB;    
}


// Sync light with motor step ------------------------------
void beatAndLight_A(int idx, int dt) //normally dt is rate_B/2
{
  digitalWrite(light_A, HIGH);
  half_step_A(idx); delay(dt);
  digitalWrite(light_A, LOW); delay(dt);
}

void beatAndLight_B(int idx, int dt) //normally dt is rate_B/2
{
  digitalWrite(light_B, HIGH);
  half_step_B(idx); delay(dt);
  digitalWrite(light_B, LOW); delay(dt);
}

void beatAndLight_AB(int idx, int dt) //normally dt is rate_B/2
{
  digitalWrite(light_A, HIGH); digitalWrite(light_B, HIGH);
  half_step_A(idx); half_step_B(idx); delay(dt);
  digitalWrite(light_A, LOW); digitalWrite(light_B, LOW); delay(dt);
}



// ************* Beat patterns ************* 
void beat_1()
{
  int ht = rate/2;
  int htl = (rate + 100) / 2;
  beatAndLight_A(1, ht);
  beatAndLight_A(2, ht);
  beatAndLight_A(3, ht);
    beatAndLight_AB(4, ht);
  beatAndLight_A(5, ht);
  beatAndLight_A(6, ht);
  beatAndLight_A(7, ht);
    beatAndLight_AB(8, htl);
}

void beat_2()
{
  int ht = rate/2;
  int htl = (rate + 100) / 2;
  beatAndLight_A(3, ht);
  beatAndLight_A(4, ht);
    beatAndLight_AB(3, ht);
  beatAndLight_A(4, ht);
  beatAndLight_A(5, ht);
    beatAndLight_AB(6, htl);
  beatAndLight_A(1, ht);
    beatAndLight_AB(2, htl);  
}


void beat_3()
{
  int ht = rate/2;
  int htl = (rate + 100) / 2;
  beatAndLight_A(6, ht);
    beatAndLight_AB(7, ht);
  beatAndLight_A(3, ht);
  beatAndLight_A(4, ht);
  beatAndLight_A(5, ht);
    beatAndLight_AB(6, ht);
    beatAndLight_AB(2, ht);
  beatAndLight_A(3, ht);  
  beatAndLight_A(4, ht);
    beatAndLight_AB(6, ht);
  beatAndLight_A(7, ht);
  beatAndLight_A(5, ht);
  beatAndLight_A(6, ht);  
}

void beat_4()
{
  int ht = rate/2;
  int htl = (rate + 100) / 2;  
    beatAndLight_AB(8, ht);
  beatAndLight_A(7, ht);
  beatAndLight_A(6, ht);
  beatAndLight_A(5, ht);
  beatAndLight_A(4, htl);  
    beatAndLight_AB(3, ht);
  beatAndLight_A(2, ht);
  beatAndLight_A(1, ht);  
}
