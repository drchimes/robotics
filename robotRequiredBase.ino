//include libraries
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//naming motors
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);


void setup() {
  AFMS.begin();//must always be the first line in setup()
 
}

void loop() {

}

void forward(){
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
}
