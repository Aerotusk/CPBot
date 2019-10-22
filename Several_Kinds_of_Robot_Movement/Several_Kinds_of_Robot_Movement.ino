/* Danny Maas, Jessica Pearson, Austin Gnecco, Saket Shanmugam
   Program: Several Kinds of Robot Movement
   Goal: "Move straight backwards for one second, then to pivot 90 degrees (one wheel
   forward, one backward, both at the same speed), and then move forward to trace a complete a
   circle (both wheels forward, but at unequal speeds). Include one second pauses between each
   different motion.
*/


// Right Motor
int right1 = 4;  //Turns out A0-A5 are reserved by the Arduino software for the analog pins 0-5
int right2 = 5;  //Hence why we kept getting errors trying to declare A1 and A2. Now we just use
// Left Motor    //Left and right 1 and 2.
int left1 = 7;
int left2 = 6;


void setup()
{
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  //Movement
  moveStraight(255, 1000);
  delay(1000);
  turn(255, -255, 250);
  delay(1000);
  turn(200, 100, 7000);
}


void loop()
{
  // Nothing, we just want it to move once.
}


//While we understand that making separate functions for moving straight and turning
//isn't necessary, we want tomake them now so that they're ready when we need them later.


void moveStraight(signed int power, int duration)
{
  if (power > 0)
  {
    analogWrite(right1, power);
    analogWrite(right2, 0);
    analogWrite(left1, power);
    analogWrite(left2, 0);
  }
  else if (power < 0)
  {
    power = abs(power);
    analogWrite(right1, 0);
    analogWrite(right2, power);
    analogWrite(left1, 0);
    analogWrite(left2, power);
  }
  delay(duration);
  halt();
}


void turn(signed int right, signed int left, int duration)
{
  if (right > 0)
  {
    analogWrite(right1, right);
    analogWrite(right2, 0);
  }
  else if (right < 0)
  {
    right = abs(right);
    analogWrite(right1, 0);
    analogWrite(right2, right);
  }
  if (left > 0)
  {
    analogWrite(left1, left);
    analogWrite(left2, 0);
  }
  else if (left < 0)
  {
    left = abs(left);
    analogWrite(left1, 0);
    analogWrite(left2, left);
  }
  delay(duration);
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
