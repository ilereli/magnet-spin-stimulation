#include <millisDelay.h>
int led = 4; //led at pin 4
int pause = 500;
millisDelay ledtimer; //led timer
millisDelay ctimer; //current timer

void setup() 
{
pinMode(led,OUTPUT);
digitalWrite(led,HIGH);
ledtimer.start(10000);
Serial.begin(96000);
}

void loop() 
{
 if (ledtimer.justFinished())
  {
  digitalWrite(led,LOW);
  }
}




