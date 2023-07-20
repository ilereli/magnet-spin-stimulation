#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();         //initialize the motorshield
Adafruit_DCMotor *motor = AFMS.getMotor(3);                 //setting DC motor to port 3

// variables that will change:
int motorState= 0;                          // bool for motor running or stopped
const int buttonPin = 7;
int runtime;
unsigned long CurrentTime = 0;              // storage of last updated timing
int epoch = 500;                            // interval at which to blink (milliseconds)
unsigned long StartTime = millis();         // StartTime variable to store initial activation of system from button press
unsigned long LoopTime = StartTime;         // LoopTime variable to calculate when epoch is reached to change motor state
bool PressDown = false;                     // Button activation boolean variable

void setup() 
{
  pinMode(buttonPin, INPUT);                //setting button to read input
  AFMS.begin();                             //starting the motorshield object
  Serial.begin(9600);
  Serial.println("System ready");
}

void loop() 
{
  PressDown = digitalRead(buttonPin);

  if (PressDown == true)
    {
      StartTime = millis();
      LoopTime = StartTime;
    
      Serial.println("Button pressed, starting simulation:");

      while (millis() - StartTime < 7200000)
        {
          CurrentTime = millis();
          if (CurrentTime - LoopTime >= epoch)
            {
              LoopTime = millis();

              if (motorState == 0)
                {
                  motor->setSpeed(255);
                  Serial.println("motorState HIGH");
                  Serial.println(millis() - StartTime);
                  motor->run(FORWARD);
                  motorState = 1;
                } 
              else
                {
                  motor->setSpeed(0);
                  Serial.println("motorState LOW");
                  motor->run(FORWARD);
                  motorState = 0;
                }
              runtime = millis() - CurrentTime;
            }
        }
      PressDown = false;
      Serial.println(millis() - StartTime);
      Serial.println(CurrentTime - LoopTime);
      motor->setSpeed(0);
      motor->run(FORWARD);
      motorState = 0;
      Serial.println(runtime);
    }
  
  else
    {
      motor->setSpeed(0);
      motor->run(FORWARD);
      motorState = 0;
    }
}
