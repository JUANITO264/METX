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

//Variables
int peso;

int counter = 0;

//Crea objeto HX711
HX711 scale;

void setup() {
 //Inicializar puerto serie
  Serial.begin(115200);
  
  //Inicializar LoRa
  LoRa.setPins(ss, rst, dio0);
  
  //Frecuencia de operación de LoRa
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  //Sincronización de palabra de LoRa
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  //Inicializar HX711
  setCpuFrequencyMhz(80); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(-6.552);
  scale.tare();
  Serial.println("HX711 Initializing OK!");
}

void loop() {
    //Código HX711
  //Leer peso
  //peso=round(scale.get_units()); con la galga se descomenta
  peso=random(10000); //comentar si se usa la galga
  Serial.print("Peso: ");
  Serial.println(peso);
  scale.power_down();
  delay(5000);
  scale.power_up();
  //Código LoRa
  //Enviar paquete
  LoRa.beginPacket();
  LoRa.print(peso);
  LoRa.endPacket();
  counter++;
  delay(10000);
}