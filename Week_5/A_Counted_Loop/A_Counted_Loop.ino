/* 
   Austin Gnecco, Danny Maas, Jessica Pearson, Saket Shanmugam
   Program: For Four Squared Loop-the-Loop
   Goal: Use a for loop in order to trace a square, then pause after
   each square trance and flash the LED for three seconds.
*/

int motorA1 = 4; // IN1 (Motor A)
int motorA2 = 5; // IN2 (Motor A)
int motorB1 = 7; // IN3 (Motor B)
int motorB2 = 6; // IN4 (Motor B)
int LED = 13; // LED pin

void setup()
{
 pinMode(motorA1, OUTPUT);
 pinMode(motorA2, OUTPUT);
 pinMode(motorB1, OUTPUT);
 pinMode(motorB2, OUTPUT);
 pinMode(LED,OUTPUT);

 //Repeat this four times:
 for(int i = 0;i<4;i++)
 {
  //Move Forwards
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  delay(1000);

  //Stop motors temporarily before turning
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB1, LOW);
  delay(100);
  
  //Turn
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorB2, HIGH);
  delay(250);

  //Stop Motors before continuing
  digitalWrite(motorA1, LOW);
  digitalWrite(motorB2, LOW);
  delay(100);
  }
  
  //Flash LED, pause for 3 seconds
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(2000);
}

void loop()
{
 
}
