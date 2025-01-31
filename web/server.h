#ifndef SERVER_H
#define SERVER_H

#include "Arduino.h"

#include <WebServer.h>

extern WebServer server;

void createServer();
void startServer();
void handleClient();

#endif // SERVER_H
