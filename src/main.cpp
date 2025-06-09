#include <Arduino.h>

#include <SPI.h>
#include <MFRC522.h>

// Configuración de pines para ESP32-WROOM-32D
#define RST_PIN 22   // GPIO22 para RST (puedes cambiarlo)
#define SS_PIN  21   // GPIO21 para SS/SDA (puedes cambiarlo)

MFRC522 mfrc522(SS_PIN, RST_PIN); // Crea instancia del lector

void setup() {
    Serial.begin(9600); // Misma velocidad que el original
    while(!Serial);     // Espera a que se conecte el monitor serial
    
    SPI.begin();        // Inicializa el bus SPI
    
    mfrc522.PCD_Init(); // Inicializa el lector RFID
    delay(4);          // Pequeña pausa necesaria
    
    Serial.println("Sistema RFID inicializado en ESP32-WROOM-32D");
    Serial.println("Acerca una tarjeta RFID al lector...");
}

void loop() {
    // Revisa si hay una tarjeta presente
    if (mfrc522.PICC_IsNewCardPresent()) {
        // Intenta leer el UID de la tarjeta
        if (mfrc522.PICC_ReadCardSerial()) {
            Serial.print("UID de la tarjeta:");
            
            // Muestra el UID en formato hexadecimal
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
            }
            Serial.println();
            
            // Detiene la comunicación con la tarjeta
            mfrc522.PICC_HaltA();
        }
    }
    delay(250); // Pequeña pausa entre lecturas
}