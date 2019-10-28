/* 
 Team: Austin Gnecco, Daniel Maas, Jessica Pearson, Saket Shanmugam
 Program: Project 5, "Don't move unless I say so..."
 Goal: to utilize IF...then...ELSE program to command the CP bot to move 
 forward repeatedly tracing out the 4 sides of the square path only if the 
 left joystick is pushed forward. If the joystick is not pushed forward, stop the motor,
 light the LED for 1/2 seconds before checking the joystick again.
 */

int right1 = 4; // IN1 (Motor A)
int right2 = 5; // IN2 (Motor A)
int left1 = 7; // IN3 (Motor B)
int left2 = 6; // IN4 (Motor B)
int LED = 13; // LED pin
int full_speed = 255;
int forward_time = 1000;
int turn_time = 255;
int joystick = 0;

void setup() 
{ 
  //Set all pinModes to output
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() 
{
  //complete a side if the joystick is moved
 for(int i = 0;i<4;i)
 {
  if(analogRead(joystick) < 600)
  {
  Trace1Side();
  PivotRight();
  i++;
  }
  else
  {
   flashLED(500);
  }  
 } 
  flashLED(1000);
  delay(1000);
}

//Forward
void Trace1Side()
{
  analogWrite(right1, full_speed);
  digitalWrite(right2, LOW);
  analogWrite(left1, full_speed);
  digitalWrite(left2, LOW);
  delay(forward_time);
  //Stop Motors
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  delay(100);
}

// Turn 90 degrees
void PivotRight()
{
  analogWrite(right2, full_speed);
  digitalWrite(right1, LOW);
  analogWrite(left1, full_speed);
  digitalWrite(left2, LOW);
  delay(turn_time);
  //Stop Motors
  digitalWrite(right1, LOW);
  digitalWrite(right2, LOW);
  digitalWrite(left1, LOW);
  digitalWrite(left2, LOW);
  delay(100);
}

//Flash
void flashLED(int flash_interval)
{
  digitalWrite(LED, HIGH);
  delay(flash_interval);
  digitalWrite(LED, LOW);
  delay(flash_interval);
}
