#include "Wireless.h"

/*
    Class constructor
*/
Wireless::Wireless() {}

/*
    Setup WiFi
*/
void Wireless::setup(Config *config) {

    _config = config;

    DEBUG_PRINT_WIFI("Start Wireless connection.");
    WiFi.hostname(_config->hostname);

    if (_config->ap_mode) {
        initAP();
    } else {
        initSTA();
    }
    DEBUG_PRINT_WIFI("Ready.");
    DEBUG_PRINT_LN();
}

/*
    Init Wireless as Access point
*/
void Wireless::initAP() {
    // WiFi.mode(WIFI_AP);
    DEBUG_PRINT_WIFI("Start Wireless in AP mode.");
    WiFi.softAP(_config->ap_ssid.c_str(), _config->ap_pass.c_str());
    IPAddress ip = WiFi.softAPIP();
    char ip_str[40];
    sprintf(ip_str, "AP ip address %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    DEBUG_PRINT_WIFI(ip_str);
}

/*
    Init Wireless as Sation
*/
void Wireless::initSTA() {
    DEBUG_PRINT_WIFI("Start Wireless in STA mode.");
    WiFi.mode(WIFI_STA);
    WiFi.begin(_config->ap_ssid.c_str(), _config->ap_pass.c_str());
    if (_config->dhcp) {
        DEBUG_PRINT_WIFI("Set dynamic IP.");
    } else {
        DEBUG_PRINT_WIFI("Set static IP.");
        IPAddress _ip(
            _config->ip[0],
            _config->ip[1],
            _config->ip[2],
            _config->ip[3]
            );
        IPAddress _mask(
            _config->mask[0],
            _config->mask[1],
            _config->mask[2],
            _config->mask[3]
            );
        IPAddress _gw(
            _config->gw[0],
            _config->gw[1],
            _config->gw[2],
            _config->gw[3]
            );
        WiFi.config(_ip, _gw, _mask);
    }
    DEBUG_PRINT_WIFI("Connecting...");
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED) {
        retry++;
        if (retry > 30) ESP.restart(); // Reastart fter 30 retryes
        delay(1000);
    }
    IPAddress ip = WiFi.localIP();
    char ip_str[40];
    sprintf(ip_str, "STA ip address %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    DEBUG_PRINT_WIFI(ip_str);
}