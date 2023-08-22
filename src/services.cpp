#include <services.h>

void setup_wifi(String ssid, String password) {
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void services::setup_display(){
  if (OLED_RST > 0) {
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, HIGH);
    delay(100);
    digitalWrite(OLED_RST, LOW);
    delay(100);
    digitalWrite(OLED_RST, HIGH);
  }
  
  display->init();
  display->flipScreenVertically();
  display->clear();
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(display->getWidth() / 2, display->getHeight() / 2, LORA_SENDER ? "LoRa Sender" : "LoRa Receiver");
  display->display();
  delay(2000); 
}

void services::setup_sd(){
  if (SDCARD_CS >  0) {
        display->clear();
        SPIClass sdSPI(VSPI);
        sdSPI.begin(SDCARD_SCLK, SDCARD_MISO, SDCARD_MOSI, SDCARD_CS);
        if (!SD.begin(SDCARD_CS, sdSPI)) {
            display->drawString(display->getWidth() / 2, display->getHeight() / 2, "SDCard  FAIL");
        } else {
            display->drawString(display->getWidth() / 2, display->getHeight() / 2 - 16, "SDCard  PASS");
            uint32_t cardSize = SD.cardSize() / (1024 * 1024);
            display->drawString(display->getWidth() / 2, display->getHeight() / 2, "Size: " + String(cardSize) + "MB");
        }
        display->display();
        delay(2000);
  }
}


services::services()
    : //ssid("Casa_EXT"),
      //password("Um7uwD6JA7q"),
      ssid("ULS"),
      password("wifi@userena")
{}

void services::servicesSetup(){

  display = new OLED_CLASS_OBJ(OLED_ADDRESS, OLED_SDA, OLED_SCL);

  setup_display();
  setup_sd();

  String info = ds3231_test();
  if (info != "") {
    display->clear();
    display->setFont(ArialMT_Plain_16);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(display->getWidth() / 2, display->getHeight() / 2, info);
    display->display();
    delay(2000);
  }

  setup_wifi(ssid,password);

  SPI.begin(CONFIG_CLK, CONFIG_MISO, CONFIG_MOSI, CONFIG_NSS);
  LoRa.setPins(CONFIG_NSS, CONFIG_RST, CONFIG_DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Error al iniciar LoRa");
    while (1);
  }
  if (!LORA_SENDER) {
    display->clear();
    display->drawString(display->getWidth() / 2, display->getHeight() / 3, "LoraRecv Ready\nListo para recibir");
    display->display();
  }else{
    display->clear();
    display->drawString(display->getWidth() / 2, display->getHeight() / 3, "LoraSend Ready\nListo para enviar");
    display->display();
  }

  Serial.println("LoRa iniciado correctamente");
}


void services::servicesLoop(){

}


