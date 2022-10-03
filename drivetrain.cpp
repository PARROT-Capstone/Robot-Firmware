#include <Servo.h>
#include "drivetrain.h"

static const uint8_t zeroSpeed = 90;
static const uint8_t maxSpeed = 180;

static Servo servo1;
static Servo servo2;

void drivetrainSetSpeed(uint8_t speed1, uint8_t speed2) {
    if (speed1 > maxSpeed) {
        speed1 = zeroSpeed;
    }
    if (speed2 > maxSpeed) {
        speed2 = zeroSpeed;
    }
    char debugStr[50];
    sprintf(debugStr, "Speed1, Speed2:\t %d, %d\n", speed1, speed2);
    Serial.println(debugStr);

    servo1.write(speed1);
    servo2.write(speed2);
}

void drivetrainInit(void) {
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);

    servo1.write(zeroSpeed);
    servo2.write(zeroSpeed);
}

void drivetrainTask(void) {
}
