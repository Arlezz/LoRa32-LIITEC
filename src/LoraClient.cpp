#include "LoraClient.h"
#include "board_def.h"


void LoraClient::setup_display(){

  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  delay(2000); 
}


LoraClient::LoraClient() {
  sensorData = new DynamicJsonDocument(1024);
}

std::string LoraClient::data_formatting(std::string* data) {
  size_t found = data->find("$");  // Buscar la primera aparición de "$"

  // Mientras se encuentre "$" en la cadena
  while (found != std::string::npos) {
      data->erase(found, 1);  // Borrar el carácter "$" encontrado
      found = data->find("$", found);  // Buscar la siguiente aparición de "$" a partir de la posición actual
  }

  return *data;
}



void LoraClient::LoraClientSetup(){

  setup_display();

  display->clearDisplay();
  display->setTextColor(WHITE);
  display->setTextSize(1);
  display->setCursor(0,0);
  display->print("LORA SENDER ");
  display->display();

  Serial.println("LoRa Sender Test");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSyncWord(0xF3);           // ranges from 0-0xFF, default 0x34, see API docs
  LoRa.setSpreadingFactor(7);  // Configura el Spreading Factor
  LoRa.setTxPower(17);  // Configura la potencia de transmisión

  Serial.println("LoRa Initializing OK!");
  display->setCursor(0,10);
  display->print("LoRa Initializing OK!");
  display->display();
  delay(2000);
}


void LoraClient::LoraClientLoop(){
}