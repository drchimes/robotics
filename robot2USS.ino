//include libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
int distance;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//naming motors
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int led = 13;
int button = 2;
int buttonState = 0;

////NEW////
int trig = 9;   // this says trig is in pin 9
int echo = 10;  // this says echo is in pin 10
int trig2 = 5;
int echo2 = 6;

void setup() {
  AFMS.begin();  //must always be the first line in setup()
  Serial.begin(9600);     // serial is communication with arduino
  
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  pinMode(trig, OUTPUT);  //this is output: creates sound
  pinMode(echo, INPUT);   //this is input: listens for returned sound
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  ultraSonic();

  if (distance < 15) {
    // Too close – STOP
    stop();
    delay(1000);
    turnRight();
    delay(150);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
  }

  else {
    // Safe – GO
    forward();
    digitalWrite(led, LOW);
  }
  delay(100);
}

void forward() {
  rightMotor->setSpeed(100);
  leftMotor->setSpeed(100);
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
}

void backward() {
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);
  rightMotor->run(BACKWARD);
  leftMotor->run(BACKWARD);
}

void stop() {
  rightMotor->setSpeed(0);
  leftMotor->setSpeed(0);
}

void turnLeft() {
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
}

void turnRight() {
  rightMotor->setSpeed(100);
  leftMotor->setSpeed(100);
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
}

void ledBlink() {
  digitalWrite(led, HIGH);  //this means turning on the LED
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

void ledButton() {
  buttonState = digitalRead(button);
  if (buttonState == HIGH) {
    digitalWrite(led, LOW);
  }
  else {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(1000);
  }
}

void ultraSonic() {
  digitalWrite(trig, LOW);   //shuts off the trig
  delayMicroseconds(2);      //waits 2 micro seconds
  digitalWrite(trig, HIGH);  //turns on the trig (sound is made)
  delayMicroseconds(10);     //sound will last 10 microseconds
  digitalWrite(trig, LOW);   //shuts off trig

  long duration = pulseIn(echo, HIGH);  //turn on the echo and convert to number
  distance = duration * 0.034 / 2;      //calculates distance from duration

  //the stuff below is the output to the seiral window; its for us
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
}
void ultraSonic2() {
  digitalWrite(trig2, LOW);   //shuts off the trig
  delayMicroseconds(2);      //waits 2 micro seconds
  digitalWrite(trig2, HIGH);  //turns on the trig (sound is made)
  delayMicroseconds(10);     //sound will last 10 microseconds
  digitalWrite(trig2, LOW);   //shuts off trig

  long duration2 = pulseIn(echo2, HIGH);  //turn on the echo and convert to number
  distance2 = duration2 * 0.034 / 2;      //calculates distance from duration

  //the stuff below is the output to the seiral window; its for us
  Serial.print("Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");
  delay(500);
}
