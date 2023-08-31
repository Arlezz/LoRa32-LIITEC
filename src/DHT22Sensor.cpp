#include "DHT22Sensor.h"
#include "board_def.h"


DHT22Sensor::DHT22Sensor(LoraClient* client):
    client(client){
}

void DHT22Sensor::DHT22SensorSetup(){
    DHTPIN = 0;
    DHTTYPE = DHT22;
    dht = new DHT_Unified(DHTPIN, DHTTYPE);  // Crear un nuevo objeto DHT_Unified
    dht->begin();
}

std::string DHT22Sensor::DHT22SensorLoop(){

    float humidity;
    float temperature;

    sensors_event_t event;
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        temperature = event.temperature;
    }
    // Get humidity event and print its value.
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        humidity = event.relative_humidity;
    }

    char temperatureFormatted[10];// Espacio suficiente para el formato
    char humidityFormatted[10];

    // Formatear las variables con dos decimales
    std::sprintf(temperatureFormatted, "%.2f", temperature);
    std::sprintf(humidityFormatted, "%.2f", humidity);

    Serial.println("---------Sensor DHT22----------");
    Serial.print("Humedad: ");
    Serial.print(humidityFormatted);
    Serial.print("% \nTemperatura: ");
    Serial.print(temperatureFormatted);
    Serial.print("°C");
    Serial.println();

    client->data->append("H: ");
    client->data->append(humidityFormatted);
    client->data->append("%$\n");
    client->data->append("Temp: ");
    client->data->append(temperatureFormatted);
    client->data->append(" *C$\n");


    return *(client->data);
}