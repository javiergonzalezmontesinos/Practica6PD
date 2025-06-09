# Practica 8 PD Ejercicio Práctico 2: Lectura de Etiqueta RFID

## Requisitos de Hardware
- **Microcontrolador**: ESP32 o cualquier placa compatible con Arduino.
- **Módulo RFID**: Módulo MFRC522 compatible con SPI.
- **Conexiones**:
  - Pines SPI (configuración predeterminada para VSPI en ESP32):
    - MOSI: GPIO 23
    - MISO: GPIO 19
    - CLK: GPIO 18
    - CS (SDA): GPIO 10
    - RST: GPIO 9

## Funcionamiento
1. **Inicialización**:
   - Se inicia la comunicación serie a 9600 baudios para mostrar información en el monitor serie.
   - Se inicializa el bus SPI y el módulo MFRC522.
   - Se muestra un mensaje inicial indicando que se está listo para leer el UID de una tarjeta RFID.
2. **Detección de Tarjetas**:
   - En el bucle principal, se verifica constantemente si hay una nueva tarjeta RFID presente.
   - Si se detecta una tarjeta, se intenta seleccionarla para leer sus datos.
3. **Lectura del UID**:
   - Si la tarjeta se selecciona correctamente, se lee su UID (un conjunto de bytes único).
   - El UID se envía al monitor serie en formato hexadecimal, con un formato que asegura que cada byte se muestre con dos dígitos (agregando un "0" inicial si es necesario).
4. **Finalización**:
   - Una vez leído el UID, se detiene la comunicación con la tarjeta para permitir la detección de nuevas tarjetas.