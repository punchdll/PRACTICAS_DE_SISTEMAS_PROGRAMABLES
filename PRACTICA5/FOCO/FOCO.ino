#define PIN_OUTPUT 7
#define PIN_INPUT A0
#define THRESHOLD 40

#define LIGHT

int input_value;
int input_percent;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_OUTPUT, OUTPUT);
}

void loop() {
  input_value = analogRead(PIN_INPUT);
  input_percent = map(input_value, 0, 1023, 0, 100);

  Serial.print("Valor: ");
  Serial.print(input_value);
  Serial.print(" | Porcentaje: ");
  Serial.println(input_percent);

  #ifdef LIGHT
  if (input_percent <= THRESHOLD) {
    digitalWrite(PIN_OUTPUT, HIGH);
  } else {
    digitalWrite(PIN_OUTPUT, LOW);
  }
  #endif

  #ifndef LIGHT
  if (input_percent >= THRESHOLD) {
    digitalWrite(PIN_OUTPUT, HIGH);
  } else {
    digitalWrite(PIN_OUTPUT, LOW);
  }
  #endif

  delay(100);
}
