#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "server.h"
#include "drivetrain.h"

static const char* ssid = "CMU-DEVICE";
static const char* password = "";

static ESP8266WebServer server(80);

void handlerFunction() {
    const String dtype = server.arg("dtype");

    if (dtype == "speed") {
        drivetrainSetSpeed((uint8_t) server.arg("speed").toInt());
    } else if (dtype == "rgbi") {
        const String r_s = server.arg("r");
        const String g_s = server.arg("g");
        const String b_s = server.arg("b");
        const String index_s = server.arg("index");
        Serial.println(index_s);
        int index = index_s.toInt();
        int red = r_s.toInt();
        int green = g_s.toInt();
        int blue = b_s.toInt();
    }

    server.send(200, "text/html", "");
    Serial.println("Recieved POST request...");
}

void serverInit(void) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print('.');
    }
}

void serverTask(void) {
    static bool serverStarted = false;
    if ((WiFi.status() == WL_CONNECTED) && (serverStarted == false)) {
        Serial.print("Connected to:\t");
        Serial.println(ssid);
        Serial.print("IP address:\t");
        Serial.println(WiFi.localIP());
        server.on("/", handlerFunction);
        server.begin();
        serverStarted = true;
    } else if ((WiFi.status() == WL_CONNECTED) && (serverStarted == true)) {
        server.handleClient();
    }
}