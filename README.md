# Practica 8 PD Ejercicio Práctico 1: Lectura/Escritura de Memoria SD


## Requisitos de Hardware
- **Microcontrolador**: ESP32 o cualquier placa compatible con Arduino.
- **Módulo de Tarjeta SD**: Compatible con la interfaz SPI.
- **Conexiones**:
  - Pines SPI (configuración predeterminada para VSPI en ESP32):
    - MOSI: GPIO 23
    - MISO: GPIO 19
    - CLK: GPIO 18
    - CS: GPIO 4 (según la configuración del ejercicio)


## Funcionamiento
1. **Inicialización**:
   - Se inicia la comunicación serie a 9600 baudios para mostrar información de depuración en el monitor serie.
   - Se intenta inicializar el módulo de la tarjeta SD utilizando el pin GPIO 4 como Chip Select (CS).
2. **Verificación de la Tarjeta SD**:
   - Si la inicialización de la tarjeta SD falla, se muestra un mensaje de error en el monitor serie y se detiene el proceso.
   - Si la inicialización es exitosa, se muestra un mensaje confirmando el éxito.
3. **Lectura del Archivo**:
   - Se intenta abrir un archivo llamado "archivo.txt" en la tarjeta SD.
   - Si el archivo se abre correctamente, se leen sus datos byte por byte y se envían al monitor serie.
   - Si no se puede abrir el archivo, se muestra un mensaje de error.
4. **Cierre del Archivo**:
   - Una vez leídos los datos, se cierra el archivo para liberar recursos.
5. **Bucle Principal**:
   - No se realizan acciones en el bucle principal, ya que la operación se ejecuta solo una vez durante la inicialización.