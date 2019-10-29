/* Danny Maas, Jessica Pearson, Austin Gnecco, Saket Shanmugam
   Program: Dual Joystick Robot Motor Control
   Goal: Have one joystick control each side of the robot (left
   joystick controls left motor, right joystick controls right
   motor)
*/

// Right Motor
int right1 = 4;  //Turns out A0-A5 are reserved by the Arduino software for the analog pins 0-5
int right2 = 5;  //Hence why we kept getting errors trying to declare A1 and A2. Now we just use
// Left Motor    //Left and right 1 and 2.
int left1 = 7;
int left2 = 6;
//Joysticks
int rightJoyStick = 0;
int leftJoyStick = 1;
//For setting the speeds:
signed int right;
signed int left;
int deadzone = 39; //15% of 255

void setup()
{
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
}


void loop()
{
  left = map(analogRead(leftJoyStick), 0, 255, -255,  255);
  right = map(analogRead(rightJoyStick), 0, 255, -255, 255);
  Move(right, left);
}

//The instructions want me to take a -100 to 100 value for
//the left and right speeds, but 255 seems more reasonable so
//that we don't lose resolution mapping down to 100, then
//back up to 255.
void Move(signed int rightSpeed, signed int leftSpeed)
{
  if (rightSpeed > deadzone)
  {
    analogWrite(right1, rightSpeed);
    analogWrite(right2, 0);
  }
  else if (rightSpeed < -deadzone)
  {
    right = abs(rightSpeed);
    analogWrite(right1, 0);
    analogWrite(right2, rightSpeed);
  }
  if (leftSpeed > deadzone)
  {
    analogWrite(left1, leftSpeed);
    analogWrite(left2, 0);
  }
  else if (leftSpeed < -deadzone)
  {
    left = abs(leftSpeed);
    analogWrite(left1, 0);
    analogWrite(left2, leftSpeed);
  }
  delay(10); //This is needed so that the motors don't instantly turn off
  //because of the "halt" function
  halt();
}


//We're going to need to stop a lot. Might as well make it a function


void halt()
{
  analogWrite(right1, 0);
  analogWrite(right2, 0);
  analogWrite(left1, 0);
  analogWrite(left2, 0);
}
