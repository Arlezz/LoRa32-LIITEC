#include <Arduino.h>
#include <services.h>
//#include <bmp280Sensor.h>
//#include <DHT22Sensor.h>
#include <LoRa.h>

services service;
int counter; 

void setup() {
    Serial.begin(115200);
    while (!Serial);
    service.servicesSetup();
    counter = 0;
}

void loop() {
    Serial.print("Sending packet: ");
    Serial.println(counter);

    //Envio de paquete LoRa al receptor
    LoRa.beginPacket();
    LoRa.print("Enviado ");
    LoRa.print(counter);
    LoRa.endPacket();

    service.display->clearDisplay();
    service.display->setCursor(0,0);
    service.display->println("LORA SENDER");
    service.display->setCursor(0,20);
    service.display->setTextSize(1);
    service.display->print("LoRa packet sent.");
    service.display->setCursor(0,30);
    service.display->print("Counter:");
    service.display->setCursor(50,30);
    service.display->print(counter);
    service.display->display();

    counter++;

    delay(1000);
}