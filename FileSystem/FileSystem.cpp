#include "FileSystem.h"

/*
    Class constructor
*/
FileSystem::FileSystem() {}

/*
    Init config
*/
void FileSystem::setup() {

    // Mount file system
    DEBUG_PRINT_FS("Press FLASH button for format FS.");
    // Delay 1sec for check reset button
    delay(1000);
    // Formating FS if presed reset button
    if( digitalRead(D3) == 0 ) {
        DEBUG_PRINT_FS("Formating FS.");
        if (!SPIFFS.format()) {
            DEBUG_PRINT_FS("Failed to format file system.");
        }
        DEBUG_PRINT_FS("Erasing ESP WiFi config.");
        ESP.eraseConfig();
    }
    // Mount FS
    DEBUG_PRINT_FS("Mounting FS.");
    if (!SPIFFS.begin()) {
        DEBUG_PRINT_FS("Failed to mount file system.");
    } else {
        DEBUG_PRINT_FS("Ready.");
    }
    DEBUG_PRINT_LN();
}