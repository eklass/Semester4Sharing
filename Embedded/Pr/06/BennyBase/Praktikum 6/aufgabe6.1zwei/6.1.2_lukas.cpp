
// our working number
volatile uint8_t number = 1;
// initialize Serial
void setup() {
Serial.begin(9600);
}
// main loop
void loop() {
// print number
Serial.println(number);

asm volatile(
"lds r24, number"   "\n\t"   //r24 <- number
"lsl r24"   "\n\t"           //left shift r24 (= r24*2)
"sts number, r24"  "\n\t"    //number <- r24

"ldi r25, 0"  "\n\t"       //r25 <- 128
"cp r25,r24"  "\n\t"         // r25 == r24
"brne noteq"  "\n\t"         // if not equal jump to noteq
"ldi r26, 1"  "\n\t"         //case: equal r26 <- 1
"sts number, r26"  "\n\t"    //number <- r26
"noteq: nop"  "\n\t"         //case not equal: do nothing
);
//Taktzyklen: 2 + 1 + 2 + 1 + 1 + (1\2) + 1 + 2 + (1\2) = 11 \ 12
}

 