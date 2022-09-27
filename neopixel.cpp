#include "neopixel.h"
#include <Adafruit_NeoPixel.h>

static const uint8_t NUMPIXELS = 5;

typedef enum color {
    COLOR_RED = 0,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_LEN
} neopixelColor_t;

static Adafruit_NeoPixel neopixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void neopixelInit(void) {
    pinMode(BUTTON_PIN, INPUT);
    neopixels.begin();
}

void neopixelTask(void) {
    static const uint32_t neopixelUpdatePeriod_ms = 100;
    static uint32_t lastUpdateTime_ms = 0;
    static int previousButtonState = LOW;
    static neopixelColor_t ledColor = COLOR_RED;
    uint32_t currentTime_ms = millis();
    if (lastUpdateTime_ms + neopixelUpdatePeriod_ms <= currentTime_ms) {
        int buttonState = digitalRead(BUTTON_PIN);
        if (buttonState != previousButtonState && buttonState == HIGH)
        {
            const int i = static_cast<int>(ledColor);
            ledColor = static_cast<neopixelColor_t>((i + 1) % static_cast<int>(COLOR_LEN));
        }
        previousButtonState = buttonState;

        neopixels.clear();
        for(uint8_t i=0; i<NUMPIXELS; i++) {
            if (ledColor == COLOR_RED) {
                neopixels.setPixelColor(i, neopixels.Color(150, 0, 0));
            } else if (ledColor == COLOR_GREEN) {
                neopixels.setPixelColor(i, neopixels.Color(0, 150, 0));
            } else {
                neopixels.setPixelColor(i, neopixels.Color(0, 0, 150));
            }
        }
        neopixels.show();
        lastUpdateTime_ms = currentTime_ms;
  }
}