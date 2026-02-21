const int LED_1 = 9;
const int LED_2 = 10;
const int POTENCIOMETRO_1 = A0;
const int POTENCIOMETRO_2 = A1;
const int WIPER_MAX = 1023;
const int VOLTAJE_MAX = 5;
const int UMBRAL_INFERIOR = 2;
const int UMBRAL_SUPERIOR = 4;

float voltaje_potenciometro_1 = 0;
float voltaje_potenciometro_2 = 0;

inline float voltaje(int lectura_discreta){
    return ((float)lectura_discreta / WIPER_MAX) * VOLTAJE_MAX;
}

void setup(){
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
}

void loop(){

     voltaje_potenciometro_1 = voltaje(analogRead(POTENCIOMETRO_1));
     voltaje_potenciometro_2 = voltaje(analogRead(POTENCIOMETRO_2));

     if(voltaje_potenciometro_1 >= UMBRAL_INFERIOR && voltaje_potenciometro_2 >= UMBRAL_INFERIOR){
         digitalWrite(LED_1, HIGH);
     }
     else{
         digitalWrite(LED_1, LOW);
     }

     if(voltaje_potenciometro_1 <=UMBRAL_SUPERIOR && voltaje_potenciometro_2 <= UMBRAL_SUPERIOR){
         digitalWrite(LED_2, HIGH);
     }
     else{
         digitalWrite(LED_2, LOW);
     }
}
