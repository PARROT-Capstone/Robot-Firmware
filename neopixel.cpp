#include <Adafruit_NeoPixel.h>
#include "neopixel.h"
#include "screen.h"

typedef enum color {
    COLOR_ONE,
    COLOR_TWO,
    COLOR_THREE,
    COLOR_FOUR,
    COLOR_FIVE,
    COLOR_SIX,
    COLOR_SEVEN,
    COLOR_EIGHT,
    COLOR_NINE,
    COLOR_LEN
} neopixelColor_t;

static const uint8_t NUMPIXELS = 5;
static const float LED_PEAK_BRIGHTNESS = 5.0f; // normalization constant

// Random distinct colors generated from https://mokole.com/palette.html
static const uint32_t LED_COLORS[COLOR_LEN][3] = {
    {85, 107, 47},
    {25, 25, 112},
    {255, 69, 0},
    {255, 215, 0},
    {0, 255, 0},
    {0, 191, 255},
    {0, 191, 255}, 
    {255, 20, 147},
    {255, 0, 0}
}; 

static Adafruit_NeoPixel neopixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
static volatile neopixelColor_t ledColor = COLOR_ONE;

// Random distinct colors generated from https://mokole.com/palette.html
void showNewColor(void) {
    neopixels.clear();
    for(uint8_t i=0; i<NUMPIXELS; i++) {
        float normalizationFactor = LED_PEAK_BRIGHTNESS / (float) (LED_COLORS[ledColor][0] + LED_COLORS[ledColor][1] + LED_COLORS[ledColor][2]);
        switch(ledColor) {
            case COLOR_ONE:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_ONE][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_ONE][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_ONE][2]));
                break;
            case COLOR_TWO:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_TWO][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_TWO][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_TWO][2]));
                break;
            case COLOR_THREE:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_THREE][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_THREE][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_THREE][2]));
                break;
            case COLOR_FOUR:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_FOUR][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_FOUR][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_FOUR][2]));
                break;
            case COLOR_FIVE:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_FIVE][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_FIVE][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_FIVE][2]));
                break;
            case COLOR_SIX:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_SIX][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_SIX][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_SIX][2]));
                break;
            case COLOR_SEVEN:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_SEVEN][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_SEVEN][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_SEVEN][2]));
                break;
            case COLOR_EIGHT:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_EIGHT][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_EIGHT][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_EIGHT][2]));
                break;
            case COLOR_NINE:
                neopixels.setPixelColor(i, neopixels.Color(normalizationFactor * LED_COLORS[COLOR_NINE][0], 
                                                           normalizationFactor * LED_COLORS[COLOR_NINE][1], 
                                                           normalizationFactor * LED_COLORS[COLOR_NINE][2]));
                break;
            default:
                break;
        }
    }
    neopixels.show();
}

void displayRobotInfo(void) {
    char robotInfo[screenDataLen];
    sprintf(robotInfo, "Robot %d", static_cast<int>(ledColor));
    screenDisplayData(SCREEN_DATA_STATUS_INFO, robotInfo);
    showNewColor();
}

void neopixelInit(void) {
    pinMode(BUTTON_PIN, INPUT);
    neopixels.begin();
    displayRobotInfo();
}

void neopixelSetRobotNumber(uint8_t number) {
    if (number < COLOR_LEN) {
        ledColor = static_cast<neopixelColor_t>(number);
        displayRobotInfo();
    }
}

void neopixelTask(void) {
    static const uint32_t neopixelUpdatePeriod_ms = 100;
    static uint32_t lastUpdateTime_ms = 0;
    static int previousButtonState = HIGH;
    uint32_t currentTime_ms = millis();
    if (lastUpdateTime_ms + neopixelUpdatePeriod_ms <= currentTime_ms) {
        int buttonState = digitalRead(BUTTON_PIN);
        if (buttonState != previousButtonState && buttonState == HIGH)
        {
            const int i = static_cast<int>(ledColor);
            ledColor = static_cast<neopixelColor_t>((i + 1) % static_cast<int>(COLOR_LEN));
            displayRobotInfo();
        }
        previousButtonState = buttonState;
        lastUpdateTime_ms = currentTime_ms;
  }
}
