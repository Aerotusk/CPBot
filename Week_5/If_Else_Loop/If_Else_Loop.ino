/* 
 *  Team: Austin Gnecco, Daniel Maas, Jessica Pearson, Saket Shanmugam
 *  
 *  Goal: to utilize IF...then...ELSE program to command the CP bot to move 
 *  forward repeatedly tracing out the 4 sides of the square path only if the 
 *  left joystick is pushed forward. If the joystick is not pushed forward, stop the motor,
 *  light the LED for 1/2 seconds before checking the joystick again.
 */

void setup() {
  int joystick_value = map(analogRead(A0), 0, 1023, 0, 255);
  
  //right motor
  int right1 = 4;
  int right2 = 5;
  //left motor
  int left1 = 7;
  int left2 = 6;
  //motor power
  int power = 255;
  
  //led
  int led_pin = 13;
  
  pinMode(left_joystick, INPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (A0 < joystick_value) { 
   //complete a square if the joystick is moved
   Trace1Side();
   PivotRight();
   Trace1Side();
   PivotRight();
   Trace1Side();
   PivotRight();
   Trace1Side();
   PivotRight();
  }
  else {
   //if the joystick isn't moving the LED will flash for 1/2 a second
   FlashLED();
   delay (3000);
  }

  void Trace1Side() {
    analogWrite(right1, power);
    analogWrite(right2, 0);
    analogWrite(left1, power);
    analogWrite(left2, 0);
    delay(1000);
  }

  void PivotRight () {
    analogWrite(right1, power);
    analogWrite(right2, 0);
    delay(255);
  }

  void FlashLED () {
    digitalWrite(led_pin, HIGH);
    delay (500); 
    digitalWrite(led_pin, LOW);
    delay (500); 
  }

}
