
#ifndef SCREEN_H
#define SCREEN_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "pinout.h"

enum screenDataType {
    SCREEN_DATA_WIFI_CONNECTION = 0,
    SCREEN_DATA_WIFI_IP,
    SCREEN_DATA_STATUS_INFO,
    SCREEN_DATA_BATT_VOLTAGE,
    SCREEN_DATA_LEN
};

const uint8_t screenDataLen = 50;

void screenInit(void);
void screenAnimateParrot(void);
void screenDisplayData(screenDataType dataType, char *data);
void screenTask(void);

#endif /* SCREEN_H */