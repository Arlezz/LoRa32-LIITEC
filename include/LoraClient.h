#ifndef LORACLIENT_H
#define LORACLIENT_H

#include <string.h>

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class LoraClient{
    private:

    public:
        std::string* data;
        Adafruit_SSD1306* display;
        LoraClient();
        //~LoraClient();
        void setup_display();
        void setup_sd();
        void LoraClientSetup();
        void LoraClientLoop();
        void LoraClientSender(String variable, String value);

};

#endif