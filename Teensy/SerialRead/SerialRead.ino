int val;    // variable to read the value from the analog pin 

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  
}

void loop() {
  
  byte jointAngle;

  // check if data has been sent from the computer:
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    jointAngle = Serial.read();
    Serial.println(jointAngle);
  }
  
  val = jointAngle - 90;     // scale it to use it with the servo (value between 0 and 180)     
}

