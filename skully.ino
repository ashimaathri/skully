/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int SERVO_PIN = 9;
int PIR_PIN = 2;
int LED_PINS[2] = {4, 5};

void setup() {
  //Serial.begin(9600);
  
  myservo.attach(SERVO_PIN);
  
  pinMode(PIR_PIN, INPUT);

  for(int i = 0; i < 2; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void stopSkully() {
  myservo.write(90);
}

void startClockwise() {
  myservo.write(0);
}

void startAnticlockwise() {
  myservo.write(180);
}

void moveTill(int angle) {
  float servoRPM = 100;
  float msPerMinute = 60000;
  float degreePerRotation = 360;
  
  float msPerRotation = msPerMinute / servoRPM;
  float msForAngle = (angle / degreePerRotation) * msPerRotation;
  
  delay(msForAngle); 
}

void moveSkully(int angle) {
  if(angle > 0) {
    startClockwise();
    moveTill(angle);
  } else {
    startAnticlockwise();
    moveTill(-angle);
  }
  
  stopSkully();
  
  delay(500);
}

void setEyeLedsState(int state) {
  for(int i = 0; i < 2; i++) {
    digitalWrite(LED_PINS[i], state);
  }  
}

void openSkullyEyes() {
  setEyeLedsState(HIGH);
}

void closeSkullyEyes() {
  setEyeLedsState(LOW);
}

void blinkAndOpenSkullyEyes() {
  for(int j = 0; j < 7; j++) {
    closeSkullyEyes();
    delay(50);
    openSkullyEyes();
    delay(50);
  }
}

void wakeUpSkully() {
  //Serial.println("Skully woke up. Boooo.....");
  
  moveSkully(180);
  
  blinkAndOpenSkullyEyes();
  
  moveSkully(-60);
  moveSkully(30);
  moveSkully(-30);
}

void putSkullyToSleep() {
  //Serial.println("Skully went to sleep. Ah....");
  
  moveSkully(-150);
  
  closeSkullyEyes();
}

int pirState = LOW;

void loop() {
  if(digitalRead(PIR_PIN) == HIGH && pirState == LOW) {
    pirState = HIGH;
    wakeUpSkully();
  } else if(digitalRead(PIR_PIN) == LOW && pirState == HIGH) {
    pirState = LOW;
    putSkullyToSleep();
  }
}
