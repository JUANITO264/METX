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
const int LOADCELL_DOUT_PIN = 21;
const int LOADCELL_SCK_PIN = 22;

//Definir pines de DHT
#define DHT1PIN 32
#define DHT2PIN 33

//Definir tipo de DHT
#define DHTTYPE DHT22 

//Definir pines de KY-037
#define sonin 25
#define sonout 26

//Variables
int peso;
int sonidoin;
int sonidoout;

//Crea objeto HX711
HX711 scale;

//Crea objeto DHT
DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);

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
  Serial.println("LoRa OK!");

  //Inicializar HX711
  setCpuFrequencyMhz(80); 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(); 
  scale.tare();
  Serial.println("HX711 OK!");
  //Inicializar DHT
  dht1.begin();
  Serial.println("DHT1 OK!");
  dht2.begin();
  Serial.println("DHT2 OK!");
  //Inicializar KY-037
  pinMode(sonin, INPUT);
  pinMode(sonout, OUTPUT);
  Serial.println("KY-037 OK!");
}

void loop() {
  //Código HX711
  //Leer peso
  scale.power_up();
  peso=scale.get_units(10);
  peso*=-1000./1008604.;
  Serial.print("Peso: ");
  Serial.println(peso);
  scale.power_down();
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
  //Código KY-037
  //Leer sonido
  //sonidoin = analogRead(sonin); con el micrófono se descomenta
  sonidoin = random(4096); //comentar si se usa el micrófono
  Serial.print("Sonido Interno: ");
  Serial.println(sonidoin);
  //sonidoout = analogRead(sonout); con el micrófono se descomenta
  sonidoout = random(4096); //comentar si se usa el micrófono
  Serial.print("Sonido Externo: ");
  Serial.println(sonidoout);
  //Código LoRa
  //Enviar paquete
  LoRa.beginPacket();
  LoRa.print(peso);
  LoRa.print("/");
  LoRa.print(t1);
  LoRa.print("/");
  LoRa.print(t2);
  LoRa.print("/");
  LoRa.print(h1);
  LoRa.print("/");
  LoRa.print(h2);
  LoRa.print("/");
  LoRa.print(sonidoin/40.96);
  LoRa.print("/");
  LoRa.print(sonidoout/40.96);
  LoRa.endPacket();
  delay(60000);
}