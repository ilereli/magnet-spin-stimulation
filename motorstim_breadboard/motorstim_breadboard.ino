#include <ezButton.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int ledPin = 4;  // the number of the LED pin
Adafruit_DCMotor *motor = AFMS.getMotor(1);
// variables that will change:
int ledState = LOW; // initializing of LED
int motorState= LOW;  // initializing of motor
const int buttonPin = 2;
//ezButton(2);
unsigned long CurrentTime = 0;  // storage of last updated timing
int epoch = 500;  // interval at which to blink (milliseconds)
unsigned long StartTime = millis(); 
unsigned long LoopTime = StartTime;
bool PressDown = false;

void setup() 
{
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  //digitalWrite(motorPin, LOW);
  //button.setDebounceTime(50); //50 ms debounce
  pinMode(buttonPin, INPUT);
  AFMS.begin();
  Serial.begin(9600);
  Serial.println("System ready");
}

void loop() 
{
  PressDown = digitalRead(buttonPin);
  //button.loop();
  //delay(100);
    
  if (PressDown == true)
    {
      StartTime = millis();
      LoopTime = StartTime;
    
      Serial.println("Button pressed, starting simulation:");

      while (millis() - StartTime < 5000)
        {
          CurrentTime = millis();
          if (CurrentTime - LoopTime >= epoch)
            {
              LoopTime = millis();

              if (motorState == 0)
                {
                  motorState = 255;
                  Serial.println("motorState HIGH");
                  Serial.println(millis() - StartTime);
                  
                } 
              else
                {
                  ledState = LOW;
                  motorState = LOW;
                  Serial.println("motorState LOW");
                  Serial.println(millis() - StartTime);
                }    
              digitalWrite(ledPin, ledState);
              digitalWrite(motorPin, motorState);  
            }
        }
      Serial.println("bool reset");
      PressDown = false;
      Serial.println(PressDown);
      Serial.println("Stimulation over"); //here
      Serial.println(millis() - StartTime);
      Serial.println(CurrentTime - LoopTime);
      Serial.println("While loop broken");
      digitalWrite(ledPin, LOW);
      digitalWrite(motorPin, LOW);
    }
  
  else
    {
      ledState == LOW;
      motorState == LOW;
      digitalWrite(ledPin, ledState);
      digitalWrite(motorPin, motorState);
    }
}
