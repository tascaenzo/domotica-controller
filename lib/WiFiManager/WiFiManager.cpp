#include "WiFiManager.h"

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

WiFiManager::WiFiManager()
{
  String password;
  String ssid;

  for (uint8_t i = 63; i < 128; i++)
    password = password + char(EEPROM.read(i));

  for (uint8_t i = 0; i < 64; i++)
    ssid = ssid + char(EEPROM.read(i));

  setPassword(password);
  setSsid(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(this->getSsid(), this->getPassword());
  Serial.print("WiFi");

  for (uint8_t i = 0; WiFi.status() != WL_CONNECTED; i++)
  {
    if (i > 25)
    {
      WiFi.softAP(WiFi.macAddress());
      IPAddress myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);

      //init http server;
      Ticker restartTimer;
      restartTimer.attach_ms(120 * 1000, reboot);

      server.begin();
      server.on("/", std::bind(&WiFiManager::handleRoot, this));
      server.on("/save", std::bind(&WiFiManager::handleSaveForm, this));
      server.onNotFound(std::bind(&WiFiManager::handleNotFound, this));
      Serial.println("HTTP server started");

      while (1)
        server.handleClient();
    }

    delay(500);
    Serial.print(".");
  }
}

void WiFiManager::reboot()
{
  Serial.printf("Retray WiFi connection");
  ESP.restart();
}

void WiFiManager::handleRoot()
{
  server.send(200, "text/html", HTML);
}

void WiFiManager::handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void WiFiManager::handleSaveForm()
{
  String ssid = server.arg("ssid");
  String password = server.arg("pass");

  Serial.print("ssid:");
  Serial.println(ssid);

  Serial.print("password:");
  Serial.println(password);

  for (uint8_t i = 0; i < ssid.length(); i++)
  {
    EEPROM.write(i, ssid[i]);
  }
  EEPROM.write(ssid.length(), '\0');

  for (uint8_t i = 63; i < password.length() + 63; i++)
  {
    EEPROM.write(i, password[i - 63]);
  }
  EEPROM.write(password.length() + 63, '\0');
  EEPROM.commit();

  setPassword(password);
  setSsid(ssid);

  String body = "<p> Modifiche Salvate Puoi Chiudere Questa Pagina </p>";
  server.send(200, "text/html", body);
  delay(1000);
  ESP.restart();
}

String WiFiManager::getSsid()
{
  return ssid;
}

String WiFiManager::getPassword()
{
  return password;
}

void WiFiManager::setSsid(String ssid)
{
  this->ssid = ssid;
}

void WiFiManager::setPassword(String password)
{
  this->password = password;
}

void WiFiManager::info()
{
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}
