#ifndef Template_h
#define Template_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "../LWConfig/LWConfig.h"

#include "HTML.h"
#include "CSS.h"
#include "JS.h"

class Template {
public:
    Template();
    String homeHandler(String content);
    String adminHandler(Config *config);
    String firmwareHandler();

    String _page(String title, String header, String content, String scripts, bool home);
    String _pageBlock(String header, String content);
    String _inputBlock(String header, String id, String value, bool disabled);
    String _checkboxBlock(String header, String id, bool value);
    String _ipBlock(String header, String id, byte value[]);

};

#endif