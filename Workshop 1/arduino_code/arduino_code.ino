#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
// variables to store our basic servo positions : up, stirring high, stirring low
int UP = 0;    // when the tea is lifted out of the cup
int STIR_HIGH = 140; // high position for stirring
int STIR_LOW = 90; // low position for stirring

// Delay between each servo position adjustment during stirring. 
// A lower value is associated with a quicker stirring.
int STIR_SMOOTH = 50;
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{ 
/*	if (Serial.available()) {
		int pos = Serial.read();
		myservo.write(pos);
	}
*/
stir();
} 

void stir() {
/*
We tell the servo to go from the STIR_HIGH to the STIR_LOW position, 
with a delay between each adjustment of position so that the movement is smooth.
*/ 
int pos;

  for(pos = STIR_HIGH; pos >= STIR_LOW; pos -= 1) // goes from STIR_HIGH to STIR_LOW
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(STIR_SMOOTH);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = STIR_LOW; pos <= STIR_HIGH; pos += 1)     // goes from STIR_LOW to STIR_HIGH
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(STIR_SMOOTH);                       // waits 15ms for the servo to reach the position 
  } 
}
