#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

//#include <DHT.h>
//#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#include "LoraClient.h"

const size_t capacity = JSON_OBJECT_SIZE(1);

class DHT22Sensor{
    private: //
        int DHTPIN;
        int DHTTYPE;
        DHT_Unified* dht;
        LoraClient* client;
    public:
        DHT22Sensor(LoraClient*);
        void DHT22SensorSetup();
        void DHT22SensorLoop();
};

#endif