#ifndef FileSystem_h
#define FileSystem_h

#include <ESP8266WiFi.h>
#include "FS.h"

#ifndef DEBUG_PRINT_LN
#define DEBUG_PRINT_LN(x)  Serial.println(x);
#endif

#ifndef DEBUG_PRINT_FS
#define DEBUG_PRINT_FS(x)  Serial.print("[FS]   "); Serial.println(x);
#endif

class FileSystem {
public:
    FileSystem();
    void setup();
};

#endif