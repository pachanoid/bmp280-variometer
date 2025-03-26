#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

// Crear objeto para el BMP280
Adafruit_BMP280 bmp;   //sin conectar el DO A 5V

// Definir pines para SoftwareSerial
SoftwareSerial miSerial(2, 3); // RX en el pin 10, TX en el pin 11

void setup() {
    Serial.begin(9600);    // Comunicación con el monitor serie
    miSerial.begin(9600);  // Comunicación con otro dispositivo

    // Iniciar el sensor BMP280
    if (!bmp.begin(0x76)) { // Dirección I2C del BMP280 (puede ser 0x77 en algunos modelos)
        Serial.println("¡No se encontró el BMP280!");
        while (1); // Detener ejecución si el sensor no está conectado
    }
}

void loop() {
    // Leer temperatura y presión del BMP280
    //float temperatura = bmp.readTemperature();
    float altura = bmp.readAltitude();

    // Crear un string con los datos
    String datos = String(altura, 2);

    // Enviar datos por SoftwareSerial
    miSerial.println(datos);

    // También mostrar en el monitor serie
    //Serial.println("Enviado: " + datos);

    delay(150); // Enviar cada 1 segundo
}