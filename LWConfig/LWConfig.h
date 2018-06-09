#ifndef LWConfig_h
#define LWConfig_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "FS.h"

#ifndef DEBUG_PRINT_LN
#define DEBUG_PRINT_LN(x)  Serial.println(x);
#endif

#ifndef DEBUG_PRINT_LWCONFIG
#define DEBUG_PRINT_LWCONFIG(x)  Serial.print("[CFG]  "); Serial.println(x);
#endif

typedef struct
{

    // Wifi settings
    bool    ap_mode    = true;
    String  ap_ssid    = "ESP8266";
    String  ap_pass    = "password";
    String  hostname   = "ESP8266";
    byte    ip[4]      = {192,168,4,1};
    byte    mask[4]    = {255,255,255,0};
    byte    gw[4]      = {192,168,4,1};
    bool    dhcp       = false;

    // Auth settings
    String  auth_login = "admin";
    String  auth_pass  = "admin";

} Config;

class LWConfig {
public:
    Config config;
    LWConfig();
    void setup();
    bool read();
    bool save();
    void saveHandler(ESP8266WebServer *server);
private:
    bool checkRange(String val);
};

#endif