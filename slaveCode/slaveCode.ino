#include <Wire.h>
#include <Servo.h>

// Slave code to run animations

//void bowtie();
void arms();

  Servo a;
  Servo b;

void setup() 
{
  a.attach(12);
  b.attach(8);
  //pinMode(10, OUTPUT);
  
  Serial.begin(19200);
  Serial.println("Output Initialized");
  Wire.begin(4);
  Serial.println("Setup on AR 4");
  Wire.onReceive(recieveEvent);
}

void recieveEvent(int message)
{
  Serial.println("Character Recieved :");
  Serial.print(message);
  // Does not seem to work. Technically the other board says that the 
  // message was sent, but this board did not recieve any data, therefore,
  // I conclude this method will not satisfy the time requirements.
}

void arms()
{
  a.write(165);
  delay(500);
  b.write(165);
  delay(500);
  a.write(90);
  delay(500);
  b.write(90);
  delay(10000);
//  for(int i; i < 200000; i++){
//  analogWrite(10,100);
//  }
}
void bowtie()
{
  //analogWrite(10, 70);
}
  
void loop() 
{
 delay(100);
 arms();
}
