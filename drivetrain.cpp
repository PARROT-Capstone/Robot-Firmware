#include <Servo.h>
#include "drivetrain.h"

static const uint8_t zeroSpeed = 90;
static const uint8_t maxSpeed = 180;

static Servo servo1;
static Servo servo2;

void drivetrainSetSpeed(uint8_t speed1, uint8_t speed2) {
    // primitive speed clamping 
    speed1 = min(max(speed1, zeroSpeed), maxSpeed);
    speed2 = min(max(speed2, zeroSpeed), maxSpeed);

    // turn off the servos with zero speed
    if (speed1 == zeroSpeed) {
        servo1.detach();
    } else {
        servo1.attach(SERVO1_PIN);
    }

    if (speed2 == zeroSpeed) {
        servo2.detach();
    } else {
        servo2.attach(SERVO2_PIN);
    }


    char debugStr[50];
    sprintf(debugStr, "Speed1, Speed2:\t %d, %d\n", speed1, speed2);
    Serial.println(debugStr);

    servo1.write(speed1);
    servo2.write(speed2);
}

// not needed since this will attach and then detach the servos instantly
// but it's here for completeness
void drivetrainInit(void) {
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);

    servo1.write(zeroSpeed);
    servo2.write(zeroSpeed);
}

void drivetrainTask(void) {
}
