#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <HTTPClient.h>

//Definir pines
#define ss 5
#define rst 14
#define dio0 2

//Datos WiFi
const char* ssid = "Juanchooo";
const char* password = "WhySoSerious?";

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
  //Inicializar WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Esperar paquete
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Paquete recibido
    Serial.print("Received packet '");
    String LoRaData;
    // Leer paquete
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // Imprimir RSSI
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    // Enviar datos a PHP
    HTTPClient http;
    http.begin("http://192.168.63.204/insert_LoRa.php?data="+ LoRaData);
    int httpCode = http.GET();
    if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
      } else {
        Serial.printf("HTTP GET... code: %d\n", httpCode);
      }
    } else {
      Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}