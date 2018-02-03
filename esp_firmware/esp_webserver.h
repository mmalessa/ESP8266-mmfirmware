#ifndef _esp_web_server
#define _esp_web_server

#include <ESP8266WebServer.h>


class EspWebServer
{
  private:
    ESP8266WebServer webServer;
    bool isRunning = false;
    void response(String &content, bool redirect);
    void handleRoot();
    void handleOn();
    void handleOff();
    void handleConfiguration();
    void handleSaveConfiguration();
    void handleReboot();
    void handleFavicon();
    void handle404();
    

  public:
    EspWebServer();
    void start();
    void stop();
    void loop();

  
};



#endif
