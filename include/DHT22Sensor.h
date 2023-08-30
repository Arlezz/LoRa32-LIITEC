#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

//#include <DHT.h>
//#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#include "LoraClient.h"
#include <string.h>

class DHT22Sensor{
    private: //
        int DHTPIN;
        int DHTTYPE;
        DHT_Unified* dht;
        //DHT* dht;
        LoraClient* client;
    public:
        DHT22Sensor(LoraClient*);
        void DHT22SensorSetup();
        std::string DHT22SensorLoop();
};

#endif