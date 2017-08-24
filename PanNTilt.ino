/*
 * This file moves a pan-tilt mechanism controlled by two potentiometers 
 * 
 * File created by Phil Ring
 */ 

#include <Servo.h> 

#define PAN_SERVO_PIN   5 // change
#define PAN_POT_PIN     7 // change?
#define TILT_SERVO_PIN  6
#define TILT_POT_PIN    8

Servo panServo;  
Servo tiltServo;

int panCurAngle = 0;
int tiltCurAngle = 0;

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
  return potVal; // scale somehow lol 
}

void setup() 
{ 
  panServo.attach(PAN_SERVO_PIN);  
  panServo.write(0);               
  delay(15);
  tiltServo.attach(TILT_SERVO_PIN);  
  tiltServo.write(0);               
  delay(15);
} 
 
void loop() 
{ 
  int panDesiredAngle = scalePotVal(analogRead(PAN_POT_PIN));
  int tiltDesiredAngle = scalePotVal(analogRead(TILT_POT_PIN));

  if (panDesiredAngle != panCurAngle) { // save processing, only write on change
    panCurAngle = moveToAngle(panServo, panDesiredAngle, panCurAngle);
  }
  if (tiltDesiredAngle != tiltCurAngle) { // save processing, only write on change
    tiltCurAngle = moveToAngle(tiltServo, tiltDesiredAngle, tiltCurAngle);
  }
} 

