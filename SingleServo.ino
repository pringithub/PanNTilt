/*
 * This file moves a servo controlled by a potentiometer 
 * 
 * File created by Phil Ring
 */ 

#include <Servo.h> 

#define SERVO_PIN   5 // actually 4 on the MHacks Hacker Board
#define POT_PIN     0 // change?

Servo myservo;  
 
int curAngle = 0;

int moveToAngle(Servo servo, int angle, int pos, int step=1) {
  //error checking for now
  if (angle < 0 || angle > 180) return 0;

  if (pos < angle) {
  for(; pos <= angle; pos += step) {                                  
      servo.write(pos);               
      delay(15);                        
    }
  } else {
    for(; pos >= angle; pos -= step) {                                
      servo.write(pos);               
      delay(15);                        
    }
  }

  return pos;
}

// scaled between 0 and 180
int scalePotVal(int potVal) {
  return potVal * 180 / 1024; // scale somehow lol 
}

void setup() 
{ 
  myservo.attach(SERVO_PIN);  
  myservo.write(0);               
  delay(15);

  // debugging
  delay(1000);
  Serial.begin(115200);
} 
 
void loop() 
{   
  int desiredAngle = scalePotVal(analogRead(POT_PIN));

  Serial.println(desiredAngle);

  if (desiredAngle != curAngle) { // save processing, only write on change
    curAngle = moveToAngle(myservo, desiredAngle, curAngle);
  }
  
} 

