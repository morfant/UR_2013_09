#include <TimerOne.h>


const int CW =  12;
const int CCW =  13;
const int LED_PIN = 11;

// The setup() method runs once, when the sketch starts

void setup()   {                
  Serial.begin(9600);

//  Timer1.initialize(40);
//  Timer1.attachInterrupt(lowToHigh_CW()); // blinkLED to run every 0.15 seconds  
  
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
  
  digitalWrite(CCW, HIGH);
//  digitalWrite(CW, LOW);  
}

void lowToHigh_CW(int microSec)
{
  digitalWrite(CW, LOW);
  delayMicroseconds(microSec);
  digitalWrite(CW, HIGH);
  delayMicroseconds(microSec);
}

void lowToHigh_CCW(int microSec)
{
  digitalWrite(CCW, LOW);
  delayMicroseconds(microSec);
  digitalWrite(CCW, HIGH);
  delayMicroseconds(microSec);
}

void loop()                     
{
  
 lowToHigh_CW(500);
 
}

