#ifndef API_H
#define API_H

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IO.h>

class Api
{
private:
  //singleton instance
  static Api *instance;

  String token;
  IO* io = IO::getInstance();
  WiFiClient client;
  HTTPClient http;
  ESP8266WebServer server;

  String getToken();
  void setToken(String token);
  bool authCheck();
  bool pinCheck(uint8_t pin, String action);

protected:
  void handleNotFound();
  void handleRootPost();
  //void handleAuthorize();

public:
  static Api *getInstance();
  Api();

  void init();
  void sendMessage();
  void handleClient();
};

#endif