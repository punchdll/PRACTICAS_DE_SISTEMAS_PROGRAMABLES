const int RELAY = 8;
const int SENSOR = A0;


const float UMBRAL_DE_TEMPERATURA = 29;

const int SENSIBILIDAD_DEL_SENSOR = 10;
const int REFERNCIA_TEMPERATURA = 25;
const int REFERENCIA_VOLTAJE = 250;
const float HISTERESIS = 0.1;

const float ORDENADA = REFERENCIA_VOLTAJE - (SENSIBILIDAD_DEL_SENSOR * REFERNCIA_TEMPERATURA); 

inline float calcular_temperatura (float voltaje){
  return ((voltaje * 1000 - ORDENADA) / SENSIBILIDAD_DEL_SENSOR);
}

inline float calcular_voltaje(int lectura_discreta){
    return ((float)lectura_discreta / 1023) * 1.1;
}
void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  analogReference(INTERNAL);
}

void loop() {

  int lectura = analogRead(SENSOR);

  float voltaje = calcular_voltaje(lectura);
  float temperatura = calcular_temperatura(voltaje);

  // IMPRESIONES SERIALES
  Serial.print("\r\033[33mLECTURA SENSOR: ");
  Serial.print(lectura);

  Serial.print("\033[34m  VOLTAJE: ");
  Serial.print(voltaje * 1000);
  Serial.print(" mV");

  Serial.print("\033[35m  TEMPERATURA: ");
  Serial.print(temperatura);
  Serial.print(" °C\033[0m");

  if (temperatura < (\034[mUMBRAL_DE_TEMPERATURA - HISTERESIS)){
    digitalWrite(RELAY, LOW);
  }
  else if (temperatura > (UMBRAL_DE_TEMPERATURA + HISTERESIS)){
    digitalWrite(RELAY, HIGH);
  }
  delay(1000);

}
