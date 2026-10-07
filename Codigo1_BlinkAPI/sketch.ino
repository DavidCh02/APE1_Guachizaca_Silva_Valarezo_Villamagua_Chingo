/*
  APE 1 - Código 1: Blink con la API de Arduino
  Placa: Arduino UNO (ATmega328P @ 16 MHz) - Simulación en Wokwi
*/

void setup() {
  pinMode(13, OUTPUT); // Configura el pin D13 (PB5) como salida digital
}

void loop() {
  digitalWrite(13, HIGH); // Enciende el LED "L"
  delay(500);            // Retardo de 500 ms
  digitalWrite(13, LOW);  // Apaga el LED "L"
  delay(500);            // Retardo de 500 ms
}