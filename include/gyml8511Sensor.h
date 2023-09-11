#ifndef GYML8511SENSOR_H
#define GYML8511SENSOR_H

#include "LoraClient.h"


class gyml8511Sensor{
    private:
        int OUT;
        int EN_REF3V3;
        LoraClient* client;
        int averageAnalogRead(int pinToRead);
        float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
    public:
        gyml8511Sensor(LoraClient*);
        void gyml8511SensorSetup();
        void gyml8511SensorLoop();
};

#endif