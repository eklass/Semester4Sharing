// our working data
uint8_t fibData[13];
void setup() {
// initialize Serial
Serial.begin(9600);
// init first two Fibonacci numbers
fibData[0] = 1;
fibData[1] = 1;
asm volatile(

"add %0, fibData"  "\n\t"
"add %0, fibData"  "\n\t"

         : "=m" (fibData)
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
