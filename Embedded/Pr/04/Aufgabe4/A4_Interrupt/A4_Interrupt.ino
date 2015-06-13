#include <avr/interrupt.h>
//### Anfang
//			Grundgeruest von der anderen Datei:
// Demo illustrating blinking led and reading of button.
// Led is finally turned off when button is pressed.
// define port for led output
const uint8_t LedPortOut = 13;
// define pin for button input
const uint8_t ButtonPinIn = 2;
// define delay for blinking in ms
const uint32_t Delay = 2000;
const uint32_t takt = 9600;
//! LED handling class. Has disable() function for emergency stop.
//! Parameter (in): PORT_NB (output port for connected led)
template <const uint8_t PORT_NB>
class TLed {
public:
//! Constructor takes state (HIGH, LOW) only if given.
//! Defaults: value for state = LOW, and is not disabled.
TLed(const uint8_t f_ledState = LOW)
: m_ledState(f_ledState), m_disabled(false) {
pinMode(PORT_NB, OUTPUT); // led is always output
digitalWrite(PORT_NB, m_ledState); // set led to default state
}
//! If this led is disable, nothing happens, otherwise
//! toggles state of led (from HIGH to LOW or from LOW to HIGH).
void toggle() {
if (m_disabled) // somehow no longer active
return;
if (m_ledState == LOW) { // toggle state
m_ledState = HIGH;
}
else {
m_ledState = LOW;
}
digitalWrite(PORT_NB, m_ledState); // set led to current state
}
//! Turn led finally off (emergency stop), state is set LOW, functionality off.
void off() {
m_disabled = true;
m_ledState = LOW;
digitalWrite(PORT_NB, m_ledState); // set led to current state
}
private:
uint8_t m_ledState; // current state of led
bool m_disabled; // disable flag (on if led is finally turned off)
};
//### Ende Grundgeruest
template <const uint8_t PIN_NB>
class TButton {
private:
  int buttonState;
public:
  TButton(const uint8_t fButtonState = LOW): buttonState(fButtonState) {
    pinMode(PIN_NB, INPUT); // led is always output
    digitalWrite(PIN_NB, buttonState);
   // buttonState=fButtonState;
  }
  int state(){
    buttonState = digitalRead(PIN_NB);
    return buttonState;
  }
};
// global instances for led output
TLed<LedPortOut> Led;
// and for button pin
TButton<ButtonPinIn> Button;
//Anfang
//		Grundgeruest vom Ende der anderen Datei
ISR(INTO_vect){
    if (Button.state()==HIGH){
	Led.off();
	Serial.println("blub");
    }
}
void setup(){
	Serial.begin(takt);
	pinMode(ButtonPinIn,INPUT);
/*
	SREG |= B10000000;
	EIMSK |= B00000001; //INT1
	EICRA = B00000010;	//ISC01 gesetzt
*/
    EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);     // Turns on INT0
    sei();                    // turn on interrupts
}
void loop() {
    if (Button.state() == HIGH) {
       Led.off();
    } else {
       Led.on();
    }
  
  // wait
delay(Delay);
}
//Ende Grundgeruest vom Ende



