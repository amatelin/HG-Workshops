#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
// variables to store our basic servo positions : up, stirring high, stirring low
int UP = 0;    // when the tea is lifted out of the cup
int STIR_HIGH = 140; // high position for stirring
int STIR_LOW = 90; // low position for stirring

// Delay between each servo position adjustment during stirring
// A lower value is associated with a quicker stirring
int STIR_SMOOTH = 50;

int STATUS_LED = 4; // Used to indicate that stirring is in progress
int POWER_LED = 5; // Always on when the Arduino is powered

int TIMER_BUTTON = 6; // Used to increment the stirring time
int stir_time; 

int BUZZER = 10;
 
void setup() 
{ 
  myservo.attach(3);  // attaches the servo on pin 3 to the servo object 
  
  pinMode(STATUS_LED, OUTPUT);
  pinMode(POWER_LED, OUTPUT);
  digitalWrite(POWER_LED, HIGH);
  digitalWrite(STATUS_LED, LOW);
  
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  Serial.begin(9600);
} 
 
void loop() 
{ 
	/*if (Serial.available()) {
		int pos = Serial.read();
		myservo.write(pos);
	}*/

	// digitalWrite(STATUS_LED, HIGH);
	// stir();
	// digitalWrite(STATUS_LED, LOW);
	digitalWrite(STATUS_LED, HIGH);
	if (isButtonPressed()) {
		stir_time++;
		Serial.println(stir_time);
		delay(500);
	}
	
	
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

bool isButtonPressed() {
/*
When the button is pressed, the TIMER_BUTTON pin is connected to ground and thus reads LOW.
Alternatively, when the button is not pressed the pin is connected to 5v through the resistor and reads HIGH
*/
	return (digitalRead(TIMER_BUTTON) ? false : true);
}

void beepBuzzer() {
/*
To indicate the end of stirring, we play a G7(sol) twice for 1 second with a 2 second intermission.
*/
	tone(pinOut, 3136, 1000);
	delay(2000);
	tone(pinOut, 3136, 1000);
}