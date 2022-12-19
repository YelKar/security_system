#include "page.h"
#include "MyData.h"
#include <WiFi.h>
#include <WebServer.h>

#define btn 0
#define led1 4
#define led2 5


// const char* ssid = "ESP32";
// const char* password = "12345678";


WebServer server(80);

void setup()
{
  Serial.begin(115200);

  delay(500);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) delay(300);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  delay(100);

  server.on("/", OnConnect);
  server.on("/alert", alert);
  server.on("/cancel", cancel);
  server.on("/update", update);
  
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void OnConnect() {
  Serial.println("conn");
  server.send(200, "text/html", page);
}

void cancel() {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("cancel");
  server.send(200, "text/plain", "OK");
}

void alert() {
  Serial.println("alert");
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/plain", "OK");
}

void update() {
  server.send(
    200, 
    "application/json", 
    digitalRead(btn) ? "{\"btn\": true}" : "{\"btn\": false}"
  );
}
