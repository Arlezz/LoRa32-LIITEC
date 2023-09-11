#include "gyml8511Sensor.h"

gyml8511Sensor::gyml8511Sensor(LoraClient* client) : client(client) {
    // Resto de la inicialización si es necesario
}

void gyml8511Sensor::gyml8511SensorSetup(){
    OUT = 14;
    EN_REF3V3 = 15;

    pinMode(OUT, INPUT);
    pinMode(EN_REF3V3, OUTPUT);
}

int gyml8511Sensor::averageAnalogRead(int pinToRead)
{
    byte numberOfReadings = 8;
    unsigned int runningValue = 0; 

    for(int x = 0 ; x < numberOfReadings ; x++)
        runningValue += analogRead(pinToRead);
    runningValue /= numberOfReadings;

    return(runningValue);
}

float gyml8511Sensor::mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void gyml8511Sensor::gyml8511SensorLoop() {

    int uvLevel = averageAnalogRead(OUT);
    int refLevel = averageAnalogRead(EN_REF3V3);

    //Utilice el pin de alimentación de 3,3 V como referencia para obtener un valor de salida muy preciso del sensor
    float outputVoltage = 3.3 / refLevel * uvLevel;

    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convierte el voltaje en un nivel de intensidad UV

    Serial.println("---------Sensor BM280----------");
    Serial.print(F("UV = ")); 
    Serial.print(uvIntensity);
    Serial.println(" mW/cm^2");

    char uvFormatted[10];// Espacio suficiente para el formato

    // Formatear las variables con dos decimales
    std::sprintf(uvFormatted, "%.2f", uvIntensity);

    (*client->sensorData)["UV"] = uvFormatted;
}


 