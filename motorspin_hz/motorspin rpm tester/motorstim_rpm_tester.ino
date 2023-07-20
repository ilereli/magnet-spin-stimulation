#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();  //initialize the motorshield
Adafruit_DCMotor *motor = AFMS.getMotor(3);          //setting DC motor to port 3

// variables that will change:
int motorState = 0;  // bool for motor running or stopped
const int buttonPin = 7;
int runtime;
unsigned long CurrentTime = 0;       // storage of last updated timing
int epoch = 500;                     // interval at which to blink (milliseconds)
unsigned long StartTime = millis();  // StartTime variable to store initial activation of system from button press
unsigned long LoopTime = StartTime;  // LoopTime variable to calculate when epoch is reached to change motor state
bool PressDown = false;              // Button activation boolean variable
volatile byte rev;
unsigned int rpm;
unsigned long timeold;
unsigned long hzval;
unsigned long period;

void setup() {
  pinMode(buttonPin, INPUT);  //setting button to read input
  AFMS.begin();               //starting the motorshield object
  Serial.println("System ready");
  // next 4 lines only because of my cheat to plug direct into arduino
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);  //cheat instead of connecting to 0v
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);  // cheat instead of connecting to 5v
  // with VCC and GND hardwired you would start here
  pinMode(2, INPUT);   // terminal marked S
  Serial.begin(9600);  // initialise serial for debugging

  attachInterrupt(0, hzcounter, RISING);  //Initialize the intterrupt pin (Arduino digital pin 2)
  rev = 0;
  rpm = 0;
  timeold = millis();
  
}

void loop() {
  PressDown = digitalRead(buttonPin);

  if (PressDown == true) {
    StartTime = millis();
    LoopTime = StartTime;

    Serial.println("Button pressed, starting simulation:");

    while (millis() - StartTime < 5000) {

      CurrentTime = millis();
      if (CurrentTime - LoopTime >= epoch) {
        LoopTime = millis();

        if (motorState == 0) {
          if (rev >= 20) {
            period = (millis() - timeold)/1000;
            rpm = 60 * rev / period ;
            hzval = rev/period;
            timeold = millis();
            Serial.println(rpm);
            Serial.println(hzval);
            rev = 0;
          }
          motor->setSpeed(255);
          Serial.println("motorState HIGH");
          motor->run(FORWARD);
          motorState = 1;

        } else {
          motor->setSpeed(0);
          Serial.println("motorState LOW");
          motor->run(FORWARD);
          motorState = 0;
        }
        runtime = millis() - CurrentTime;
      }
    }
    PressDown = false;
    motor->setSpeed(0);
    motor->run(FORWARD);
    motorState = 0;
  }

  else {
    motor->setSpeed(0);
    motor->run(FORWARD);
    motorState = 0;
  }
}

void hzcounter()  //This function is called whenever a magnet/interrupt is detected by the arduino
{
  rev++;
}
