
const int A =  12;
const int AA =  13;
const int B =  14;
const int BB =  15;
const int LED_PIN = 11;

char sBuf[4];
char onOff[8];
unsigned char holdTime[4][8];

byte jointAngle = 0;
int currentStep = 0;

byte tVal = 0;

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
  
  pinMode(A, OUTPUT);
  pinMode(AA, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BB, OUTPUT);
//  
  digitalWrite(A, HIGH);
  digitalWrite(AA, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(BB, HIGH);  
  
//for(int j = 0; j < 10; j++){
//// CCW
//  for(int i = 8; i >= 1; i--){
////    waveDrive(i);
////    two_phase(i);
//    half_step(i);
//    delayMicroseconds(2000);
//  }
//  delay(100);
//}

//  for(int j = 0; j < 300; j++){  
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
  
//    half_step(1);
//    delayMicroseconds(holdTime[0][0]);
//    half_step(2);
//    delayMicroseconds(holdTime[0][1]);
//    half_step(3);
//    delayMicroseconds(holdTime[0][2]);
//    half_step(4);
//    delayMicroseconds(holdTime[0][3]);
//    half_step(5);
//    delayMicroseconds(holdTime[0][4]);
//    half_step(6);
//    delayMicroseconds(holdTime[0][5]);
//    half_step(7);
//    delayMicroseconds(holdTime[0][6]);
//    half_step(8);
//    delayMicroseconds(holdTime[0][7]);


//if(holdTime[0][1] > 120) digitalWrite(LED_PIN, HIGH);
//else digitalWrite(LED_PIN, LOW);


  for(int i = 1; i <= 8; i++){
    half_step(i);
    delayMicroseconds(holdTime[0][i] * 10);
//    half_step(i);
//    delayMicroseconds(10000);    
    
  }

//  delay(10);
// CW
//  for(int i = 1; i <= 8; i++){
//    waveDrive(i);
//    two_phase(i);
//    half_step(i);
//    delayMicroseconds(500);
//  }

  //delay(200);


//for(int j = 0; j < 30; j++){
//// CCW
//  for(int i = 8; i >= 1; i--){
//    waveDrive(i);
//    two_phase(i);
//    half_step(i);
//    delayMicroseconds(2000);
//  }
//  delay(1000);
//}


  
//  if(sBuf[0] == 0){
//    if(sBuf[1] == 0){
//      if(sBuf[2] == 1){
//        digitalWrite(LED_PIN, HIGH);
//      }
//    }
//  }  
//  
//  digitalWrite(LED_PIN, LOW);


//  for(int i = 0; i < 1; i++){
//    moveOneDegree();
//    delayMicroseconds(200);
//  }

//  for(int i = 0; i < 1; i++){
//    moveOneDegree();
//    delayMicroseconds(200);
//  }
//
//  for(int i = 0; i < 1; i++){
//    moveOneDegree();
//    delayMicroseconds(200);
//  }
//
//  for(int i = 0; i < 1; i++){
//    moveOneDegree();
//    delayMicroseconds(20);
//    moveOneDegree();
//    delayMicroseconds(20);
//    moveOneDegree();
//    delayMicroseconds(20);
//    moveOneDegree();
//    delayMicroseconds(20);
//    moveOneDegree();
//    delayMicroseconds(20);
//    moveOneDegree();
//    delayMicroseconds(20);
//  }
  
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
