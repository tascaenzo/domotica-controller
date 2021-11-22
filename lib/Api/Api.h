
#ifndef API_H
#define API_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

class Api
{
private:
  String token;
  WiFiClient client;
  HTTPClient http;
  ESP8266WebServer server;

  String getToken();
  void setToken(String token);

protected:
  void handleNotFound();
  void handleRoot();

public:
  Api();

  void updateServer();
  void sendMessage(); 
  void handleClient();
};

#endif