#include "pinout.h"
#include "screen.h"
#include "neopixel.h"
#include "drivetrain.h"
#include "server.h"

// Heartbeat Task
void heartbeatTask(void) {
    static uint32_t lastBlink_ms = 0;
    static const uint32_t blinkPeriod_ms = 250;
    uint32_t currentTime_ms = millis();
    if (lastBlink_ms + blinkPeriod_ms <= currentTime_ms) {
        digitalWrite(HEARTBEAT_PIN, !digitalRead(HEARTBEAT_PIN));
        lastBlink_ms = currentTime_ms;
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(HEARTBEAT_PIN, OUTPUT);
    pinMode(ELECTROMAGNET_PIN, OUTPUT);
    digitalWrite(ELECTROMAGNET_PIN, LOW);

    screenInit();
    neopixelInit();
    drivetrainInit();
    serverInit();
}

void loop() {
    screenTask();
    serverTask();
    heartbeatTask();
    neopixelTask();
    drivetrainTask();
}
