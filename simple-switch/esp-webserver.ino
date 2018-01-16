#include "esp-webserver.h"

void httpServerStart()
{
  httpServer.on("/", httpHandleRoot);
  httpServer.on("/on", httpHandleOn);
  httpServer.on("/off", httpHandleOff);
  httpServer.on("/configuration", httpHandleConfiguration);
  httpServer.on("/save", httpHandleSaveConfiguration);
  httpServer.on("/reboot", httpHandleReboot);
  httpServer.on("/favicon.ico",httpHandleFavicon);
  httpServer.onNotFound(http404);
  httpServer.begin();
}

void httpResponse(String &content, bool redirect)
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

  httpServer.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  httpServer.sendHeader("Pragma", "no-cache");
  httpServer.sendHeader("Expires", "-1");

  httpServer.send(200, "text/html", html);
}

void httpHandleRoot()
{
  String content = "Home page";
  httpResponse(content, false);
}

void httpHandleOn()
{
  masterRelay.on();
  String content = "ON";
  httpResponse(content, true);
}

void httpHandleOff()
{
  masterRelay.off();
  String content = "OFF";
  httpResponse(content, true);
}

void httpHandleConfiguration()
{
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
  httpResponse(content, false);
}

void httpHandleSaveConfiguration()
{

  cfg.setWifiSSID(httpServer.arg("wifiSSID"));
  cfg.setWifiPassword(httpServer.arg("wifiPassword"));
  cfg.setWifiDeviceName(httpServer.arg("wifiDeviceName"));
  cfg.setMqttHost(httpServer.arg("mqttHost"));
  cfg.setMqttUser(httpServer.arg("mqttUser"));
  cfg.setMqttPassword(httpServer.arg("mqttPassword"));
  cfg.setMqttTopic(httpServer.arg("mqttTopic"));
  
  String content = "Saved";

  content += "<form action='/reboot' method='post'>";
  content += "<div><input type='submit' value='Reboot'></div>";
  content += "</form>";
  
  httpResponse(content, false);
}

void httpHandleReboot()
{
  String content = "Reboot";
  httpResponse(content, true);
  delay(500);
  ESP.restart();
}

void httpHandleFavicon()
{
}

void http404()
{
  String content = "ERROR 404";
  httpResponse(content, false);
}



