#ifndef BM280SENSOR_H
#define BM280SENSOR_H

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class bmp280Sensor{
    private:
        int SDA;
        int SCL;
        Adafruit_BMP280* bmp;
    public:
        void bmp280SensorSetup();
        void bmp280SensorLoop();
};

#endif