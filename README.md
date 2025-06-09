# Practica 8 PD Ejercicio Voluntario: Escritura en Tarjeta SD tras Lectura de Etiqueta RFID

## Requisitos de Hardware
- **Microcontrolador**: ESP32 o cualquier placa compatible con Arduino.
- **Módulo de Tarjeta SD**: Compatible con la interfaz SPI (por ejemplo, el módulo referenciado en el documento original).
- **Módulo RFID**: Módulo MFRC522 compatible con SPI (por ejemplo, el módulo referenciado en el documento original).
- **Conexiones**:
  - Pines SPI para el módulo SD (VSPI predeterminado en ESP32):
    - MOSI: GPIO 23
    - MISO: GPIO 19
    - CLK: GPIO 18
    - CS: GPIO 4
  - Pines SPI para el módulo MFRC522 (usando los mismos pines SPI, pero con un CS diferente):
    - MOSI: GPIO 23
    - MISO: GPIO 19
    - CLK: GPIO 18
    - CS (SDA): GPIO 10
    - RST: GPIO 9

## Requisitos de Software
- **Entorno de Desarrollo**: Arduino IDE o PlatformIO.
- **Bibliotecas**: Bibliotecas estándar para SPI, manejo de tarjetas SD y control del módulo MFRC522.

## Funcionamiento
1. **Inicialización**:
   - Se inicia la comunicación serie a 9600 baudios para mostrar información de depuración en el monitor serie.
   - Se inicializa el bus SPI compartido para ambos dispositivos (SD y RFID).
   - Se inicializa el módulo de la tarjeta SD utilizando GPIO 4 como Chip Select (CS).
   - Se inicializa el módulo MFRC522 utilizando GPIO 10 como CS y GPIO 9 como Reset.

2. **Verificación de la Tarjeta SD**:
   - Se verifica que la tarjeta SD se inicialice correctamente. Si falla, se muestra un mensaje de error en el monitor serie y se detiene el proceso.
   - Si la inicialización es exitosa, se confirma con un mensaje en el monitor serie.

3. **Detección y Lectura de la Etiqueta RFID**:
   - El sistema comprueba continuamente si hay una nueva etiqueta RFID presente.
   - Si se detecta una etiqueta, se selecciona y se lee su UID (un conjunto de bytes único, normalmente 4 o 7 bytes).

4. **Escritura en la Tarjeta SD**:
   - Se abre un archivo en la tarjeta SD (por ejemplo, "rfid_log.txt") en modo escritura o anexado.
   - Si el archivo se abre correctamente, se escribe el UID de la etiqueta RFID en formato hexadecimal, seguido de una marca de tiempo o un separador para claridad.
   - Si no se puede abrir el archivo, se muestra un mensaje de error en el monitor serie.
   - El archivo se cierra tras cada escritura para garantizar la integridad de los datos.

5. **Bucle Principal**:
   - El sistema permanece en un bucle continuo, detectando nuevas etiquetas RFID y registrando sus UIDs en el archivo de la tarjeta SD.