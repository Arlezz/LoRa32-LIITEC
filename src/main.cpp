#include <Arduino.h>
#include <services.h>
#include <bmp280Sensor.h>
#include <DHT22Sensor.h>
#include <LoRa.h>

services service;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  service.servicesSetup();
}

void loop() {
  String message = "Hola desde LoRa32 V2.1_1.6";
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println(message);
  delay(5000);  // Espera 5 segundos antes de enviar nuevamente
}
