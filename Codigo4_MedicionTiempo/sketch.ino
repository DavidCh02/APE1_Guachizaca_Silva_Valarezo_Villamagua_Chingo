// APE 1 - Codigo 4: costo de digitalWrite() frente al acceso directo al registro
// Placa: Arduino UNO (ATmega328P @ 16 MHz) - simulacion en Wokwi 
const uint16_t N = 10000;

void setup() { Serial.begin(9600); pinMode(13, OUTPUT);

unsigned long t0 = micros();
for (uint16_t i = 0; i < N; i++) { digitalWrite(13, HIGH); digitalWrite(13, LOW);
}
unsigned long t1 = micros();
for (uint16_t i = 0; i < N; i++) { PORTB |= (1 << PORTB5);
PORTB &= ~(1 << PORTB5);
}
unsigned long t2 = micros();

Serial.print(F("digitalWrite : ")); Serial.print((t1 - t0) / (2.0 * N), 3); Serial.println(F(" us por escritura")); Serial.print(F("Registro	: "));
Serial.print((t2 - t1) / (2.0 * N), 3); Serial.println(F(" us por escritura"));
}

void loop() {}
