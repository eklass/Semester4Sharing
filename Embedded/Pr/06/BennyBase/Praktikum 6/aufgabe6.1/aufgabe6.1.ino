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
"lsl %0\n;"				//LSL benoetigt 1 Taktzyklus
         : "=d" (number)
         : "0" ((number>0 && number<128) ? number : 1)
);
//TODO: insert program here
    //LDS r15, _number;				//LDS benoetigt 2 Taktzyklen 
    //ADD r15,0x01;					//ADD benoetigt 1 Taktzyklus
     //printf("%d\n", number);
}
