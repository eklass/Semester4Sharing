// Arduino Uno PIN 13 is connected to PORTB5 of ATMega328

void simpleDelay(unsigned int f_iterations) {
    // loop with nop for delay
    for (unsigned long i = 0; i < f_iterations; ++i) {
        for (volatile unsigned long j = 0; j < 1000; ++j) ;
    }
}

void setup() {
  // set direction of DDRB5
  uint8_t *portAdd = (uint8_t*) 0x24; // DDRB address 
  *portAdd |= 0x20; // set bit 5
}

void loop() {
  // set and clear PortB5
  uint8_t *pinB = (uint8_t*) 0x25; // PortB address 
  *pinB |= 0x20; // set bit 5
  simpleDelay(1000);
  *pinB &= 0xDF; // clear bit 5
  simpleDelay(1000);
}
