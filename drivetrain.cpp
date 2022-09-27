#include <Servo.h>
#include "drivetrain.h"

static Servo servo1;
static Servo servo2;

static volatile uint8_t speed = 90;

void drivetrainSetSpeed(uint8_t newSpeed) {
    if (newSpeed > 180) {
        speed = 90;
    } else {
        speed = newSpeed;
    }
}

void drivetrainInit(void) {
    servo1.attach(SERVO1_PIN);
    servo2.attach(SERVO2_PIN);

    servo1.write(speed);
    servo2.write(180-speed);
}

void drivetrainTask(void) {
    servo1.write(speed);
    servo2.write(180-speed);
}