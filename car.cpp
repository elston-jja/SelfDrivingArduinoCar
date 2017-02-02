#include "car.h"
#include "/usr/share/arduino/hardware/arduino/avr/cores/arduino/Arduino.h"
#include <Wire.h>
/*
  Car Class
  by Elston
*/


//  Initialize the class
Car::Car(int baud, int servoPin)
{
	Serial.begin(baud);
	servo = servoPin;
}

/*
  Ultrasonic sensor setup
  Saves the trig and echo pins for the class
  initializes the pins from the class as output and input respectively
*/
void Car::USSetup(int trigPin, int echoPin)
{
	tp = trigPin;
	ep = echoPin;
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	Serial.print("Ultra Sonic Sensor Initialized");
}

/*
  Motor setup
  Gets the pins for the left motor and the right motor
  saves the pins in the object and then initializes the pins as outputs
 */
void Car::MotorSetup(int leftMotorP, int leftMotorN, int rightMotorP, int rightMotorN)
{
	lP = leftMotorP;
	lN = leftMotorN;
	rP = rightMotorP;
	rN = rightMotorN;
	
	int pins[4] = {lP,lN,rP,rN};

	for ( int i; i < 4 ; i++ )
    {
		pinMode(pins[i], OUTPUT);
    }

	Serial.print("Motors Initialized");
}

int Car::distance()
{
    int duration(0), distance(0);
	digitalWrite(tp, HIGH);
	delayMicroseconds(1000);
	digitalWrite(tp, LOW);
	duration = pulseIn(ep, HIGH);
	distance = (duration /2) / 29.2;
	if (distance > 0)
    {
		return (distance);
    }
	return(0);
}

void Car::forward()
{
  digitalWrite(rP, HIGH);
  digitalWrite(lP, HIGH);
  delay(1000);
  digitalWrite(rP, LOW);
  digitalWrite(lP, LOW);
}

 void Car::reverse()
{
  digitalWrite(rN, HIGH);
  digitalWrite(lN, HIGH);
  delay(1000);
  digitalWrite(rN, LOW);
  digitalWrite(lN, LOW);
}


void Car::turn(bool direction, int duration)
{
  //rotate and reverse rotate each wheel respectivly
	// go left
	if (direction)
    {
      digitalWrite(rP, HIGH);
      digitalWrite(lN, HIGH);
      delay(duration);
      digitalWrite(rP, LOW);
      digitalWrite(lN, LOW);
      
    }
  //rotate right
  else
    {
      digitalWrite(rN, HIGH);
      digitalWrite(lP, HIGH);
      delay(duration);
      digitalWrite(rN, LOW);
      digitalWrite(lP, LOW);
    }
}

void Car::turnH(bool direction, int duration)
{	
  //rotate ONLY one wheel
  if (direction)
    {
      //turn left
      digitalWrite(rP, HIGH);
      delay(duration);
      digitalWrite(rP, LOW);
    }
  else
    {
      //turn right
      digitalWrite(lP, HIGH);
      delay(duration);
      digitalWrite(lP, LOW);
    }
}

void Car::BeginAnimation()
{
	Wire.begin();
  Wire.beginTransmission(4);
  int message = 1;
  Wire.write(message);
  Wire.endTransmission();
}

void Car::printc(char* printedstring)
{
  Serial.print(printedstring);
}

void Car::beep(int pin)
{
  tone(pin, 494, 300);
}

