#include <Arduino.h>

void readSerial();
void blinkTask(void *parameter);

int frequency = 500;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200); // Stellt Serielle Konsole Baudrate auf 115200

  Serial.print(">"); // erster output für die Eingabe

  xTaskCreate( // erstellt einen extra thread, damit das Blinken unabhänig von dem Main Loop ist
    blinkTask,
    "BlinkTask",
    2048,
    NULL,
    1,
    NULL
  );
}

void loop() {
  readSerial();
}

void readSerial() {
  static String buffer = "";

  while (Serial.available()) {

    char c = Serial.read();
    Serial.print(c);

    if (c == '\n') {

      Serial.print("Neue Frequenz: ");
      Serial.println(buffer);

      frequency = buffer.toInt();
      buffer = "";

      Serial.print(">");
    } else {
      buffer += c;

    }
  }
}

void blinkTask(void *parameter) {

  while(true) {
    digitalWrite(LED_BUILTIN , HIGH);
    vTaskDelay(frequency / portTICK_PERIOD_MS);

    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(frequency / portTICK_PERIOD_MS);
  }
}