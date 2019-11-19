/* Austin Gnecco, Danny Maas, Jessica Pearson, Saket Shanmugam
   Program: New Wiring
   Goal: Get the robot working with the new wiring.
*/


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


//For setting the speeds:
signed int right;
signed int left;
signed int power;      //right powers


void setup()
{
  //Set the pins as outputs
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
}


void loop()
{
//  Move(0,0);
//  coast();
//  halt();
}


void Move(signed int rightSpeed, signed int leftSpeed)
{
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
    analogWrite(ENA, leftSpeed);
  }
  else if (leftSpeed < 0)
  {
    digitalWrite(left2, LOW);
    digitalWrite(left1, HIGH);
    analogWrite(ENA, abs(leftSpeed));
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
