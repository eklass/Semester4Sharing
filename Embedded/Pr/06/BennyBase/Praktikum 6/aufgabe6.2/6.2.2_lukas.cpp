// our working data
uint8_t fibData[13];
void setup() {
// initialize Serial
Serial.begin(9600);
// init first two Fibonacci numbers
fibData[0] = 1;
fibData[1] = 1;

//Taktzyklen: (2 + 2 + 1 + 1 + 2) * 12 = 96

asm volatile(
"lds r16, fibData"  "\n\t"
"lds r17, fibData+1"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+2, r18"  "\n\t"

"lds r16, fibData+1"  "\n\t"
"lds r17, fibData+2"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+3, r18"  "\n\t"

"lds r16, fibData+2"  "\n\t"
"lds r17, fibData+3"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+4, r18"  "\n\t"

"lds r16, fibData+3"  "\n\t"
"lds r17, fibData+4"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+5, r18"  "\n\t"

"lds r16, fibData+4"  "\n\t"
"lds r17, fibData+5"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+6, r18"  "\n\t"

"lds r16, fibData+5"  "\n\t"
"lds r17, fibData+6"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+7, r18"  "\n\t"

"lds r16, fibData+6"  "\n\t"
"lds r17, fibData+7"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+8, r18"  "\n\t"

"lds r16, fibData+7"  "\n\t"
"lds r17, fibData+8"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+9, r18"  "\n\t"

"lds r16, fibData+8"  "\n\t"
"lds r17, fibData+9"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+10, r18"  "\n\t"

"lds r16, fibData+9"  "\n\t"
"lds r17, fibData+10"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+11, r18"  "\n\t"

"lds r16, fibData+10"  "\n\t"
"lds r17, fibData+11"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+12, r18"  "\n\t"

"lds r16, fibData+11"  "\n\t"
"lds r17, fibData+12"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+13, r18"  "\n\t"

);
}
// main loop
void loop() {
// print data
for (int i = 0; i < 13; i++)
{
Serial.println(fibData[i]);
}
// delay 1s
delay(1000);
}