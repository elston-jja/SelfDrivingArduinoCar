#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED
#include <Servo.h>
/*
  functions for CAR
*/

class Car
{
public:
	// 
	Car(int baud, int servoPin);

	// setup for sensor and motors
	void USSetup(int trigPin, int echoPin);
	
	void MotorSetup(int leftMotorP, int LeftMotorN, int rightMotorP, int rightMotorN);

	// Sensor control
	void sensor(int angle);
	
	// Motor Control
	void forward();
	void reverse();
	
	int distance();

	void turn(bool direction, int duration);
	void turnH(bool direction, int duration);

	void BeginAnimation();

  void printc(char* printedstring);

  void beep(int pin);
private:

	// Setup Servo as type
	//Servo e;
	/*
  This will save the values for the positve and negative pins
  for the right and left motors, this is saved to be called 
  in the motor control functions
*/
	int lP, lN, rP, rN;
	// ultrasonic sensor pins (trig and echo)
	int tp, ep;
	// Servo pin
	int servo;
  
	char* printedstring;
};
#endif
