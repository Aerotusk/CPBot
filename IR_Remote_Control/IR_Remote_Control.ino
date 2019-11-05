/* Danny Maas, Jessica Pearson, Austin Gnecco, Saket Shanmugam
   Program: Remote Control Robot
   Goal: Control the robot with an IR remote. There are 15 buttons
   that will be used to control it: 11 to control speed, four to
   control direction. Make a function that will take any of these
   speeds as inputs and still work.

   Also, we haven't changed the robot over to the new wiring yet.
   We will be making that change this week and it will show up in
   our code next time. For now though, we aren't having any PWM
   issues.
*/
#include <IRremote.h>
#include <IRremoteInt.h>

//Stuff needed for the IR libraries to work
IRrecv irrecv(12); // Create an irrecv object instance
decode_results results; // Create a place to hold the IR code read x

//Motors:
// Right Motor
int right1 = 4;
int right2 = 5;
// Left Motor
int left1 = 7;
int left2 = 6;

//For setting the speeds:
signed int right;
signed int left;
signed int rightPower; //Since rightSpeed and leftSpeed get used later
signed int leftPower;  //but we still need something to store left and 
signed int power;      //right powers


void setup()
{
  //Set the pins as outputs
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  irrecv.enableIRIn();
}


void loop()
{
  if (irrecv.decode(&results)) // Have we received an IR signal?
  {
    translateIR(); // Determine which key was pressed
    irrecv.resume();
  }
  halt(); //We prefer to have the robot only move when we press
  //buttons, because sometimes the robot turns and doesn't
  //receive codes anymore, and just keeps moving. This keeps
  //that from happening.
}


void translateIR() //Includes case statement to have different things
                   //happen for different button presses.
{
  switch (results.value)
  {
    case 0xFF18E7: //Up (Move Forwards)
      rightPower = power;
      leftPower = power;
      Move(rightPower, leftPower);
      break;

    case 0xFF10EF: //Left (Turn Left)\
      rightPower = -power;
      leftPower = power;
      Move(rightPower, leftPower);
      break;

    case 0xFF5AA5: //Right (Turn Right)
      rightPower = power;
      leftPower = -power;
      Move(rightPower, leftPower);
      break;

    case 0xFF4AB5: //Down (Move Backwards)
      rightPower = power;
      leftPower = power;
      Move(rightPower, leftPower);
      break;

    case 0xFF38C7: //OK (Motors at 0%)
      power = 0;
      break;

    case 0xFFA25D: //1 (Motors at 10%)
      power = 25;
      break;

    case 0xFF629D: //2 (Motors at 20%)
      power = 50;
      break;

    case 0xFFE21D: //3 (Motors at 30%)
      power = 75;
      break;

    case 0xFF22DD: //4 (Motors at 40%)
      power = 105;
      break;

    case 0xFF02FD: //5 (Motors at 50%)
      power = 130;
      break;

    case 0xFFC23D: //6 (Motors at 60%)
      power = 155;
      break;

    case 0xFFE01F: //7 (Motors at 70%)
      power = 180;
      break;

    case 0xFFA857: //8 (Motors at 80%)
      power = 205;
      break;

    case 0xFF906F: //9 (Motors at 90%)
      power = 230;
      break;

    case 0xFF9867: //0 (Motors at 100%)
      power = 255;
      break;

    case 0xFFFFFFFF: //Repeat
      Move(rightPower, leftPower);
      break;
  }
  delay(10);
}


//Move the motors
//The lab procedure said to make a different function for
//each type of movement (Move forwards, backwards, left, right),
//but that's not super efficient. Plus, we already developed this
//function a week or so ago and we want to keep it.
void Move(signed int rightSpeed, signed int leftSpeed)
{
  if (rightSpeed > 0)
  {
    analogWrite(right1, rightSpeed);
    analogWrite(right2, 0);
  }
  else if (rightSpeed < 0)
  {
    right = abs(rightSpeed);
    analogWrite(right1, 0);
    analogWrite(right2, abs(rightSpeed));
  }
  if (leftSpeed > 0)
  {
    analogWrite(left1, leftSpeed);
    analogWrite(left2, 0);
  }
  else if (leftSpeed < 0)
  {
    left = abs(leftSpeed);
    analogWrite(left1, 0);
    analogWrite(left2, abs(leftSpeed));
  }
  delay(80); //This prevents the motor from turning off instantly,
  //but it also times it so that the motors receive STOP
  //right before they would receive a REPEAT code.
  //(Values other than 80 made it jittery)
}


void halt()  //Stop all motors
{
  analogWrite(right1, 0);
  analogWrite(right2, 0);
  analogWrite(left1, 0);
  analogWrite(left2, 0);
}
