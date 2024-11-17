#include <SPI.h>
#include <LoRa.h>
#include <Arduino.h>
#include "HX711.h"
#include "DHT.h"

//Definir pines de LoRa
#define ss 5
#define rst 14
#define dio0 2

//Definir pines de HX711
const int LOADCELL_DOUT_PIN = 22;
const int LOADCELL_SCK_PIN = 21;

//Definir pines de DHT
#define DHT1PIN 32
#define DHT2PIN 33
//Definir tipo de DHT
#define DHTTYPE DHT22 
//Variables
int peso;


//Crea objeto HX711
HX711 scale;
#define CALIBRATION_FACTOR -471.497

//Crea objeto DHT
DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);

void setup() {
 //Inicializar puerto serie
  Serial.begin(115200);
  
  //Inicializar LoRa
  /*LoRa.setPins(ss, rst, dio0);
  
  //Frecuencia de operación de LoRa
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  //Sincronización de palabra de LoRa
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa OK!");

  //Inicializar HX711
  setCpuFrequencyMhz(80); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR); 
  scale.tare();
  Serial.println("HX711 OK!");*/
  //Inicializar DHT
  dht1.begin();
  Serial.println("DHT1 OK!");
  dht2.begin();
  Serial.println("DHT2 OK!");
}

void loop() {
  /*//Código HX711
  //Leer peso
  scale.power_up();
  //peso=round(scale.get_units()); con la galga se descomenta
  peso=random(10000); //comentar si se usa la galga
  Serial.print("Peso: ");
  Serial.println(peso);
  scale.power_down();*/
  //Código DHT
  //Leer temperatura y humedad
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  //Comprobar si la lectura es correcta
  if (isnan(h1) || isnan(t1)) {
    Serial.println(F("Fallo de Lectura DHT"));
    return;
  }
  Serial.print(F("Humedad Interna: "));
  Serial.print(h1);
  Serial.print(F("%  Temperatura Interna: "));
  Serial.print(t1);
  Serial.print(F("°C "));
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  //Comprobar si la lectura es correcta
  if (isnan(h2) || isnan(t2)) {
    Serial.println(F("Fallo de Lectura DHT"));
    return;
  }
  Serial.print(F("Humedad Externa: "));
  Serial.print(h2);
  Serial.print(F("%  Temperatura Externa: "));
  Serial.println(t2);
  /*//Código LoRa
  //Enviar paquete
  LoRa.beginPacket();
  LoRa.print(peso);
  LoRa.print("/");
  LoRa.endPacket();
  counter++;*/
  delay(10000);
}