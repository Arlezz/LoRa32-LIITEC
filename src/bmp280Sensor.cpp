#include "bmp280Sensor.h"

bmp280Sensor::bmp280Sensor(LoraClient* client) : client(client) {
    // Resto de la inicialización si es necesario
}

void bmp280Sensor::bmp280SensorSetup(){
   SDA = 21;
   SCL = 22;

   Wire.begin(SDA, SCL);
   bmp = new Adafruit_BMP280();

   if (!bmp->begin(0x76)) {
      Serial.println("No se pudo encontrar el sensor BMP280. Verifica las conexiones o la dirección I2C.");
      while (1);
   }

   bmp->setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Modo de muestreo de temperatura */
                  Adafruit_BMP280::SAMPLING_X2,     /* Factor de sobremuestreo de presión */
                  Adafruit_BMP280::SAMPLING_X16,    /* Factor de sobremuestreo de temperatura */
                  Adafruit_BMP280::FILTER_X16,      /* Filtro */
                  Adafruit_BMP280::STANDBY_MS_500); /* Tiempo de espera en modo de espera */

}

void bmp280Sensor::bmp280SensorLoop() {
    Serial.println("---------Sensor BM280----------");
    Serial.print(F("Temperatura = "));
    float temperature = bmp->readTemperature();
    Serial.print(bmp->readTemperature());
    Serial.println(" *C");

    Serial.print(F("Presion: "));
    float pressure = bmp->readPressure()/100;
    Serial.print(pressure);
    Serial.println(" Pa");

    Serial.print(F("Altura aprox: "));
    float altitude = bmp->readAltitude(1013.25);
    Serial.print(altitude);
    Serial.println(" m");

    char temperatureFormatted[10];// Espacio suficiente para el formato
    char pressureFormatted[10];
    char altitudeFormatted[10];

    // Formatear las variables con dos decimales
    std::sprintf(temperatureFormatted, "%.2f", temperature);
    std::sprintf(pressureFormatted, "%.2f", pressure);
    std::sprintf(altitudeFormatted, "%.2f", altitude);


    (*client->sensorData)["Temperatura"] = temperatureFormatted;
    (*client->sensorData)["Presion"] = pressureFormatted;
    (*client->sensorData)["Altitud"] = altitudeFormatted;
}


 