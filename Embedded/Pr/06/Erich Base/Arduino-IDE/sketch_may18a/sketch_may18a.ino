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
  asm volatile("add r16, r17"
  : /* Keine Output-Operanden */
  : "a" (addr)
  : "r16"
  
  /* Addition der Register r16 und r17. Das Ergebnis wird im Register r16 abgelegt*/
  
); }
