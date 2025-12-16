#include <Arduino.h>
#include <Wifi.h>
#include <WebServer.h>

void handleRoot();
void handlePage1();
void handleNotFound();

const char *ssid = "Jan_Sch";
const char *password = "123456789";
const int ap_channel = 6;
const boolean ap_hidden = false;

IPAddress local_ip(192,168,4,100);
IPAddress gateway(192,168,4,254);
IPAddress netmask(255,255,255,0);

WebServer server(80);

const char StartPage[] PROGMEM = R"htmlgrenze(
  <html>
  <body>
    <div style="display: flex; flex-direction: row; justify-content: center; align-items: center; width: 100%; height; 100%;">
      <div style="width: 300px; height: 150px; border: 1px solid black; border-radius: 7px;">
        <h1 style="width: 100%; text-align: center;">Willkommen!</h1>
        <p style="width: 100%; height: auto; text-align: center;">Teststartseite vom ESP32!!</p>
        <p style="width: 100%; height: auto; text-align: center; color: lightgray;">bloß dass die halt noch nichts kann...</p>
      </div>
    </div>
  </body>
  </html>
)htmlgrenze";

const char Page1[] PROGMEM = R"htmlgrenze(
    <html>
      <head>
        <meta charset="UTF-8">
        <style>

          .d-flex {
            display: flex;
            align-items: center;
            justify-content: center;
            width: 100%;
          }

          .main {
            width: 35%;
            border: 2px lime dashed;
            border-radius: 7px;
            background-color: green;
          }
        </style>
      </head>
      <body>
        <div class='d-flex'>
          <div class='main'>
            <h1>ESP32</h1>
            <br>
            <p>Der ESP32 ist ein kostengünstiger und mit geringem Leistungsbedarf ausgeführter 32-Bit-Mirkocontroller der 
              chinesischen Firma espressif und ermöglicht durch seine offene Bauweise den Aufbau von WLAN-gesteuerten 
              Aktoren und Sensoren.</p>
              <br>
              <h4>Der ESP32 ist einer der meisten verbreiteten Microcontroller für Smarthome Komponenten.</h4>
          </div>
        </div>
      </body>
    </html>
)htmlgrenze";

void setup() {
  WiFi.softAPConfig(local_ip, gateway, netmask);
  boolean result = WiFi.softAP(ssid, password, ap_channel, ap_hidden);

  if(result) {
    server.on("/", handleRoot);
    server.on("/uebung", handlePage1);
    server.onNotFound(handleNotFound);
    server.begin();
  }
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", StartPage);
}

void handlePage1() {
  server.send(200, "text/html", Page1);
}

void handleNotFound() {
  server.send(404, "text/plain", "404 not found!!!");
}
