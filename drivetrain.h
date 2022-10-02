#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "pinout.h"

void drivetrainInit(void);
void drivetrainTask(void);

void drivetrainSetSpeed(uint8_t speed1, uint8_t speed2);

#endif /* DRIVETRAIN_H */