#include <bmp280Sensor.h>
#include <settings.h>

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

 void bmp280Sensor::bmp280SensorLoop(){
   Serial.println("---------Sensor BM280----------");
   Serial.print(F("Temperature = "));
   Serial.print(bmp->readTemperature());
   Serial.println(" *C");

   Serial.print(F("Pressure = "));
   float pressure = bmp->readPressure();
   Serial.print(bmp->readPressure());
   Serial.println(" Pa");

   Serial.print(F("Approx altitude = "));
   float altitude = bmp->readAltitude(1013.25);
   Serial.print(altitude); /* Adjusted to local forecast! */
   Serial.println(" m");
 }
 