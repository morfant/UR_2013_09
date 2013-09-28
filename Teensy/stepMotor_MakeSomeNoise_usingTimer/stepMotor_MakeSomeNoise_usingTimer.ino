#include <avr/interrupt.h>
#include <avr/io.h>
#include <TimerOne.h>

int count = 0;
unsigned long m_time = 0;
unsigned long m_time_diff = 0;
boolean m_timeCheck = false;
boolean hold_B_toggle = false;


// Motor control pin A
const int A = 0;
const int AA = 1;
const int B = 2;
const int BB = 3;

// Motor control pin B
const int A_2 = 6;
const int AA_2 = 7;
const int B_2 = 8;
const int BB_2 = 9;

// Light signal pins
const int light_A = 21;
const int light_B = 20;

//const int kTimeMulti = 10;
int timeMulti = 10;
int potsValFor_A[2];
int potsValFor_B[2];
int pitch_A = 0;
int pitch_B = 0;
int piMod_A = 0;
int piMod_B = 0;
int rate_A = 0;
int rate_B = 0;


void setup()   {
  
  Serial.begin(9600);
  Timer1.initialize(50000);
  Timer1.attachInterrupt(readPots);
  
  init8BitTimerB_0(0);

  // init array with zero.
    for(int i = 0; i < 2; i++){
      potsValFor_A[i] = 0;
      potsValFor_B[i] = 0;
    }
    
  // Pin mode setup ------------------------------  
  pinMode(A, OUTPUT);
  pinMode(AA, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BB, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(AA_2, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(BB_2, OUTPUT);
  
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
}

  // Get serial from SC
void readPots()
{
  // Read pots
  for(int i = 0; i < 2; i++){
    potsValFor_A[i] = analogRead(15 - i);
    potsValFor_B[i] = analogRead(13 - i);
  }
  
  // Update pitch, rate
  pitch_A = potsValFor_A[0] / 128;
//  piMod_A = map(potsValFor_A[0], 0, 1023, 1, 1023) % 128;

  if(potsValFor_A != 0){
    piMod_A = potsValFor_A[0] % 128;
  }else{
    piMod_A = 0;
  }
  
  timeMulti = map(potsValFor_A[1], 0, 1023, 1, 32);

  pitch_B = potsValFor_B[0] / 128;

  if(potsValFor_B != 0){
    piMod_B = potsValFor_B[0] % 128;
  }else{
    piMod_B = 0;
  }

//  rate_B = potsValFor_B[1];
  rate_B = map(potsValFor_B[1], 0, 1023, 1, 3000);    
}

// ************ Main loop ************
void loop()                     
{
  if(hold_B_toggle){
    hold_B();
    sound_A();
  } else{
    hold_A();
    sound_B();
  }
  
//  digitalWrite(light_A, HIGH);  

//  delayMicroseconds(10);

  // TEST CODE  
//  noInterrupts();
//  Serial.print("pitch_A: ");
//  Serial.println(pitch_A);
////  Serial.println(potsValFor_A[0]);
//  Serial.print("piMod_A: ");
//  Serial.println(piMod_A);
//  interrupts();
  
}

void sound_A()
{  
  digitalWrite(light_A, HIGH);
  
  for(int i = 0; i <= pitch_A; i++){
    if(i != pitch_A) stepAndLight_A(i, 128 * timeMulti);
    else stepAndLight_A(pitch_A, piMod_A * timeMulti);
  }
}

void sound_B()
{
  digitalWrite(light_B, HIGH);
  
  for(int i = 0; i <= pitch_B; i++){
    if(i != pitch_B) stepAndLight_B(i, 128 * timeMulti);
    else stepAndLight_A(pitch_B, piMod_B * timeMulti);
  }
}


void stepAndLight_A(int idx, int dt)
{
//  digitalWrite(light_A, HIGH);
  half_step_A(idx); delayMicroseconds(dt/2);
//  digitalWrite(light_A, LOW);
  delayMicroseconds(dt/2);
}

void stepAndLight_B(int idx, int dt)
{
//  digitalWrite(light_B, HIGH);
  half_step_B(idx); delayMicroseconds(dt/2);
//  digitalWrite(light_B, LOW); 
  delayMicroseconds(dt/2);
}

void stepAndLight_AB(int idx, int dt)
{
  //digitalWrite(light_A, HIGH); digitalWrite(light_B, HIGH);
  half_step_A(idx); half_step_B(idx);
  delayMicroseconds(dt/2);
//  digitalWrite(light_A, LOW); digitalWrite(light_B, LOW); delayMicroseconds(dt/2);
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


void hold_A() // A motor control pins HIGH
{
    digitalWrite(light_A, LOW);  
    digitalWrite(A, HIGH);
    digitalWrite(AA, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(BB, HIGH);
//    delayMicroseconds(ht);
}

void hold_B() // B motor control pins HIGH
{
    digitalWrite(light_B, LOW);
    digitalWrite(A_2, HIGH);
    digitalWrite(AA_2, HIGH);
    digitalWrite(B_2, HIGH);
    digitalWrite(BB_2, HIGH);  
//    delayMicroseconds(ht);
}
