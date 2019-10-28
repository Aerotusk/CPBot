/*
  Names: Danny Maas, Jessica Pearson, Austin Gnecco, Saket Shanmugam
  Program: Project 1b, The Hard Way
  Description: Make the robot drive in a square, stop, and flash the built-in LED. Code must
  be placed inside the setup() fuction, use constants, and only the pinMode(); digitalWrite();
  analogWrite(); and delay(); commands. No new functions or loops.
*/

// Right motor
const int A1 = 4;
const int A2 = 5;
// Left Motor
const int B1 = 7;
const int B2 = 6;
// Forward: A/B1 255 (or just high), A/B2 0 (or just low)
const int led = 13;
const int full_speed = 255;
const int forward_time = 1000;
const int turn_time = 255;
const int flash_interval = 250;


void setup()
{
  // Declare pin modes
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  pinMode(led, OUTPUT);

  // Forward
  analogWrite(A1, full_speed);
  digitalWrite(A2, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(forward_time);

  // Turn 90 degrees
  analogWrite(A2, full_speed);
  digitalWrite(A1, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(turn_time);

  // Forward
  analogWrite(A1, full_speed);
  digitalWrite(A2, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(forward_time);

  // Turn 90 degrees
  analogWrite(A2, full_speed);
  digitalWrite(A1, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(turn_time);

  // Forward
  analogWrite(A1, full_speed);
  digitalWrite(A2, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(forward_time);

  // Turn 90 degrees
  analogWrite(A2, full_speed);
  digitalWrite(A1, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(turn_time);

  // Forward
  analogWrite(A1, full_speed);
  digitalWrite(A2, LOW);
  analogWrite(B1, full_speed);
  digitalWrite(B2, LOW);
  delay(forward_time);

  // Stop
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);

  // Flash
  digitalWrite(led, HIGH);
  delay(flash_interval);
  digitalWrite(led, LOW);

  // End
}

void loop()
{
  //Not allowed to use :(
}
