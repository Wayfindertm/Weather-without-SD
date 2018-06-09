#ifndef Wireless_h
#define Wireless_h

#include <ESP8266WiFi.h>
#include "../LWConfig/LWConfig.h"

#ifndef DEBUG_PRINT_LN
#define DEBUG_PRINT_LN(x)  Serial.println(x);
#endif

#ifndef DEBUG_PRINT_WIFI
#define DEBUG_PRINT_WIFI(x)  Serial.print("[WiFi] "); Serial.println(x);
#endif

class Wireless {
public:
    Wireless();
    void setup(Config *config);
    void initAP();
    void initSTA();
private:
    Config* _config;
};

#endif