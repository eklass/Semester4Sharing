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
"add r24,r24\n;"
         : "=d" (number)
         : "0" ((number>0 && number<128) ? number : 1)
);
//TODO: insert program here
    //LDS r15, _number;
    //ADD r15,0x01;     
     //printf("%d\n", number);
}
