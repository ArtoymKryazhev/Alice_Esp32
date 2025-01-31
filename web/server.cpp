#include <WebServer.h>
#include "server.h"
#include "index.h"

WebServer server(80);

void createServer() {
  // Обработка GET-запроса на корневой адрес
  server.on("/", handleRoot);
}

void startServer() {
  server.begin();
  Serial.println("Web server started.");
}

void handleClient() {
  server.handleClient(); // Обработка входящих клиентов
}
