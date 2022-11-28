#include <Servo.h>
#include "drivetrain.h"

static const uint8_t zeroSpeed = 90;
static const uint8_t maxSpeed = 180;

static Servo servo1;
static Servo servo2;

static volatile uint32_t lastServoTime_ms;
static volatile bool servosAttached = false;
static const uint32_t servoTimeout_ms = 1000;

void drivetrainSetSpeed(uint8_t speed1, uint8_t speed2) {
    // Store current time
    lastServoTime_ms = millis();

    if (!servosAttached) {
        servo1.attach(SERVO1_PIN);
        servo2.attach(SERVO2_PIN);
        servosAttached = true;
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
    servosAttached = true;

    servo1.write(zeroSpeed);
    servo2.write(zeroSpeed);
}

void drivetrainTask(void) {
    // Detach servos if hasn't received command in a while
    uint32_t currentTime_ms = millis();
    if (lastServoTime_ms + servoTimeout_ms <= currentTime_ms && servosAttached) {
        servo1.write(zeroSpeed);
        servo2.write(zeroSpeed);
        servo1.detach();
        servo2.detach();
        servosAttached = false;
    }
}
