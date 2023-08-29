#include <DHT22Sensor.h>
#include <sstream> 
#include <settings.h>

void DHT22Sensor::DHT22SensorSetup(){
    
    
    DHTPIN = 19;
    DHTTYPE = DHT22;
    //TOPIC = "sensor/dht22";

    dht = new DHT(DHTPIN,DHTTYPE);
}

void DHT22Sensor::DHT22SensorLoop(){

    float h = dht->readHumidity();
    // Reads the humidity in %
    float t = dht->readTemperature();

    //String message = "dht22:"+String(t)+":"+String(h);

    //String jsonString = "{\"" + String(VARIABLE_TEMPERATURA) + "\":" + String(t) + ", \"" + String(VARIABLE_HUMEDAD) + "\":" + String(h) + "}";

    Serial.println("---------Sensor DHT22----------");
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print("% \nTemperatura: ");
    Serial.print(t);
    Serial.print("°C");
    Serial.println();

}