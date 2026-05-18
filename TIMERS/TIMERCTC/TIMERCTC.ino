void setup() {
  cli();
  DDRB |= (1 << DDB0);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12);
  OCR1A = 24999;
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

ISR(TIMER1_COMPA_vect) {
  PORTB ^= (1 << PORTB0);
}

void loop() {
}