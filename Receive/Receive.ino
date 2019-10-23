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


#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 53;

signed int right;
signed int left;

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
  uint8_t xaxis;
  uint8_t yaxis;
};

NRFLite _radio;
RadioPacket _radioData;

void setup()
{
  Serial.begin(9600);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }

}


void loop()
{
  while (_radio.hasData())
  {
    _radio.readData(&_radioData); // Note how '&' must be placed in front of the variable name.
    left = map(_radioData.yaxis, 0, 255, -255,  255);
    right = map(_radioData.xaxis, 0, 255, -255, 255);
        tank(left, right, 10);
//    arcade(right, left);
//    Serial.println(left);

  }
}


//While we understand that making separate functions for moving straight and turning
//isn't necessary, we want tomake them now so that they're ready when we need them later.


void arcade(signed int throttle, signed int steering)
{
  Serial.print("Throttle: ");
  Serial.println(throttle);
  Serial.print("Steering: ");
  Serial.println(steering);
  {
    if ((throttle > 10) && (steering > 10))
    {
      tank(throttle, map(throttle, 0, 255, 0, throttle - steering), 10);
    }
    else if ((throttle > 10) && (steering < -11))
    {
      tank(map(throttle, 0, 255, 0, throttle + steering), throttle, 10);
    }
    else if ((throttle < -10) && (steering > 10))
    {
      tank(throttle, map(throttle, -255, 0, 0, throttle + steering), 10);
    }
    else if ((throttle < -10) && (steering < -11))
    {
      tank(map(throttle, -255, 0, throttle - steering, 0), throttle, 10);
    }
    else if ((steering > -10) && (steering < 10))
    {
      tank(throttle, throttle, 10);
    }
    else
    {
      tank(0, 0, 10);
    }
  }

}




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


void tank(signed int right, signed int left, int duration)
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
