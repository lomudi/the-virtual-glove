#include <Arduino.h>
#include <Coordinates.h>
#include <Servo.h>
#include <PID_v1.h>

Servo fingerOne;
int analogPin = A5;
int valAng;
int servoAngles[537];

float *getFingerPoint(float r, float phi)
{
  // This method is doing coordinates conversion from polar, r = distance and phi = angle
  Coordinates point = Coordinates();
  point.fromPolar(r, phi);
  float myPoint[] = {point.getX(), point.getY()};
  return myPoint;
}

int stopFinger(int ang)
{
  if (ang >= 500)
  {
    fingerOne.attach(8);
    fingerOne.writeMicroseconds(0.5);
    fingerOne.write(servoAngles[ang]);
    delay(1000);
  }
  else
  {
    fingerOne.detach();
  }
}

int readAngle()
{
  valAng = analogRead(analogPin);
  return valAng;
}

int servoCalibration()
{
  fingerOne.attach(8);
  fingerOne.write(0);
  delay(150);
  for (size_t i = 536; i < 2418; i++)
  {
    fingerOne.write(i);
    delay(150);
    int currAng = readAngle();
    servoAngles[currAng] = i;
    Serial.print("save into array box: ");
    Serial.print(currAng);
    Serial.print(" value = ");
    Serial.print(servoAngles[currAng]);
    Serial.println("");
  }
  fingerOne.detach();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  servoCalibration();
}

void loop()
{
  // put your main code here, to run repeatedly:
  int currServoAng = readAngle();
  Serial.println(currServoAng);
  stopFinger(currServoAng);

  //delay(15); // waits for the servo to get there
}
