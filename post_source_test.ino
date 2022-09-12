/**
   PostHTTPClient.ino
    Created on: 21.11.2016
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// Create the server on port 80
ESP8266WebServer server(80); //creating the server at port 80

bool recieved = false;

//#define SERVER_IP "10.0.1.7:9080" // PC address with emulation on host
#define OTHER_NODE_IP "1720.126.170.242"

#ifndef STASSID
#define STASSID "CMU-DEVICE"
#define STAPSK ""
#endif

void handlerFunction() {
  recieved = true;
  server.send(200, "text/html", "");
  Serial.println("Recieved POST request...");
}

void setup() {

  Serial.begin(115200);

  Serial.println("Booted");
  Serial.println();
  Serial.println();

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // start the server
  server.on("/", handlerFunction);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://172.26.170.242");  // HTTP

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    unsigned long tic = millis();
    int httpCode = http.POST("");

    // wait for a post request
    while (!recieved) {
//      Serial.println("Waiting...");
      server.handleClient();  
    }
    unsigned long toc = millis();
    
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      Serial.printf("%d\n", toc-tic);

    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(10000);
}
