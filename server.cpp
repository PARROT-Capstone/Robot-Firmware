#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "server.h"
#include "screen.h"
#include "drivetrain.h"
#include "neopixel.h"

// modified from https://randomnerdtutorials.com/esp8266-web-server/

static const char* ssid = "CMU-DEVICE";
static const char* password = "";

static ESP8266WebServer server(80);

void handlerFunction() {
    const String dtype = server.arg("dtype");

    if (dtype == "speed") {
        drivetrainSetSpeed((uint8_t) server.arg("servo1").toInt(),
                           (uint8_t) server.arg("servo2").toInt());
    } else if (dtype == "pallet") {
        int pallet = server.arg("power").toInt();
        if (pallet == HIGH) {
            digitalWrite(ELECTROMAGNET_PIN, HIGH);
        } else {
            digitalWrite(ELECTROMAGNET_PIN, LOW);
        }
    } else if (dtype == "robotNumber") {
        neopixelSetRobotNumber((uint8_t) server.arg("robotNumber").toInt());
    }

    server.send(200, "text/html", "");
}

void serverInit(void) {
    pinMode(ELECTROMAGNET_PIN, OUTPUT);
    digitalWrite(ELECTROMAGNET_PIN, LOW);

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED) {
        screenAnimateParrot();
        delay(75);
    }
    char wifiInfo[screenDataLen];
    sprintf(wifiInfo, "WiFi: %s", ssid);
    screenDisplayData(SCREEN_DATA_WIFI_CONNECTION, wifiInfo);
    char ipInfo[screenDataLen];
    sprintf(ipInfo, "IP: %s", WiFi.localIP().toString().c_str());
    screenDisplayData(SCREEN_DATA_WIFI_IP, ipInfo);
    server.on("/", handlerFunction);
    Serial.println(WiFi.localIP());
    server.begin();
}

void serverTask(void) {
    server.handleClient();
}
