#include <SocketIoClient.h>



/*
void setup() {
  // put your setup code here, to run once:
  pinMode(D1, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D1, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  delay(1000);
}
*/

/*
  Esp8266 Websockets Client

  This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Prints all incoming messages while the connection is open

  Hardware:
        For this sketch you only need an ESP8266 board.

  Created 15/02/2019
  By Gil Maimon
  https://github.com/gilmaimon/ArduinoWebsockets

*/

#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

const char* ssid = "Aman"; //Enter SSID
const char* password = "aman1234"; //Enter Password
const char* websockets_server_host = "192.168.1.12"; //Enter server adress
const uint16_t websockets_server_port = 8080; // Enter server port

using namespace websockets;

WebsocketsClient client;
SocketIoClient webSocket;
#define USE_SERIAL Serial

void setup() {
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for(int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) {
        Serial.print(".");
        delay(1000);
    }

    // Check if connected to wifi
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("No Wifi!");
        return;
    }

    Serial.println("Connected to Wifi, Connecting to server.");
    // try to connect to Websockets server
    webSocket.begin("192.168.1.12",8080);

    webSocket.on("event", event);
    webSocket.on("switch", switchEvent);
}

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

void switchEvent(const char * payload, size_t length) {
  USE_SERIAL.printf("got switch message: %s\n", payload);
}

void loop() {
    // let the websockets client check for incoming messages
    webSocket.loop();
}
