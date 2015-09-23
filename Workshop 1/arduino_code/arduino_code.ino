#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
// variables to store our basic servo positions : up, stirring high, stirring low
const int UP = 0;    // when the tea is lifted out of the cup
const int STIR_HIGH = 140; // high position for stirring
const int STIR_LOW = 90; // low position for stirring

// Delay between each servo position adjustment during stirring
// A lower value is associated with a quicker stirring
int STIR_SMOOTH = 50;

const int STATUS_LED = 4; // Used to indicate that stirring is in progress
const int POWER_LED = 5; // Always on when the Arduino is powered

const int BUTTON = 6; // Starts stirring when pressed

const int TIME_POT = A5;
int stir_time;

const int BUZZER = 8; // Used to indicate end of stirring. Needs to be a PWM pin.
 
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
	
	Serial.println(getStirringTime());
	delay(1000);
	
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
	return (digitalRead(BUTTON) ? false : true);
}

void beepBuzzer() {
/*
To indicate the end of stirring, we play a G7(sol) twice for 1 second with a 2 second intermission.
*/
	tone(BUZZER, 3136, 1000);
	delay(2000);
	tone(BUZZER, 3136, 1000);
}

long getStirringTime() {
/*
Get analog value from potentiometer (range 0-1023), re-base between 0 and 10 and multiply by 60*1000 to get the time in milliseconds.
*/
	float time = mapFloat(analogRead(TIME_POT), 0, 1023, 0, 10);
	long millisTime = (long)(time*60*1000);
	return millisTime;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
/*
Helper function used to re-map an number from one range to another. We don't use the native 'map' because it only returns integers. 
*/
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}