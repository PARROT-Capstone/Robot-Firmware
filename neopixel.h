#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include "pinout.h"

void neopixelInit(void);
void neopixelSetRobotNumber(uint8_t number);
void neopixelTask(void);

#endif /* NEOPIXEL_H */