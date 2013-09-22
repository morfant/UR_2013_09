
const int A =  12;
const int AA =  13;
const int B =  14;
const int BB =  15;
const int LED_PIN = 11;
const int POT_PIN = 21;

char sBuf[4];
char onOff[8];
unsigned char holdTime[4][8];

byte jointAngle = 0;
int currentStep = 0;

byte tVal = 0;
int potVal = 0;

boolean cwFlag = true;

// The setup() method runs once, when the sketch starts

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

void setup()   {                
  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
//  establishContact();  // send a byte to establish contact until receiver responds 
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  
  pinMode(A, OUTPUT);
  pinMode(AA, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BB, OUTPUT);
//  
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
  // Get serial from SC
  if (Serial.available()) {
    Serial.readBytes(sBuf, 4);
    
    if(sBuf[2] != 0) holdTime[sBuf[0]][sBuf[1]] = sBuf[3];
    else holdTime[sBuf[0]][sBuf[1]] = 0;
  }   


  // Step idx
  if(cwFlag){
    // half-step cw
    if(currentStep <= 8) currentStep++;
    else currentStep = 1;
  }else{
    // half-step ccw
    if(currentStep > 1) currentStep--;
    else currentStep = 8;
  }

//  potVal = map(analogRead(POT_PIN), 0, 255, 0, 2000000);
  potVal = map(analogRead(POT_PIN), 0, 255, 0, 1000);
//  half_step(currentStep);
  
  half_step(1);
      delay(potVal);  
  half_step(2);
      delay(potVal);
  half_step(3);
      delay(potVal);
  half_step(4);
      delay(potVal + 100);
  half_step(2);
      delay(potVal);
  half_step(3);
      delay(potVal);
  half_step(4);
      delay(potVal);
  half_step(5);  
      delay(potVal + 100);
  half_step(1);
      delay(potVal);  
  half_step(2);
      delay(potVal + 100);
  half_step(5);
      delay(potVal);
  half_step(6);
      delay(potVal);
  half_step(7);
      delay(potVal);
  half_step(8);
      delay(potVal + 100);
  half_step(3);
      delay(potVal);
  half_step(4);  
      delay(potVal + 100);

//  delayMicroseconds(potVal);
//    delay(potVal);



// Just spinning
// CW
//  for(int i = 1; i <= 8; i++){
//    waveDrive(i);
//    two_phase(i);
//    half_step(i);
//    delayMicroseconds(500);
//  }

  //delay(200);


//// CCW
//  for(int i = 8; i >= 1; i--){
//    waveDrive(i);
//    two_phase(i);
//    half_step(i);
//    delayMicroseconds(2000);
//  }
//  delay(1000);
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
