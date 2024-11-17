#include <SPI.h>
#include <LoRa.h>

//Definir pines
#define ss 5
#define rst 14
#define dio0 2

void setup() {
  //Inicializar puerto serie
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //Inicializar LoRa
  LoRa.setPins(ss, rst, dio0);
  
  //Frecuencia de operación
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  //Sincronización de palabra
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  //Esperar paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Paquete recibido
    Serial.print("Received packet '");

    // Leer paquete
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // Imprimir RSSI
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}