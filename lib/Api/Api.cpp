#include "Api.h"
#include "constants.h"

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

Api *Api::instance = 0;

Api *Api::getInstance()
{
  if (instance == 0)
  {
    instance = new Api();
  }
  return instance;
}

Api::Api()
{
  server.begin(SERVER_PORT);
  server.sendHeader(F("Access-Control-Allow-Origin"), F(ALLOW_ORIGIN));

  server.on("/", HTTP_POST, std::bind(&Api::handleRoot, this));
  //server.on("/authorize", HTTP_POST, std::bind(&Api::handleAuthorize, this));

  server.onNotFound(std::bind(&Api::handleNotFound, this));
}

String Api::getToken()
{
  return token;
}

void Api::setToken(String token)
{
  this->token = token;
}

void Api::init()
{
  String token;
  for (uint8_t i = 128; i < 255; i++)
    token += char(EEPROM.read(i));
  setToken(token);

  StaticJsonDocument<200> doc;
  doc["ip"] = WiFi.localIP();
  doc["mac"] = WiFi.macAddress();

  String json;
  serializeJson(doc, json);

  String url;
  url.concat(API_URL);
  url.concat("/update-ip");
  http.begin(client, url);

  http.addHeader("Content-Type", "application/json");
  //http.addHeader("Authorization", "Bearer " + token);

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

bool Api::authChek()
{
  StaticJsonDocument<200> doc;
  String json;
  String serverIp = server.client().remoteIP().toString();
  if (serverIp != ALLOW_ORIGIN)
  {
    doc["statusCode"] = 401;
    doc["message"] = "Reject IP address";
    doc["error"] = "Forbidden";
    serializeJson(doc, json);
    server.send(401, "application/json", json);
    return false;
  }
  return true;
}

void Api::handleClient()
{
  server.handleClient();
}

//////////////////// coontrollers ////////////////////

/*void Api::handleAuthorize()
{
  if (!authChek())
    return;

  StaticJsonDocument<200> body;
  StaticJsonDocument<200> response;
  String jsonResponse;
  deserializeJson(body, server.arg("plain"));

  JsonObject obj = body.as<JsonObject>();
  String token = obj["token"].as<String>();

  for (uint8_t i = 128; i < token.length() + 128; i++)
  {
    EEPROM.write(i, token[i - 128]);
  }
  EEPROM.write(token.length() + 128, '\0');
  EEPROM.commit();

  Serial.println(token);
  response["action"] = "StoredToken";
  response["success"] = true;

  serializeJson(response, jsonResponse);
  server.send(200, "application/json", jsonResponse);
}*/

void Api::handleRoot()
{
  if (!authChek())
    return;

  StaticJsonDocument<200> body;
  StaticJsonDocument<200> response;
  String jsonResponse;

  deserializeJson(body, server.arg("plain"));

  response["statusCode"] = 200;
  serializeJson(response, jsonResponse);
  server.send(200, "application/json", jsonResponse);
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