#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "server.h"
#include "screen.h"
#include "drivetrain.h"

static const char* ssid = "Fios-T9wDR";//"CMU-DEVICE";
static const char* password = "bland94toy84bun";//"";

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
        int index = index_s.toInt();
        int red = r_s.toInt();
        int green = g_s.toInt();
        int blue = b_s.toInt();
    }

    server.send(200, "text/html", "");
}

void serverInit(void) {
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
    server.begin();
}

void serverTask(void) {
    // static bool serverStarted = false;
    // if (serverStarted == false) {
        
    //     serverStarted = true;
    // } else {
        server.handleClient();
    // }
}