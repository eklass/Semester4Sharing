
void an(int time)
{
   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(time);              // wait for a second
}

void aus(int time)
{
   digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
   delay(time);              // wait for a second
}

void setup() {
   pinMode(13, OUTPUT);
}

void loop() {
  an(1000);
  aus(1000);
  an(1000);
  aus(4000);
}

