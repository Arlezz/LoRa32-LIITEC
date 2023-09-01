#ifndef BM280SENSOR_H
#define BM280SENSOR_H

#include "LoraClient.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


class bmp280Sensor{
    private:
        int SDA;
        int SCL;
        Adafruit_BMP280* bmp;
        LoraClient* client;
    public:
        bmp280Sensor(LoraClient*);
        void bmp280SensorSetup();
        void bmp280SensorLoop();
};

#endif