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

// Voltage Sense Task
void voltageSenseTask(void) {
    static uint32_t lastSample_ms = 0;
    static const uint32_t samplePeriod_ms = 1000;
    uint32_t currentTime_ms = millis();
    if (lastSample_ms + samplePeriod_ms <= currentTime_ms) {
        // 10-bit ADC reading from 0 to 1V
        const uint32_t maxADCValue = (1 << 10);
        const uint32_t R1 = 560;
        const uint32_t R2 = 300;
        const uint32_t R3 = 220;
        const uint32_t R4 = 100;
        const uint32_t Rparallel = R2 * (R3 + R4) / (R2 + R3 + R4);
        const uint32_t voltsPerMillivolt = 1000;
        uint32_t adcValue = analogRead(A0);
        uint32_t espVoltage_mV = adcValue * voltsPerMillivolt * (R3 + R4) / R4 / maxADCValue;
        uint32_t battVoltage_mV = espVoltage_mV * (R1 + Rparallel) / Rparallel;
        char battInfo[screenDataLen];
        sprintf(battInfo, "Battery: %d mV", battVoltage_mV);
        screenDisplayData(SCREEN_DATA_BATT_VOLTAGE, battInfo);
        lastSample_ms = currentTime_ms;
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(HEARTBEAT_PIN, OUTPUT);

    screenInit();
    neopixelInit();
    drivetrainInit();
    serverInit();
}

void loop() {
    screenTask();
    serverTask();
    heartbeatTask();
    voltageSenseTask();
    neopixelTask();
    drivetrainTask();
}
