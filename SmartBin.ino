#define TP 6
#define EP 7
#include <Stepper.h>
bool open;
const int stepsPerRevolution = 2048; 

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

unsigned long currentTime,previousTime,delayTime=5000;

int distance()
{
  digitalWrite(TP, LOW);
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  long duration = pulseIn(EP, HIGH);
  int   distance = duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.println(distance);
  return distance;
}
void setup() {
  // put your setup code here, to run once:
  myStepper.setSpeed(6);
  pinMode(TP,OUTPUT);
  pinMode(EP,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime=millis();
  int D=distance();
  if(D!=0)
  {
  if(D<=10&&!open)
  {
    open=true;
    myStepper.step(-400);
    Serial.println("Open");
    previousTime=currentTime;
  }
  else if(D>10&&currentTime-previousTime>=delayTime&&open)
  {
    open=false;
    myStepper.step(400);
    Serial.println("Close");
  }
  }
  delay(10);
}
