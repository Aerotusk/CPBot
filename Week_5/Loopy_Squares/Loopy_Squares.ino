/*
  Name: Danny Maas, Jessica Pearson, Austin Gnecco, Saket Shanmugam
  Program: Endless Loop
  Description: Trace a loop using functions, and have it loop it so that it runs
  indefinitely. It should pause for three seconds between each loop.
*/

// Right motor
const int right1 = 4;
const int right2 = 5;
// Left Motor
const int left1 = 7;
const int left2 = 6;
// Forward: A/left1 255 (or just high), A/left2 0 (or just low)
const int led = 13;
const int full_speed = 255;
const int forward_time = 750;
const int turn_time = 255;


void setup()
{
  // Declare pin modes
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(led, OUTPUT);
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

// Flash
void flashLED(int flash_interval)
{
  digitalWrite(led, HIGH);
  delay(flash_interval);
  digitalWrite(led, LOW);
  // End
}

void loop()
{
  //Drive in a square
  Trace1Side();
  PivotRight();
  Trace1Side();
  PivotRight();
  Trace1Side();
  PivotRight();
  Trace1Side();
  PivotRight();
  flashLED(1000);
  delay(2000); //Since it's a three second total, as the LED is on for 1 and it delays for 2
}
