const int RELAY = 7;
const int SENSOR = A0;

// ∘C
const float UMBRAL_DE_TEMPERATURA = 0;

//Referencias
// mV / ∘C
const int SENSIBILIDAD_DEL_SENSOR = 10;
const int REFERNCIA_TEMPERATURA = 25;
const int REFERENCIA_VOLTAJE = 750;

const float ORDENADA = REFERENCIA_VOLTAJE - (SENSIBILIDAD_DEL_SENSOR * REFERNCIA_TEMPERATURA); 

inline float calcular_temperatura (float voltaje){
  return ((voltaje * 1000 - ORDENADA) / SENSIBILIDAD_DEL_SENSOR);
}


inline float calcular_voltaje(int lectura_discreta){
    return ((float)lectura_discreta / 1024) * 5;
}
void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
}

void loop() {

  int lectura = analogRead(SENSOR);
  float voltaje = calcular_voltaje(lectura);
  float temperatura = calcular_temperatura(voltaje);

  // IMPRESIONES SERIALES
  Serial.print("LECTURA DISCRETA: ");
  Serial.println(lectura);

  Serial.print("VOLTAJE: ");
  Serial.print(voltaje * 1000);
  Serial.println(" mV");

  Serial.print("TEMPERATURA: ");
  Serial.print(temperatura);
  Serial.println(" ∘C");


  if (temperatura < UMBRAL_DE_TEMPERATURA){
    digitalWrite(RELAY, LOW);
  }
  else{
    digitalWrite(RELAY, HIGH);
  }
  delay(1000);

}
