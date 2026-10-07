/*
  APE 1 - Código 3: Laboratorio de bits
  Placa: Arduino UNO (ATmega328P @ 16 MHz) - Simulación en Wokwi
  Circuito: LEDs en PB0..PB3 (D8..D11) | Pulsador en PD2 (D2) | LED L en PB5 (D13)
*/

#include <Arduino.h>

const uint8_t MASK_LEDS = 0x0F;                // Máscara 0b00001111 para PB0..PB3
const uint8_t NUM_MODOS = 3;
const uint8_t PATRON_INICIAL[NUM_MODOS] = {0b0000, 0b0001, 0b0101};
const unsigned long PERIODO_MS = 300;

uint8_t modo = 0;
uint8_t patron = PATRON_INICIAL[0];
uint8_t btnAnterior = 1;                        // Lectura inicial con Pull-Up (alto)
unsigned long tAnterior = 0;

// Imprime un entero de 8 bits en formato binario exacto en el Monitor Serie
void imprimirBin8(const char *etiqueta, uint8_t v) {
  Serial.print(etiqueta);
  for (int8_t i = 7; i >= 0; i--) {
    Serial.print((v >> i) & 1);
  }
  Serial.println();
}

// Actualiza los LEDs en PB0..PB3 conservando el estado previo del LED L en PB5
void escribirLeds(uint8_t valor) {
  PORTB = (PORTB & ~MASK_LEDS) | (valor & MASK_LEDS);
}

// Muestra operaciones lógicas bit a bit en la consola
void demoOperaciones() {
  uint8_t a = 0b11001100;
  uint8_t b = 0b10101010;
  imprimirBin8("a      = ", a);
  imprimirBin8("b      = ", b);
  imprimirBin8("a & b  = ", a & b);
  imprimirBin8("a | b  = ", a | b);
  imprimirBin8("a ^ b  = ", a ^ b);
  imprimirBin8("~a     = ", (uint8_t)~a);
  imprimirBin8("a << 1 = ", (uint8_t)(a << 1));
  imprimirBin8("a >> 2 = ", a >> 2);
  Serial.print("~a sin cast, en BIN: ");
  Serial.println(~a, BIN);
}

void setup() {
  // Configuración de puertos
  DDRB |= MASK_LEDS | (1 << DDB5);             // PB0..PB3 y PB5 como salidas
  DDRD &= ~(1 << DDD2);                        // PD2 como entrada
  PORTD |= (1 << PORTD2);                      // Pull-Up activo en PD2

  Serial.begin(9600);
  Serial.println(F("APE 1 - Laboratorio de bits"));
  demoOperaciones();
  escribirLeds(patron);
}

void loop() {
  // Lectura directa del registro de entrada PIND (Bit 2)
  uint8_t btn = (PIND >> PIND2) & 1;           
  
  // Detección de flanco de bajada (pulsador presionado a GND)
  if (btnAnterior == 1 && btn == 0) {
    modo = (modo + 1) % NUM_MODOS;
    patron = PATRON_INICIAL[modo];
    Serial.print(F("Modo: "));
    Serial.println(modo);
  }
  btnAnterior = btn;

  // Temporización no bloqueante
  if (millis() - tAnterior >= PERIODO_MS) {
    tAnterior = millis();
    switch (modo) {
      case 0: // Secuencia 0: Contador binario
        patron = (patron + 1) & MASK_LEDS;
        break;
      case 1: // Secuencia 1: Rotación de bit a la izquierda
        patron = ((patron << 1) | (patron >> 3)) & MASK_LEDS;
        break;
      case 2: // Secuencia 2: Parpadeo/Inversión con máscara
        patron ^= MASK_LEDS;
        break;
    }
    escribirLeds(patron);
    PINB = (1 << PINB5);                       // Conmuta estado del LED L
    imprimirBin8("PORTB  = ", PORTB);
  }
}