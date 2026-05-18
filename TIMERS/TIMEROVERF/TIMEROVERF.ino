void setup() {
  cli();
  DDRD |= (1 << DDD4);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 3035;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  sei();
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 3035;
  PORTD ^= (1 << PORTD4);
}

void loop() {
}