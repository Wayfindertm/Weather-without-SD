// ESP modules
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include "FS.h"

// Auth module
#include <ArduinoOTA.h>

#define DEBUG_PRINT_LN(x)  Serial.println(x);
#define DEBUG_PRINT_ESP(x)  Serial.print("[ESP]  "); Serial.println(x);

// Libs
#include "FileSystem/FileSystem.h"
#include "LWConfig/LWConfig.h"
#include "Wireless/Wireless.h"
#include "Template/Template.h"
#include "Sensors/Sensors.h"

// Modules
FileSystem FS;
LWConfig CFG;
Wireless WIFI;
Template TPL;
Sensors SEN;

// WEB server
ESP8266WebServer server(80);

void setup() {

    // Init serial port
    Serial.begin(115200);
    DEBUG_PRINT_LN();
    DEBUG_PRINT_LN();
    delay(500);

    // Boot header
    DEBUG_PRINT_ESP("Booting.");
    DEBUG_PRINT_ESP("SDK: " + String(ESP.getSdkVersion()));
    DEBUG_PRINT_LN();

    // Init SPIFFS
    FS.setup();

    // Init global config
    CFG.setup();

    // Init sensors
    SEN.setup();

    // WiFi
    WIFI.setup(&CFG.config);
    delay(500);

    // Home page handler
    server.on ("/", [](){
        server.send( 200, "text/html", TPL.homeHandler(SEN.homeHandler(&TPL)));
    });

    // Admin page handler
    server.on ("/admin/", [](){
        if(!server.authenticate(CFG.config.auth_login.c_str(), CFG.config.auth_pass.c_str()))
            return server.requestAuthentication();
        if ( server.method() == HTTP_GET && server.args() == 0 ) {
            server.send( 200, "text/html", TPL.adminHandler(&CFG.config));
        } else {
            CFG.saveHandler(&server);
            server.send( 200, "application/json", "{\"success\":\"true\"}" );
            ESP.restart();
            return;
        }
    });

    // Devices page handler
    server.on ("/devices/", [](){
        if(!server.authenticate(CFG.config.auth_login.c_str(), CFG.config.auth_pass.c_str()))
            return server.requestAuthentication();
        if ( server.method() == HTTP_GET && server.args() == 0 ) {
            server.send( 200, "text/html", SEN.sensorsHandler(&TPL));
        } else {
            SEN.saveHandler(&server);
            server.send( 200, "application/json", "{\"success\":\"true\"}" );
            ESP.restart();
            return;
        }
    });

    // Sensors json
    server.on ("/sensors.json", [](){
        server.send( 200, "application/json", SEN.jsonHandler() );
    });

    // Update page handler
    server.on ("/firmware/", [](){
        if(!server.authenticate(CFG.config.auth_login.c_str(), CFG.config.auth_pass.c_str()))
            return server.requestAuthentication();
        server.send( 200, "text/html", TPL.firmwareHandler());
    });

    // Firmware update hundler
    server.on("/fwupdate", HTTP_POST, [](){
        if(!server.authenticate(CFG.config.auth_login.c_str(), CFG.config.auth_pass.c_str()))
            return server.requestAuthentication();
        server.sendHeader("Connection", "close");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "text/html", (Update.hasError())?"<h1>FAIL</h1>":"<meta http-equiv='refresh' content='5; url=/'><h1>Ok</h1><br>Redirecting...");
        ESP.restart();
    },[](){
        if(!server.authenticate(CFG.config.auth_login.c_str(), CFG.config.auth_pass.c_str()))
            return server.requestAuthentication();
        HTTPUpload& upload = server.upload();
        if(upload.status == UPLOAD_FILE_START){
            Serial.setDebugOutput(true);
            WiFiUDP::stopAll();
            Serial.printf("Update: %s\n", upload.filename.c_str());
            uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
            if(!Update.begin(maxSketchSpace)){
                Update.printError(Serial);
            }
        } else if(upload.status == UPLOAD_FILE_WRITE){
            if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
                Update.printError(Serial);
            }
        } else if(upload.status == UPLOAD_FILE_END){
            if(Update.end(true)){
                Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
            Serial.setDebugOutput(false);
        }
        yield();
    });

    // Web Server CSS handlers
    server.on("/reset.css", [](){ server.send( 200, "text/css", resetCSS); });
    server.on("/style.css", [](){ server.send( 200, "text/css", styleCSS); });

    // Web Server JS handlers
    server.on("/scripts.js", [](){ server.send(200, "application/javascript", scripts); });

    // Web Server NOT FOUND handler
    server.onNotFound ([](){
        server.send(404, "text/html", "<h1>Not found.</h1>");
    });

    // Start Web Server
    DEBUG_PRINT_ESP("Start WEB server.");
    server.begin();
    DEBUG_PRINT_LN();
    delay(1000);

    // ESP ready
    DEBUG_PRINT_ESP("Ready.");
    DEBUG_PRINT_LN();
}

void loop() {
    SEN.handle();
    SEN.HTTPhandle();
    ArduinoOTA.handle();
    server.handleClient();
}