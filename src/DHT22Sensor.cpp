#include "DHT22Sensor.h"
#include "board_def.h"

DHT22Sensor::DHT22Sensor(LoraClient* client):
    client(client){
}

void DHT22Sensor::DHT22SensorSetup(){
    
    
    DHTPIN = 0;
    DHTTYPE = DHT22;

    dht = new DHT_Unified(DHTPIN,DHTTYPE);
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

    Serial.println("---------Sensor DHT22----------");
    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.print("% \nTemperatura: ");
    Serial.print(temperature);
    Serial.print("°C");
    Serial.println();

    client->data->append("H: ");
    client->data->append(std::to_string(humidity));
    client->data->append("%$\n");
    client->data->append("Temp: ");
    client->data->append(std::to_string(temperature));
    client->data->append(" *C$\n");

    return *(client->data);
}