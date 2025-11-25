#include <Arduino.h>
#include <Wifi.h>

const char *ssid = "WLAN 67676767";
const char *password = "123456789";
const int ap_channel = 6;
const boolean ap_hidden = false;

IPAddress local_ip(192,168,4,100);
IPAddress gateway(192,168,4,254);
IPAddress netmask(255,255,255,0);

void setup() {
  WiFi.softAPConfig(local_ip, gateway, netmask);
  WiFi.softAP(ssid, password, ap_channel, ap_hidden);
}

void loop() {
  delay(1000);
}
