// our working data
uint8_t fibData[13];
void setup() {
// initialize Serial
Serial.begin(9600);
// init first two Fibonacci numbers
fibData[0] = 1;
fibData[1] = 1;
asm volatile(
 //TODO: insert program here
//"mov %2, %0" "\n\t"
//"add %0, %1" "\n\t"
//"mov %0, %1" "\n\t"
//"add %3, %2" "\n\t"
//"mov %4, %2" "\n\t"
//"add %4, %3" "\n\t"
//"mov %5, %3" "\n\t"
//"add %5, %4" "\n\t"
//"mov %6, %4" "\n\t"
//"add %6, %5" "\n\t"
//"mov %7, %5" "\n\t"
//"add %7, %6" "\n\t"
//"mov %8, %6" "\n\t"
//"add %8, %7" "\n\t"
//"mov %9, %7" "\n\t"
//"add %9, %8" "\n\t"
//"mov %A1, %8" "\n\t"
//"add %A1, %9" "\n\t"
//"mov %A2, %9" "\n\t"
//"add %A2, %A1" "\n\t"
//"nop"


"mov r20, %0"  "\n\t"
"mov r21, %1"  "\n\t"
"mov r18, r20 "  "\n\t"
"add r18, r21"  "\n\t"
"sts %0, r18"  "\n\t"

"mov r16, r21"  "\n\t"
"mov r17, r18"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts %1, r18"  "\n\t"

"mov r17, r18"  "\n\t"
"mov r18, r16 "  "\n\t"
"add r18, r17"  "\n\t"
"sts fibData+4, r18"  "\n\t"

"mov r17, r18"  "\n\t"
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

         : "=d" (fibData[2]),"=d" (fibData[3])
         : "d" (fibData[0]),"d" (fibData[1])
);
}
//"mov r30, %0;mov r29, %1;add r30,r29;mov %0, r30;\n;"
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
