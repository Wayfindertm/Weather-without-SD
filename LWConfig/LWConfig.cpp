#include "LWConfig.h"

/*
    Class constructor
*/
LWConfig::LWConfig() {}

/*
    Init config
*/
void LWConfig::setup() {

    DEBUG_PRINT_LWCONFIG("Load config.");

    // Load config
    if (!read()) {
        DEBUG_PRINT_LWCONFIG("Write default config file.");
        save();
    }

    DEBUG_PRINT_LWCONFIG("Ready.");
    DEBUG_PRINT_LN();

}

/*
    Read config from SPIFFS
*/
bool LWConfig::read(){

    // Try open SPIFFS config
    File configFile = SPIFFS.open("/config.json", "r");
    if (!configFile) {
        DEBUG_PRINT_LWCONFIG("Failed to open config file.");
        return false;
    }

    // Check config file size
    size_t size = configFile.size();
    if (size > 1024) {
        DEBUG_PRINT_LWCONFIG("Config file size is too large.");
        return false;
    }

    // Try parse config
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());

    if (!json.success()) {
        DEBUG_PRINT_LWCONFIG("Failed to parse config file.");
        return false;
    }

    // Load WiFi settings
    config.ap_mode      = json["ap_mode"];
    config.ap_ssid      = json["ap_ssid"].asString();
    config.ap_pass      = json["ap_pass"].asString();
    config.hostname     = json["hostname"].asString();
    config.dhcp         = json["dhcp"];

    config.ip[0]        = json["ip"][0];
    config.ip[1]        = json["ip"][1];
    config.ip[2]        = json["ip"][2];
    config.ip[3]        = json["ip"][3];

    config.mask[0]      = json["mask"][0];
    config.mask[1]      = json["mask"][1];
    config.mask[2]      = json["mask"][2];
    config.mask[3]      = json["mask"][3];

    config.gw[0]        = json["gw"][0];
    config.gw[1]        = json["gw"][1];
    config.gw[2]        = json["gw"][2];
    config.gw[3]        = json["gw"][3];

    // Load auth settings
    config.auth_login   = json["auth_login"].asString();
    config.auth_pass    = json["auth_pass"].asString();


    configFile.close();
    return true;
}

/*
    Save config to SPIFFS
*/
bool LWConfig::save() {

    // Try to open file for writing
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
        DEBUG_PRINT_LWCONFIG("Failed to open config file for writing.")
        return false;
    }

    StaticJsonBuffer<1024> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

    json["ap_mode"]     = config.ap_mode;
    json["ap_ssid"]     = config.ap_ssid.c_str();
    json["ap_pass"]     = config.ap_pass.c_str();
    json["hostname"]    = config.hostname.c_str();
    json["dhcp"]        = config.dhcp;

    JsonArray& ip       = json.createNestedArray("ip");
        ip.add(config.ip[0]);
        ip.add(config.ip[1]);
        ip.add(config.ip[2]);
        ip.add(config.ip[3]);

    JsonArray& mask     = json.createNestedArray("mask");
        mask.add(config.mask[0]);
        mask.add(config.mask[1]);
        mask.add(config.mask[2]);
        mask.add(config.mask[3]);

    JsonArray& gw       = json.createNestedArray("gw");
        gw.add(config.gw[0]);
        gw.add(config.gw[1]);
        gw.add(config.gw[2]);
        gw.add(config.gw[3]);

    json["auth_login"]  = config.auth_login.c_str();
    json["auth_pass"]   = config.auth_pass.c_str();

    json.printTo(configFile);
    configFile.close();
    return true;
}

/*
    IP range check
*/
bool LWConfig::checkRange(String val) {
    return (val.toInt() < 0 || val.toInt() > 255) ? false : true;
}

/*
    Save config from server data
*/
void LWConfig::saveHandler(ESP8266WebServer *server) {

    config.ap_mode = false;
    config.dhcp    = false;
    for ( uint8_t i = 0; i < server->args(); i++ ) {

        // Auth settings
        if(server->argName(i)=="auth_login") config.auth_login = server->arg(i);
        if(server->argName(i)=="auth_pass") config.auth_pass = server->arg(i);

        // WiFi settings
        if(server->argName(i)=="hostname") config.hostname = server->arg(i);
        if(server->argName(i)=="ap_mode" && server->arg(i)=="1") config.ap_mode = true;
        if(server->argName(i)=="ap_ssid") config.ap_ssid = server->arg(i);
        if(server->argName(i)=="ap_pass") config.ap_pass = server->arg(i);

        // IP settings
        if(server->argName(i)=="dhcp" && server->arg(i)=="1") config.dhcp = true;
        if(server->argName(i)=="ip_0" && checkRange(server->arg(i))) config.ip[0] = server->arg(i).toInt();
        if(server->argName(i)=="ip_1" && checkRange(server->arg(i))) config.ip[1] = server->arg(i).toInt();
        if(server->argName(i)=="ip_2" && checkRange(server->arg(i))) config.ip[2] = server->arg(i).toInt();
        if(server->argName(i)=="ip_3" && checkRange(server->arg(i))) config.ip[3] = server->arg(i).toInt();
        if(server->argName(i)=="mask_0" && checkRange(server->arg(i))) config.mask[0] = server->arg(i).toInt();
        if(server->argName(i)=="mask_1" && checkRange(server->arg(i))) config.mask[1] = server->arg(i).toInt();
        if(server->argName(i)=="mask_2" && checkRange(server->arg(i))) config.mask[2] = server->arg(i).toInt();
        if(server->argName(i)=="mask_3" && checkRange(server->arg(i))) config.mask[3] = server->arg(i).toInt();
        if(server->argName(i)=="gw_0" && checkRange(server->arg(i))) config.gw[0] = server->arg(i).toInt();
        if(server->argName(i)=="gw_1" && checkRange(server->arg(i))) config.gw[1] = server->arg(i).toInt();
        if(server->argName(i)=="gw_2" && checkRange(server->arg(i))) config.gw[2] = server->arg(i).toInt();
        if(server->argName(i)=="gw_3" && checkRange(server->arg(i))) config.gw[3] = server->arg(i).toInt();

    }

    // Saving new config
    save();
}