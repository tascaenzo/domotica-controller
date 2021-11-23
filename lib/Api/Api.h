
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
  bool authChek();

protected:
  void handleNotFound();
  void handleRoot();
  void handleAuthorize();

public:
  Api();

  void init();
  void sendMessage(); 
  void handleClient();
};

#endif