#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebServer.h>
#include "time.h"

// 1. Configuración según enunciado
#define SD_CS 5       // Usar HSPI (GPIO14 CLK, GPIO12 MISO, GPIO13 MOSI)
#define RFID_SS 15    // Usar VSPI (GPIO18 CLK, GPIO19 MISO, GPIO23 MOSI)
#define RFID_RST 22

// 2. Compartición SPI como indica la práctica
/* 
   HSPI: SD Card
   VSPI: RFID
   Así evitamos conflictos usando buses SPI separados
*/

// Credenciales WiFi
const char* ssid = "Oneplus";
const char* password = "159635741ja";

// Configuración NTP
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

// Instancias
SPIClass hspi(HSPI);  // Para SD
SPIClass vspi(VSPI);  // Para RFID
MFRC522 mfrc522(RFID_SS, RFID_RST);
WebServer server(80);

// Archivo de logs
const char* logFile = "/rfid_log.txt";

void setup() {
  Serial.begin(115200);
  
  // 3. Inicialización dual SPI como indica el hardware del ESP32
  Serial.println("Iniciando buses SPI...");
  hspi.begin(14, 12, 13, SD_CS); // HSPI para SD
  vspi.begin(18, 19, 23, RFID_SS); // VSPI para RFID
  
  // Configurar RFID
  mfrc522.PCD_Init();
  Serial.println("Lector RFID listo");

  // Iniciar SD card
  if(!SD.begin(SD_CS, hspi)) {
    Serial.println("Error en tarjeta SD!");
    return;
  }
  Serial.println("SD card lista");

  // Conectar WiFi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado! IP: " + WiFi.localIP().toString());

  // Configurar hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // 4. Configurar servidor web como pide el enunciado
  server.on("/", HTTP_GET, [](){
    String html = "<html><head><title>Registro RFID</title>";
    html += "<meta http-equiv='refresh' content='5'>";
    html += "<style>table {width:100%; border-collapse:collapse;}";
    html += "th,td {border:1px solid #ddd; padding:8px;}";
    html += "tr:nth-child(even){background-color:#f2f2f2;}</style>";
    html += "</head><body><h1>Lecturas RFID</h1><table>";
    html += "<tr><th>Fecha</th><th>Hora</th><th>UID</th></tr>";

    File file = SD.open(logFile);
    if(file) {
      while(file.available()) {
        String line = file.readStringUntil('\n');
        // Formato: 2023-11-20 14:30:45 - UID: XX:XX:XX:XX
        int sep = line.indexOf(" - UID: ");
        if(sep != -1) {
          String fechaHora = line.substring(0, sep);
          String uid = line.substring(sep + 7);
          html += "<tr><td>" + fechaHora.substring(0, 10) + "</td>";
          html += "<td>" + fechaHora.substring(11) + "</td>";
          html += "<td>" + uid + "</td></tr>";
        }
      }
      file.close();
    }
    html += "</table></body></html>";
    server.send(200, "text/html", html);
  });
  server.begin();
}

void loop() {
  server.handleClient();
  
  // 5. Lectura RFID y registro como pide el enunciado
  if(mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Obtener UID
    String uid = "";
    for(byte i = 0; i < mfrc522.uid.size; i++) {
      uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      uid += String(mfrc522.uid.uidByte[i], HEX);
      if(i < mfrc522.uid.size-1) uid += ":";
    }

    // Obtener fecha/hora
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)) {
      Serial.println("Error al obtener hora");
      return;
    }
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);

    // Registrar en SD
    File file = SD.open(logFile, FILE_APPEND);
    if(file) {
      file.print(timeStr);
      file.print(" - UID: ");
      file.println(uid);
      file.close();
      Serial.println("Registro guardado: " + String(timeStr) + " - " + uid);
    } else {
      Serial.println("Error al abrir archivo");
    }

    mfrc522.PICC_HaltA();
  }
  delay(250);
}