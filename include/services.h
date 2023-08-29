#ifndef SERVICES_H
#define SERVICES_H

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Libraries for sensors
#include <bmp280Sensor.h>
#include <DHT22Sensor.h>

class services{
    private:
  
    public:
        Adafruit_SSD1306* display;
        services();
        void setup_display();
        void setup_sd();
        void servicesSetup();
        void servicesLoop();

};

#endif