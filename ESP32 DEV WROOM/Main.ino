#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Xe Do Tham"
#define BLYNK_AUTH_TOKEN ""

char ssid[] = "";
char pass[] = "";

bool fetch_blynk_state = true;  //true or false

#include "TB6612fng.h"
#include "GPS.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Servo_ESP32.h>

#define VPIN_BUTTON_0    V0
#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_5    V5
#define VPIN_BUTTON_6    V6
#define VPIN_BUTTON_7    V7 
#define VPIN_BUTTON_8    V8
#define VPIN_BUTTON_9    V9
#define VPIN_BUTTON_10   V10 
#define VPIN_BUTTON_11   V11
#define VPIN_BUTTON_12   V12

int wifiFlag = 0;
int currentMovement = STOP;
bool stopFlag = false;

static const int servoPin1 = 4;
static const int servoPin2 = 23;

Servo_ESP32 servo1;
Servo_ESP32 servo2;

int angle = 90;
int angleStep = 1;

int angleMin = 0;
int angleMax = 180;

char auth[] = BLYNK_AUTH_TOKEN;

BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state){
    for (int i = 0; i <= 12; i++) {
      Blynk.syncVirtual(V0);
    }
  }
}

void handleButtonAction(int state, int stopAction) {
  if (state == STOP) {
    moveSTOP();
  }
  else {
    switch (stopAction) {
      case 0:
        resetESP();
        break;
      case 1:
        moveUP();
        break;
      case 2:
        moveDOWN();
        break;
      case 3:
        moveLEFT();
        break;
      case 4:
        moveRIGHT();
        break;
      case 5:
        moveUP_LEFT();
        break;
      case 6:
        moveUP_RIGHT();
        break;
      case 7:
        moveDOWN_LEFT();
        break;
      case 8:
        moveDOWN_RIGHT();
        break;
      case 9:
        moveTURN_LEFT();
        break;
      case 10:
        moveTURN_RIGHT();
        break;
      default:
        moveSTOP();
        break;
    }
  }
}

BLYNK_WRITE(VPIN_BUTTON_0) {
  handleButtonAction(param.asInt(), 0);
}
 
BLYNK_WRITE(VPIN_BUTTON_1) {
  handleButtonAction(param.asInt(), 1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  handleButtonAction(param.asInt(), 2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  handleButtonAction(param.asInt(), 3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  handleButtonAction(param.asInt(), 4);
}

BLYNK_WRITE(VPIN_BUTTON_5) {
  handleButtonAction(param.asInt(), 5);
}

BLYNK_WRITE(VPIN_BUTTON_6) {
  handleButtonAction(param.asInt(), 6);
}

BLYNK_WRITE(VPIN_BUTTON_7) {
  handleButtonAction(param.asInt(), 7);
}

BLYNK_WRITE(VPIN_BUTTON_8) {
  handleButtonAction(param.asInt(), 8);
}

BLYNK_WRITE(VPIN_BUTTON_9) {
  handleButtonAction(param.asInt(), 9);
}

BLYNK_WRITE(VPIN_BUTTON_10) {
  handleButtonAction(param.asInt(), 10);
}

BLYNK_WRITE(VPIN_BUTTON_11) {
  servo1.write(param.asInt());
}

BLYNK_WRITE(VPIN_BUTTON_12) {
  servo2.write(param.asInt());
}

void setup(void) {
  Serial.begin(115200);
  setUpPinModes();

  pinMode(PWM_FL, OUTPUT);
  pinMode(PWM_FR, OUTPUT);
  pinMode(PWM_BR, OUTPUT);
  pinMode(PWM_BL, OUTPUT);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(90);
  servo2.write(90);
  Serial.println();
  
  mygps.begin(GPSBaud);
  timer.setInterval(5000L, checkGPS); 
  WiFi.begin(ssid, pass);
  Blynk.config(auth);
  
  delay(1000);
}

void loop() {
  if (stopFlag) {  // Check the stop flag
    moveSTOP();  // Stop the robot
    stopFlag = false;  // Reset the stop flag
  }
  
  repeat();
  Blynk.run();
}
