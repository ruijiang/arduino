
#include <Servo.h>

enum ServoIndex {
  FRONT_LEFT_HIP = 0,
  FRONT_LEFT_KNEE = 1,
  FRONT_RIGHT_HIP = 2,
  FRONT_RIGHT_KNEE = 3,
  
  REAR_LEFT_HIP = 4,
  REAR_LEFT_KNEE = 5,
  REAR_RIGHT_HIP = 6,
  REAR_RIGHT_KNEE = 7
};

int servoConfigs[8][4] = {
  {13, 50, -1,  45},  // FRONT_LEFT_HIP
  {12, 5, 1,    50},    // FRONT_LEFT_KNEE
  {11, 120, 1,  50},  // FRONT_RIGHT_HIP
  {10, 150, -1, 45}, // FRONT_RIGHT_KNEE
  
  {9, 115, -1,  45}, // REAR_LEFT_HIP
  {8, 20, 1,    50},   // REAR_LEFT_KNEE
  {7, 35, 1,    45},   // REAR_RIGHT_HIP
  {6, 150, -1,  50}, // REAR_RIGHT_KNEE
};

const int STEPS = 10;
int walks[][STEPS] = {
  // FRONT_LEFT_HIP
  {0, -20, 0, 20, 20,    0, 0, 0, 0, 0},
  // FRONT_LEFT_KNEE
  {0, -20, -20, -20, 0,  0, 0, 0, 0, 0},
  // FRONT_RIGHT_HIP
  {0, 0, 0, 0, 0,    0, -20,  0,   20, 20},
  // FRONT_RIGHT_KNEE
  {0, 0, 0, 0, 0,    0, -20, -20, -20, 0},

  // REAR_LEFT_HIP
  {0, 0, 0, 0, 0,       0, -20, 0, 20, 20},
  // REAR_LEFT_KNEE
  {0, 0, 0, 0, 0,       0, -20, -20, -20, 0},
  // REAR_RIGHT_HIP
  {0, -20, 0, 20, 20,   0, 0, 0, 0, 0},
  // REAR_RIGHT_KNEE
  {0, -20, -20, -20, 0, 0, 0, 0, 0, 0},
};

Servo servos[8];

void setup() {
  for (int i = 0; i < 8; i++) {
    servos[i].attach(servoConfigs[i][0]);
  }
  for (int i = 0; i < 8; i++) {
    writeServoAdjust(i, 0);
  }
}

void writeServo(int servo, int degree) {
  servos[servo].write(servoConfigs[servo][1] + servoConfigs[servo][2] * degree);
}

void writeServoAdjust(int servo, int degree) {
  writeServo(servo, servoConfigs[servo][3] - degree);
}

int interval = 30;

void simpleMove() {
  for (int d = 0; d < 20; d++) {
    for (int i = 0; i < 8; i++) {
      writeServo(i, servoConfigs[i][3] - d);
    }
    delay(interval);
  }
  for (int d = 20; d > 0; d--) {
    for (int i = 0; i < 8; i++) {
      writeServo(i, servoConfigs[i][3] - d);
    }
    delay(interval);
  }  
}

const int INTERVAL = 10;
void moveFLRR() {
  for (int i = 0; i < STEPS; i++) {
    for (int k = 0; k < INTERVAL; k++) {
      for (int si = 0; si < 8; si++) {
        int currentDegree = walks[si][i];
        int nextDegree;
        if (i + 1 == STEPS) {
          nextDegree = walks[si][0];
        } else {
          nextDegree = walks[si][i + 1];            
        }
        int degree = currentDegree + (nextDegree - currentDegree) * k / INTERVAL;
        writeServoAdjust(si, degree);
      }
      delay(20);
    }
  }
}

void calibrate() {
  for (int i = 0; i < 8; i++) {
    writeServoAdjust(i, 0);  
  }
  delay(20);
}

void loop() {
  //calibrate();
  //simpleMove();
  moveFLRR();
  return;
}
