#include <SPI.h>
#include <LoRa.h>
#include <Arduino.h>
#include "HX711.h"

//Definir pines de LoRa
#define ss 5
#define rst 14
#define dio0 2

//Definir pines de HX711
const int LOADCELL_DOUT_PIN = 22;
const int LOADCELL_SCK_PIN = 21;

int counter = 0;

//Creae objeto HX711
HX711 scale;

void setup() {
 //Inicializar puerto serie
  Serial.begin(115200);
  
  //Inicializar LoRa
  //LoRa.setPins(ss, rst, dio0);
  
  //Frecuencia de operación de LoRa
  /*while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }*/
  //Sincronización de palabra de LoRa
  //LoRa.setSyncWord(0xF3);
  //Serial.println("LoRa Initializing OK!");

  //Inicializar HX711
  setCpuFrequencyMhz(80); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-6.552);
  scale.tare();
  Serial.println("HX711 Initializing OK!");
}

void loop() {
  //Código LoRa
  //Enviar paquete
  /*LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();*/
  counter++;
  //Código HX711
  //Leer peso
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 5);
  scale.power_down();
  delay(5000);
  scale.power_up();

  //delay(10000);
}