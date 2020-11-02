/*
 * Use an ultrasound distance detector to avoid obstacle.
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val = 0;    // variable to read the value from the analog pin
int motorpin = 10;

#define enA 9
#define enB 10
#define in1 4
#define in2 5
#define in3 6
#define in4 7
#define button 4
#define pin 13

const int trigPin = 10;
const int echoPin = 11;

// defines variables
long duration;
int distance;

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(button, INPUT);
  pinMode(pin, OUTPUT);   
  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Ultrasonic sensor.
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input  
  Serial.begin(9600);
}

double readDis() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

void moveForward() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);  
}

void moveBackward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH); 
    delay(200);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
    delay(300);
}

void stop() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);   
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);   
}

void makeNoise() {
  for (int i = 0; i < 100; i++) {
    digitalWrite(pin, LOW);
    delay(2);
    digitalWrite(pin, HIGH);
    delay(2);
  }
}

void loop() {
  int pwmOutput = 128; // map(potValue, 0, 1023, 0 , 255); // Map the potentiometer value from 0 to 255
  analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
  analogWrite(enB, pwmOutput); // Send PWM signal to L298N Enable pin

  double dis = readDis();
  if (dis < 30) {
    stop();
    makeNoise();
    moveBackward();
    // delay(1000);                           // waits for the servo to get there
  } else {
    moveForward();  
    delay(300);                           // waits for the servo to get there    
  } 

  int pause = 0;
  if (pause) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    delay(300);
  }
}
