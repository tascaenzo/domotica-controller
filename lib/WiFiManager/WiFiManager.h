#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

class WiFiManager
{
private:
  String ssid;
  String password;
  ESP8266WebServer server;
  
  static void reboot();

protected:
  void handleNotFound();
  void handleSaveForm();
  void handleRoot();

public:
  WiFiManager();

  String getSsid();
  String getPassword();

  void setSsid(String ssid);
  void setPassword(String password);

  void info();
};

const char HTML[] =
    "<!DOCTYPE html>"
    "<html>"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"

    "<style>"
    "body {font-family: Arial, Helvetica, sans-serif;}"
    "form {border: 3px solid #f1f1f1;}"

    "input[type=text], input[type=password] {"
    "width: 100%;"
    "padding: 12px 20px;"
    "margin: 8px 0;"
    "display: inline-block;"
    "border: 1px solid #ccc;"
    "box-sizing: border-box;}"

    "button {"
    "background-color: #4CAF50;"
    "color: white;"
    "padding: 14px 20px;"
    "margin: 8px 0;"
    "border: none;"
    "cursor: pointer;"
    "width: 100%;}"

    "button:hover {opacity: 0.8;}"

    ".cancelbtn {"
    "width: auto;"
    "padding: 10px 18px;"
    "background-color: #f44336;}"

    ".imgcontainer {"
    "text-align: center;"
    "margin: 24px 0 12px 0;}"

    "img.avatar {"
    "width: 40%;"
    "border-radius: 50%;}"

    ".container {"
    "padding: 16px;}"

    "</style>"
    "</head>"
    "<body>"

    "<h2>Setting WiFi</h2>"
    "<form action='/save'>"

    "<div class='container'>"
    "<label for='uname'><b>SSID</b></label>"
    "<input type='text' placeholder='Enter SSID' name='ssid' required>"
    "<label for='psw'><b>Password</b></label>"
    "<input type='password' placeholder='Enter Password' name='pass' required>"
    "<button type='submit'>Salva</button>"

    "</form>"

    "</body>"
    "</html>";

#endif