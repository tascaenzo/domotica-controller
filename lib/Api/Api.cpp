#include "Api.h"
#include "constants.h"

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

Api::Api()
{
  String token;

  /*for (uint8_t i = 128; i < 256; i++)
    token += char(EEPROM.read(i));
  setToken(token);*/

  server.begin(SERVER_PORT);
  server.sendHeader(F("Access-Control-Allow-Origin"), F("192.168.1.77"));
  server.on("/", HTTP_POST, std::bind(&Api::handleRoot, this));
  server.onNotFound(std::bind(&Api::handleNotFound, this));
}

void Api::handleClient()
{
  server.handleClient();
}

void Api::handleRoot()
{
  StaticJsonDocument<200> doc;
  String json;
  String serverIp = client.remoteIP().toString().c_str();
  if (serverIp != SERVER_ORIGIN)
  {
    doc["statusCode"] = 401;
    doc["message"] = "You are not the server";
    doc["error"] = "Forbidden";
    serializeJson(doc, json);
    server.send(401, "application/json", json);
    return;
  }

  doc["statusCode"] = 200;
  serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void Api::handleNotFound()
{
  StaticJsonDocument<200> doc;
  String json;

  doc["statusCode"] = 404;
  doc["message"] = "Not Found Endpoint";
  doc["error"] = "Not Found";
  serializeJson(doc, json);

  server.send(404, "application/json", json);
}

String Api::getToken()
{
  return token;
}

void Api::setToken(String token)
{
  this->token = token;
}

void Api::updateServer()
{
  StaticJsonDocument<200> doc;
  doc["ip"] = "my_ip";

  String json;
  serializeJson(doc, json);

  http.begin(client, API_URL);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.PATCH(json);

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}