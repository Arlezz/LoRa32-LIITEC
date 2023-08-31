#include "LoraClient.h"
#include "bmp280Sensor.h"
#include "DHT22Sensor.h"
#include <LoRa.h>

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

    Serial.print("\n*********** ENVIADO ****************** \n");
    Serial.println(client.data->c_str());
    Serial.print("******************************** \n");


    //Envio de paquete LoRa al receptor
    LoRa.beginPacket();
    LoRa.print(client.data->c_str());
    LoRa.endPacket();

    
    //Formateo de datos para mostrar en pantalla OLED
    std::string data = client.data_formatting(client.data);
    
    //Mostrar en pantalla OLED
    client.display->clearDisplay();
    client.display->setCursor(0,0);
    client.display->println("LORA SENDER");
    client.display->setCursor(0,15);
    client.display->setTextSize(1);
    client.display->print("LoRa packet sent.");
    client.display->setCursor(0,25);
    client.display->print(data.c_str());
    client.display->display();

    // Liberar memoria ocupada por el std::string anterior
    delete client.data;

    // Reasignar un nuevo std::string vacío al puntero data
    client.data = new std::string();

    delay(2000);
}