#include <Servo.h>
#include <Wire.h>
#include "car.h"

/*
  Written by Michael Nugyen and Elston Almeida
  Grade 12 Computer Enginnering CPT
  Wall Tracing Robot

  Using Car library

  Note: Change the include statement in car.cpp to your Arduino.h.

  Commands:

  USSetup(t,p)

  t - trigger pin
  p - echo pin

  MotorSetup(lp,ln,rp,rn)

  lp - left motor positive
  ln - left motor negative

  rp - right motor positive
  rn - right motor negative

  forward()

  No arguments, moves car forward for 1000 ms or 1 second

  reverse()

  No arguments, moved card back for 1000 ms or 1 second

  distance()

  No arguments, returns only positive values of distance recorded
  from the ultrasonic sensor

  turn(x, n)

  Inverses the motors to provide a sharp turn

  x - the direction to turn, uses a bool value.

  true  -> left
  false -> right

  n - the amount of time spent turning

  turnH(x, n)

  Truns one motor off and the other turns

  Same arguments as turn(x,n)
*/

// pin number ints
#define trigPin 4
#define echoPin 3
#define leftMotorP 9
#define leftMotorN 10
#define rightMotorP 7
#define rightMotorN 8

// For ease of use, the words "left" and "right" are changed to boolean values . 
// This is to use the turn functions from the car class
#define left true
#define right false

Car car(9600, 13);

// increment timer
int t(0);

// Forward declaration
void moveAround();

// Create the variable s that inherits the servo class
Servo s;

void setup()
{
  car.USSetup(trigPin, echoPin);
  car.MotorSetup(leftMotorP, leftMotorN, rightMotorP, rightMotorN);
  s.attach(11);
  s.write(165);
  Serial.begin(19200);
  delay(1000);
  car.BeginAnimation();
  car.beep(12);
}

void loop()
{
  /* The car has to be able to look forward and determine any obstacles, this means that a timer is required to be
     implimented, rather than using a built in library to handle timing, the timing is going to be done automatically
     variant on the loop timings, the loops will increment timer "t" and every time t > n.
     The car will turn servo 90 degrees and do its checks and then preform its respected tasks.
  */

  t++;

  // Every two iterations of the loop run run look forward
  if (t == 2)
  {
    t = 0;
    s.write(90);
    delay(1000);

    // If the distance is less than 50cm in the front, try and move arround object.
    // Additionally beep to identify an obsticle
    if (car.distance() < 50)
    {
      car.printc("playing tone");
      car.beep(12);
      moveAround();
    }
    s.write(165);
    delay(1000);
  }

  // The following code below has all been documented above

  // car is too close
  if (car.distance() < 50)
  {
    car.turn(right, 1000);
    car.forward();
    car.turn(left, 750);
  }

  // car is almost out of range
  if ( car.distance() > 100 && car.distance() < 120)
  {
    car.turn(left, 750);
    car.forward();
    car.turn(right, 200);
  }

  // car is out of range, turn left
  if (car.distance() > 120)
  
  {
    s.write(120);
    delay(1000);
    if (car.distance() < 30)
    {
      car.reverse();
      car.turn(right, 2000);
      car.forward();
      car.forward();
    }
    s.write(165);
    delay(1000);
    car.turn(left, 1200);
    car.forward();
  }

  // Car is in range
  if (50 < car.distance() < 100)
  {
    car.forward();
  }
}

/*
 * The car will read the distance to the left or right
 * and it will the move to the side where there is more distance
 * as called by the distance function.
 * when there is a person in front of the car the car will beep
 * and will try to move around the person.
 * 
 * Reclusive function : MAKE SURE NOT TO CREATE AN INFINITE LOOP
 */
 void moveAround() 
 {
  // Create throwaway variable called testing for the comparison of the distances on either side of the car
  int testing;

  // Check the right side of the car
  s.write(8);
  delay(1000);
  
  // Save the distance to the right to the throwaway value
  testing = car.distance();
  
  // Check the left side of the car
  s.write(165);
  delay(1000);
  
  // Compare the distance from the left side of the car to the right side.
  // Check which one is larger and move towards the direction where there is more distance
  if (car.distance() > testing)
  {
    // Move left if the distance to the left is greater than the right
    car.turn(left, 1000);
    car.forward();
  }
  else 
  {
    // Move right if the distance is greater to the right
    car.turn (right, 1000);
    car.forward();
  }
  // Once again check if there is any object directly in front about 30cm away.
  s.write(90);
  delay(1000);
  if (car.distance() < 30)
  {
    // Calls itself again to move arround the object infront
    tone(12,494,300);
    moveAround();
  }
}
