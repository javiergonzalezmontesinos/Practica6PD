#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

// Configuración de pines para ESP32-WROOM-32D
#define SD_CS 5  // GPIO5 como Chip Select (ajustar según conexión)

File myFile;

void setup() {
    Serial.begin(9600); // Mantenemos 9600 como en el original
    Serial.print("Iniciando SD ...");
    
    // Inicialización SPI con el pin CS correcto
    if (!SD.begin(SD_CS)) {
        Serial.println("No se pudo inicializar");
        Serial.println("Verifique conexión en pin GPIO" + String(SD_CS));
        return;
    }
    Serial.println("inicializacion exitosa");

    // Abrir archivo (solo lectura como en el original)
    myFile = SD.open("/archivo.txt"); // Path absoluto recomendado
    if (myFile) {
        Serial.println("archivo.txt:");
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close();
    } else {
        Serial.println("Error al abrir el archivo");
    }
}

void loop() {
    // Vacío como en el original
}