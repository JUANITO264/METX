#include <SPI.h>
#include <LoRa.h>

//Definir pines
#define ss 5
#define rst 14
#define dio0 2

int counter = 0;

void setup() {
 //Inicializar puerto serie
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

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
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //Enviar paquete
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(10000);
}