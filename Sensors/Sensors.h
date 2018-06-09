#ifndef Sensors_h
#define Sensors_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "FS.h"

#include "../Template/Template.h"
#include "HTML.h"
#include "JS.h"

#ifndef DEBUG_PRINT_LN
#define DEBUG_PRINT_LN(x)  Serial.println(x);
#endif

#ifndef DEBUG_PRINT_SENSORS
#define DEBUG_PRINT_SENSORS(x)  Serial.print("[SEN]  "); Serial.println(x);
#endif

// Sensors module
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

typedef struct
{

    // DHT 1 settings
    bool    dht1_en     = false;
    int     dht1_pin    = 4;
    int     dht1_type   = 22;

    // DHT 2 settings
    bool    dht2_en     = false;
    int     dht2_pin    = 4;
    int     dht2_type   = 11;

    // DS18x20 settings
    bool    ds_en       = false;
    int     ds_pin      = 2;

    // Url to send data
    String  url         = "localhost";

} SConfig;

class Sensors {
public:
    Sensors();
    void setup();
    bool read();
    bool save();
    String homeHandler(Template *TPL);
    String sensorsHandler(Template *TPL);
    void saveHandler(ESP8266WebServer *server);
    String jsonHandler();
    void handle();
    void HTTPhandle();

    String _typeBlock(String id);
    String _pinBlock(String id);
    unsigned char h2int(char c);
    String urldecode(String str);


private:
    SConfig config;

    unsigned long _previousMillis = 0;
    unsigned long _httpMillis = 0;
    const long _interval = 10000;
    const long _httpinterval = 600000;
    float _dht1_temp    = -127;
    float _dht1_hum     = 0;
    float _dht2_temp    = -127;
    float _dht2_hum     = 0;
    float _ds_temp      = -127;
    OneWire* _onewire;
    DallasTemperature _ds;
    DHT* _dht1;
    DHT* _dht2;
    HTTPClient _http;

};

#endif