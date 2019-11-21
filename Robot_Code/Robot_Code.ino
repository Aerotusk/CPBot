/* Austin Gnecco, Danny Maas, Jessica Pearson, Saket Shanmugam
   Program: New Wiring
   Goal: Get the robot working with the new wiring.
*/
// Include the Servo library
#include <Servo.h>

// Declare the Servo pin
int servoPin = 11;
float past;
// Create a servo object
Servo Servo1;






//define pins and variables
const int farLeftSensorAnalog = 15;
const int farLeftSensorDigital = 43;

const int leftSensorAnalog = 14;
const int leftSensorDigital = 45;

const int middleSensorAnalog = 13;
const int middleSensorDigital = 47;

const int rightSensorAnalog = 12;
const int rightSensorDigital = 49;

const int farRightSensorAnalog = 11;
const int farRightSensorDigital = 51;

// Pins used for digital input of obstacle sensors
const int RangeTriggerPin = 40; // Rangefinder Trigger input pin
const int RangeEchoPin = 41; // Rangefinder Echo Sensor output pin
const unsigned long RangeTimeout = 4000; //4 millisec timeout value.

boolean left;
boolean middle;
boolean right;
float rightAdj;
float leftAdj;

// Declares variables
unsigned long EchoDelay = 0;
float Distance = 0.0;

//Motors:
// Right Motor
#define ENA 2
#define right1 3
#define right2 4
// Left Motor
#define left1 5
#define left2 6
#define ENB 7


//Pin Functions:
//  ENA  ||  RM1  ||  RM2  ||  LM1  ||  LM2  ||  ENB  ||     Result
//(1-255)||   L   ||   H   ||       ||       ||       ||  Right Forward
//(1-255)||   H   ||   L   ||       ||       ||       || Right Backwards
// (255) ||   L   ||   L   ||       ||       ||       ||   Right Stop
//  (0)  ||  Any  ||  Any  ||       ||       ||       ||   Right Coast
//       ||       ||       ||   L   ||   H   ||(1-255)||  Left Forward
//       ||       ||       ||   H   ||   L   ||(1-255 || Left Backwards
//       ||       ||       ||   L   ||   L   || (255) ||    Left Stop
//       ||       ||       ||  Any  ||  Any  ||  (0)  ||    Left Coast


void setup()
{
  Serial.begin(9600);

  // Attaches the servo to the pin
  Servo1.attach(servoPin);

  // Makes servo go to 90 degrees
  Servo1.write(90);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(farLeftSensorAnalog, INPUT);
  pinMode(farLeftSensorDigital, OUTPUT);

  pinMode(leftSensorAnalog, INPUT);
  pinMode(leftSensorDigital, OUTPUT);

  pinMode(middleSensorAnalog, INPUT);
  pinMode(middleSensorDigital, OUTPUT);

  pinMode(rightSensorAnalog, INPUT);
  pinMode(rightSensorDigital, OUTPUT);

  pinMode(farRightSensorAnalog, INPUT);
  pinMode(farRightSensorDigital, OUTPUT);
}


void loop()
{
  //Serial.println(analogRead(13));
  adjustMotorSpeeds(sensePathPositionError(getPathSensorStates()));
  Servo1.write(updatePointingAngle(getPathSensorStates()));
  tank(125, 125);
  delay(10);
  hardStop();
}


void tank(signed int rightSpeed, signed int leftSpeed)
{
  rightSpeed *= rightAdj;
  leftSpeed *= leftAdj;
  Serial.print(rightAdj);
  Serial.print("   ");
  Serial.println(leftAdj);
  if (rightSpeed > 0)
  {
    digitalWrite(right1, LOW);
    digitalWrite(right2, HIGH);
    analogWrite(ENA, rightSpeed);
  }
  else if (rightSpeed < 0)
  {
    digitalWrite(right2, LOW);
    digitalWrite(right1, HIGH);
    analogWrite(ENA, abs(rightSpeed));
  }
  if (leftSpeed > 0)
  {
    digitalWrite(left1, LOW);
    digitalWrite(left2, HIGH);
    analogWrite(ENB, leftSpeed);
  }
  else if (leftSpeed < 0)
  {
    digitalWrite(left2, LOW);
    digitalWrite(left1, HIGH);
    analogWrite(ENB, abs(leftSpeed));
  }
}


void coast()  //Allow motors to coast
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void hardStop() //Stop the motors
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
}


float sensePathPositionError(byte pathSensorStates)
{
  int sum = 0;
  int state[5];
  for (int i = 0; i < 5; i++)
  {
    state[i] = bitRead(pathSensorStates, i);
    sum += bitRead(pathSensorStates, i);

  }
  if(sum == 0)
  {
    return past;
  }
  if (sum == 1)
  {
    for (int i = 0; i < 5; i++)
    {
      if (state[i] == 1)
      {
        past = (map((i), 0, 4, 2, -2));
        return (map((i), 0, 4, 2, -2));
      }
      else
      {
      }
    }
  }
  else if (sum == 2)
  {
    for (int i = 0; i < 4; i++)
    {
      if (state[i] == 1)
      {
        if (state[i + 1] == 1)
        {
          past = ((float)(-i) + (float)(1.5));
          return ((float)(-i) + (float)(1.5));
        } else {
          return past;
        }
      } else {}
    }
  } else {
    return past;
  }
}


int updatePointingAngle(float pathError)
{
  int pointGain = 15;
  int sensorPointAngle = 90 - (pointGain * pathError);
  return sensorPointAngle;
}


void adjustMotorSpeeds(float pathError)
{
  int gain = 50;
  int adjustment = gain * pathError;

  rightAdj = (100. - (adjustment)) / 100.;
  leftAdj = (100.  + (adjustment)) / 100.;
}

int readLineSensor(int SensorAnalogInPin, int SensorDigitalOutPin) {
  int SensorState = analogRead(SensorAnalogInPin);


  //determine whether or not the sensor reads white or black
  if (SensorState > 300) {
    //the line is black
    digitalWrite(SensorDigitalOutPin, HIGH);
    return (1);
  }
  else {
    //the line is white
    digitalWrite(SensorDigitalOutPin, LOW);
    return (0);
  }
}

byte getPathSensorStates () {
  //receive values of the sensors
  int a = readLineSensor(farLeftSensorAnalog, farLeftSensorDigital);
  int b = readLineSensor(leftSensorAnalog, leftSensorDigital);
  int c = readLineSensor(middleSensorAnalog, middleSensorDigital);
  int d = readLineSensor(rightSensorAnalog, rightSensorDigital);
  int e = readLineSensor(farRightSensorAnalog, farRightSensorDigital);

  //convert individual digital sensor values into a single byte type digital code
  byte sensorCode = 0;
  bitWrite(sensorCode, 4, a);
  bitWrite(sensorCode, 3, b);
  bitWrite(sensorCode, 2, c);
  bitWrite(sensorCode, 1, d);
  bitWrite(sensorCode, 0, e);
  return (sensorCode);
  //display binary sensor code in serial monitor

}
