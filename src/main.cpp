#include "LoraClient.h"
#include "bmp280Sensor.h"
#include "DHT22Sensor.h"
#include <LoRa.h>
#include <ArduinoJson.h>

LoraClient client;
bmp280Sensor bmp280(&client);
DHT22Sensor dht22(&client);
int counter; 

void setup() {
    Serial.begin(115200);
    while (!Serial);
    client.LoraClientSetup();
    bmp280.bmp280SensorSetup();
    dht22.DHT22SensorSetup();
}

void loop() {
    Serial.print("Sending packet: \n");
    bmp280.bmp280SensorLoop();
    dht22.DHT22SensorLoop();

    String json;
    serializeJson((*client.sensorData), json);

    Serial.print("\n*********** ENVIADO ****************** \n");
    Serial.println(json.c_str());
    Serial.print("******************************** \n");

    //Envio de paquete LoRa al receptor
    LoRa.beginPacket();
    LoRa.print(json.c_str());
    LoRa.endPacket();
    
    
    //Formateo de datos para mostrar en pantalla OLED
    String dataDisplay = "";
    dataDisplay += "Hum: ";
    dataDisplay += (*client.sensorData)["Humedad"].as<String>();
    dataDisplay += "%";
    dataDisplay += "\nTem: ";
    dataDisplay += (*client.sensorData)["Temperatura"].as<String>();
    dataDisplay += "*C";
    dataDisplay += "\nPre: ";
    dataDisplay += (*client.sensorData)["Presion"].as<String>();
    dataDisplay += " Pa";
    dataDisplay += "\nAlt: ";
    dataDisplay += (*client.sensorData)["Altitud"].as<String>();
    dataDisplay += " m";

    
    //Mostrar en pantalla OLED
    client.display->clearDisplay();
    client.display->setCursor(0,0);
    client.display->println("LORA SENDER");
    client.display->setCursor(0,15);
    client.display->setTextSize(1);
    client.display->print("LoRa packet sent.");
    client.display->setCursor(0,25);
    client.display->print(dataDisplay.c_str());
    client.display->display();

    // Liberar memoria ocupada por el json anterior
    client.sensorData->clear();

    delay(2000);
}