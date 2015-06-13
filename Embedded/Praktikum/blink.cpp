// Arduino Uno PIN 13 is connected to PortB5 of ATMega328P

typedef unsigned char uint8_t; // set type for unsigned int 8

void simpleDelay(unsigned int f_iterations) {
    // loop with nop for delay
    for (unsigned long i = 0; i < f_iterations; ++i) {
        for (volatile unsigned long j = 0; j < 1000; ++j) ;
    }
}

int main() {
    // set direction of DDRB5 
    uint8_t *portAdd = (uint8_t*) 0x24; // DDRB address
    *portAdd |= 0x20; // set bit 5      

    for (;;) { // infinite loop 
        uint8_t *portB = (uint8_t*) 0x25; // PortB address
        *portB |= 0x20; // set bit 5
        simpleDelay(1000);
        asm volatile("cbi 0x5, 5\n\t"); // clear bit 5
        simpleDelay(1000);
    }
}
