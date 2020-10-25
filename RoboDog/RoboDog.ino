
#include <Servo.h>

Servo servo1, servo2;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  servo1.attach(10);  // attaches the servo on pin 9 to the servo object
  servo2.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (int i = 120; i > 0; i--) {
    servo1.write(i);
    servo2.write(180 - i);
    delay(10);
  }
}
