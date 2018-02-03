#include "esp_webserver.h"

EspWebServer::EspWebServer()
{
}

void EspWebServer::start()
{
#if DEBUG_MODE
  Serial.println("Starting web server");
#endif
 
  webServer.on("/", std::bind(&EspWebServer::handleRoot, this));
  webServer.on("/on", std::bind(&EspWebServer::handleOn, this));
  webServer.on("/off", std::bind(&EspWebServer::handleOff, this));
  webServer.on("/configuration", std::bind(&EspWebServer::handleConfiguration, this));
  webServer.on("/save", std::bind(&EspWebServer::handleSaveConfiguration, this));
  webServer.on("/reboot", std::bind(&EspWebServer::handleReboot, this));
  webServer.on("/favicon.ico",std::bind(&EspWebServer::handleFavicon, this));
  webServer.onNotFound(std::bind(&EspWebServer::handle404, this));
  webServer.begin();
  isRunning = true;
}

void EspWebServer::stop()
{
  if (!isRunning) {
    return;
  }
  
#if DEBUG_MODE
  Serial.println("Stopping web server");
#endif
  
  webServer.stop();
  isRunning = false;
}

void EspWebServer::loop()
{
  if (isRunning) {
    webServer.handleClient();
  }
}

void EspWebServer::response(String &content, bool redirect = false)
{
  String html = 
    "<!DOCTYPE html>"
    "<html lang='en'>"
    "<head>"
    "<meta charset='UTF-8'>"
    "<meta name='viewport' content='user-scalable = yes'>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";

  if (redirect) {
    html += "<meta http-equiv='refresh' content='0; URL=/'>";
  }
   
  html += "<title>ESP Configuration</title>"
    "<style>"
      "body{font-family:Helvetica;font-size:14px;margin:0;background-color:#292929}"
      "a{color:#aaaaaf;text-decoration:none}"
      "a:hover{color:#fafaff}"
      "ul{margin:0;padding:0;list-style-type:none}"
      "li.horizontal{display:inline;padding-right:10px;color:#aaaaaf}"
      ".container{margin:0 auto;height:auto}"
      ".header,.navigation,.section,.section-content{width:100%}"
      ".header{color:#eaeaef;padding:10px}"
      ".navigation{background-color:#676767;color:#fafaff;padding:10px}"
      "form div{padding:5px 0px;}"
      "form label{display:inline-block;width:120px;text-align:right;padding-right:10px;}"
      "form input[type=text]{display:inline-block;width:150px;}"
      "form input[type=submit]{display:inline-block;width:290px;background-color:green;color:white;}"
    "</style>"
    "</head>"
    "<body>"
    "<div class='container'>"
    "<div class='header'>";

  html += 
    "<div class='navigation'>"
    "<ul>"
    "<li class='horizontal'><a href='/'>Info</a></li>"
    "<li class='horizontal'><a href='/on'>ON</a></li>"
    "<li class='horizontal'><a href='/off'>OFF</a></li>"
    "<li class='horizontal'><a href='/configuration'>Configuration</a></li>"
    "<li class='horizontal'><a href='/reboot'>Reboot</a></li>"
    "</ul>"
    "</div>";

  html += content;
  html += 
    "</div>"
    "</div>"
    "</body>"
    "</html>";

  webServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  webServer.sendHeader("Pragma", "no-cache");
  webServer.sendHeader("Expires", "-1");

  webServer.send(200, "text/html", html);
}


void EspWebServer::handleRoot()
{
  String content = "Relay state is: ";
  content += masterRelay.getState() ? "ON" : "OFF";
 response(content);
}

void EspWebServer::handleOn()
{
  // FIXME (global masterRelay)
  masterRelay.on();
  String content = "Switch to ON";
  response(content);
}

void EspWebServer::handleOff()
{
  // FIXME (global masterRelay)
  masterRelay.off();
  String content = "Switch to OFF";
  response(content);
}

void EspWebServer::handleConfiguration()
{
  //FIXME (global cfg)
  String content = "<form action='/save' method='post'>";

  content += "<h4>WiFi</h4>";
  content += "<div><label>SSID</label><input type='text' name='wifiSSID' length='32' value='"; content += cfg.wifiSSID; content += "'/></div>";
  content += "<div><label>Password</label><input type='text' name='wifiPassword' length='32' value='"; content += cfg.wifiPassword; content += "'/></div>";
  content += "<div><label>Device name</label><input type='text' name='wifiDeviceName' length='32' value='"; content += cfg.wifiDeviceName; content += "'/></div>";

  content += "<h4>MQTT</h4>";
  content += "<div><label>Host</label><input type='text' name='mqttHost' length='32' value='"; content += cfg.mqttHost; content += "'/></div>";
  content += "<div><label>Port</label><input type='text' name='mqttPort' length='5' value='"; content += cfg.mqttPort; content += "'/></div>";
  content += "<div><label>User</label><input type='text' name='mqttUser' length='32' value='"; content += cfg.mqttUser; content += "'/></div>";
  content += "<div><label>Password</label><input type='text' name='mqttPassword' length='32' value='"; content += cfg.mqttPassword; content += "'/></div>";
  content += "<div><label>Topic</label><input type='text' name='mqttTopic' length='32' value='"; content += cfg.mqttTopic; content += "'/></div>";

  content += "<div></div>";
  content += "<div><input type='submit' value='Save'></div>";
  
  content += "</form>";
  response(content);
}

void EspWebServer::handleSaveConfiguration()
{
  // FIXME (global cfg)
  cfg.setWifiSSID(webServer.arg("wifiSSID"));
  cfg.setWifiPassword(webServer.arg("wifiPassword"));
  cfg.setWifiDeviceName(webServer.arg("wifiDeviceName"));
  cfg.setMqttHost(webServer.arg("mqttHost"));
  cfg.setMqttUser(webServer.arg("mqttUser"));
  cfg.setMqttPassword(webServer.arg("mqttPassword"));
  cfg.setMqttTopic(webServer.arg("mqttTopic"));
  
  String content = "Saved";

  content += "<form action='/reboot' method='post'>";
  content += "<div><input type='submit' value='Reboot'></div>";
  content += "</form>";
  
  response(content);
}

void EspWebServer::handleReboot()
{
  String content = "Reboot";
  response(content);
  delay(500);

  // FIXME
  //reboot();
  exitFromConfiguration();
}

void EspWebServer::handleFavicon()
{
}

void EspWebServer::handle404()
{
  String content = "ERROR 404";
  response(content);
}

