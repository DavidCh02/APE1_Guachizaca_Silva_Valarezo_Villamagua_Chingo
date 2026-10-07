/*
  APE 1 - Código 2: Blink escribiendo registros directamente
  Placa: Arduino UNO (ATmega328P @ 16 MHz) - Simulación en Wokwi
  Regla: Sin uso de pinMode() ni digitalWrite()
*/

void setup() {
  // Configura PB5 (Pin D13) como salida usando manipulación de bits
  DDRB |= (1 << DDB5);
}

void loop() {
  // Conmutación del LED mediante operador XOR atómico
  PORTB ^= (1 << PORTB5); 
  delay(500);

  /*
    Variantes probadas en la práctica:
    
    // B2: Encendido y apagado explícito
    // PORTB |= (1 << PORTB5);
    // delay(500);
    // PORTB &= ~(1 << PORTB5);
    // delay(500);

    // B3: Conmutación atómica escribiendo 1 en el registro de entrada (PINB)
    // PINB = (1 << PINB5);
    // delay(500);
  */
}