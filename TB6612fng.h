#ifndef TB6612fng_H
#define TB6612fng_H

#include <vector>

#define FRONT_LEFT_MOTOR 0
#define FRONT_RIGHT_MOTOR 1
#define BACK_RIGHT_MOTOR 2
#define BACK_LEFT_MOTOR 3

#define FORWARD 1
#define BACKWARD -1
#define STOP 0

const int PWM_FL = 27;  const int PWM_FR = 19;
const int PWM_BL = 32;  const int PWM_BR = 0;  

int pwmFL = 255;  int pwmFR = 255;
int pwmBL = 255;  int pwmBR = 255;

struct MOTOR_PINS {
  int pinIN1;
  int pinIN2;    
};

std::vector<MOTOR_PINS> motorPins = 
{
  {26, 25},  //FRONT_LEFT_MOTOR
  {2, 18},  //FRONT_RIGHT_MOTOR   
  {15, 5},  //BACK_RIGHT_MOTOR 
  {14, 33},  //BACK_LEFT_MOTOR
};

void rotateMotor(int motorNumber, int motorDirection){
  if (motorDirection == FORWARD){
    digitalWrite(motorPins[motorNumber].pinIN1, HIGH);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);    
  }
  else if (motorDirection == BACKWARD){
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, HIGH);     
  }
  else if (motorDirection == STOP){
    digitalWrite(motorPins[motorNumber].pinIN1, LOW);
    digitalWrite(motorPins[motorNumber].pinIN2, LOW);       
  }
}

void move(int motorFL, int motorFR, int motorBL, int motorBR) {
  rotateMotor(FRONT_LEFT_MOTOR, motorFL);     rotateMotor(FRONT_RIGHT_MOTOR, motorFR);
  rotateMotor(BACK_LEFT_MOTOR, motorBL);      rotateMotor(BACK_RIGHT_MOTOR, motorBR);
}

void speed(int pwmFL, int pwmFR, int pwmBL, int pwmBR) {
  analogWrite(PWM_FL, abs(pwmFL));   analogWrite(PWM_FR, abs(pwmFR));  
  analogWrite(PWM_BL, abs(pwmBL));   analogWrite(PWM_BR, abs(pwmBR));  
}

void moveSTOP() {
 move(STOP, STOP, 
      STOP, STOP);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void resetESP(){
  ESP.restart();
}

void moveUP() {
 move(FORWARD, FORWARD, 
      FORWARD, FORWARD);
 speed(pwmFL, pwmFR, 
       pwmBR, pwmBL);
}

void moveDOWN() {
 move(BACKWARD, BACKWARD, 
      BACKWARD, BACKWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveLEFT() {
 move(BACKWARD, FORWARD, 
      FORWARD,  BACKWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveRIGHT() {
 move(FORWARD, BACKWARD, 
      BACKWARD, FORWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveUP_LEFT() {
 move(STOP, FORWARD, 
      FORWARD, STOP);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveUP_RIGHT() {
 move(FORWARD, STOP, 
      STOP, FORWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveDOWN_LEFT() {
 move(BACKWARD, STOP, 
      STOP, BACKWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveDOWN_RIGHT() {
 move(STOP, BACKWARD, 
      BACKWARD, STOP);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveTURN_LEFT() {
 move(BACKWARD, FORWARD, 
      BACKWARD, FORWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void moveTURN_RIGHT() {
 move(FORWARD, BACKWARD, 
      FORWARD, BACKWARD);
 speed(pwmFL, pwmFR, 
       pwmBL, pwmBR);
}

void setUpPinModes(){
  for (int i = 0; i < motorPins.size(); i++)
  {
    pinMode(motorPins[i].pinIN1, OUTPUT);
    pinMode(motorPins[i].pinIN2, OUTPUT);  
    rotateMotor(i, STOP);  
  }
}



#endif