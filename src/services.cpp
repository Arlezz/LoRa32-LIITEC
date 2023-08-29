#include <services.h>
#include <board_def.h>


void services::setup_display(){

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



services::services(){
}

void services::servicesSetup(){

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


void services::servicesLoop(){

}


