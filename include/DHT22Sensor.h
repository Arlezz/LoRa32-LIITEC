#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include <DHT.h>

class DHT22Sensor{
    private: //
        int DHTPIN;
        int DHTTYPE;
        DHT* dht;
    public:
        void DHT22SensorSetup();
        void DHT22SensorLoop();
};

#endif