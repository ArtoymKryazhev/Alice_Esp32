#include <WebServer.h>
#include "index.h"

#define LED_PIN 2
int value;
bool ledState = false;

void handleRoot() {
  // Получаем параметр "value" из запроса
  if (server.hasArg("value")) {
    value = server.arg("value").toInt();

    if (value == 1 && ledState == false) {
      digitalWrite(LED_PIN, HIGH);
      ledState = true;
      server.send(200, "text/plain", "turn on");
    } else if (value == 0 && ledState == true) {
      digitalWrite(LED_PIN, LOW);
      ledState = false;
      server.send(200, "text/plain", "turn off");
    }

  } else {
    server.send(400, "text/plain", "not get 'value'");
  }
}
