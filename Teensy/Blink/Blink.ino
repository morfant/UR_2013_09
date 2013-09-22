/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

#include <TimerOne.h>


// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 11;
const int sourcePin_1 = 12;
const int sourcePin_2 = 13;
const int readPin = 0;

int readVal = 0;
int readValCopy = 0;

// the setup() method runs once, when the sketch starts

void setup() {
  Serial.begin(38400);

  Timer1.initialize(150000);
  Timer1.attachInterrupt(readPot); // blinkLED to run every 0.15 seconds  
  
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(sourcePin_1, OUTPUT);  
  pinMode(sourcePin_2, OUTPUT);    
}


void readPot(void)
{
  readVal = max(analogRead(readPin), 10);
}


void loop() {
  
  noInterrupts();
  readValCopy = readVal;
  interrupts();
  
  digitalWrite(ledPin, HIGH);   // set the LED on
  digitalWrite(sourcePin_1, HIGH);   // set the LED on  
  digitalWrite(sourcePin_2, LOW);   // set the LED on     
  delay(readValCopy);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  digitalWrite(sourcePin_1, LOW);   // set the LED on    
  digitalWrite(sourcePin_2, HIGH);   // set the LED on    
  delay(readValCopy);                  // wait for a second
}

