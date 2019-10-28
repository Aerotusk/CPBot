/* 
   Names: Austin Gnecco, Danny Maas, Jessica Pearson, Saket Shanmugam
   Program: Project 4, For Four Squared Loop-the-Loop
   Goal: Use a for loop in order to trace a square, then pause after
   each square trance and flash the LED for three seconds.
*/

int right1 = 4; // IN1 (Motor A)
int right2 = 5; // IN2 (Motor A)
int left1 = 7; // IN3 (Motor B)
int left2 = 6; // IN4 (Motor B)
int LED = 13; // LED pin
int full_speed = 255;
int forward_time = 1000;
int turn_time = 255;

void setup()
{
 pinMode(right1, OUTPUT);
 pinMode(right2, OUTPUT);
 pinMode(left1, OUTPUT);
 pinMode(left2, OUTPUT);
 pinMode(LED,OUTPUT);
}

void loop()
{
 //Repeat this four times:
 for(int i = 0;i<4;i++)
 {
  Trace1Side();
  PivotRight();
 }
 flashLED(1000);
 delay(2000);
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
}
