
#ifndef SCREEN_H
#define SCREEN_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "pinout.h"

void screenInit(void);
void screenTask(void);

#endif /* SCREEN_H */