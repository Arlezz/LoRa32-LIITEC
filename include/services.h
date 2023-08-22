#ifndef SERVICES_H
#define SERVICES_H

#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <board_def.h>
#include "ds3231.h"
#include <SD.h>

class services{
    private: //
        const char* ssid;
        const char* password;
        OLED_CLASS_OBJ* display;
        //WiFiClient loraClient;
  
    public:
        services();
        void setup_display();
        void setup_sd();
        void servicesSetup();
        void servicesLoop();

};

#endif