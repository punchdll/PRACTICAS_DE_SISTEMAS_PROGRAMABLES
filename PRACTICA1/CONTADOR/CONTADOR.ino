const int SALIDAS [] = {10, 11, 12, 13};

const int INCREMENTO = 6;
const int DECREMENTO = 7;

const int ESPERA = 500;

const int BITS = 4;
const int MAX = (1 << BITS) - 1;
const int MIN = 0;

int contador = 0;
int estado_boton_incremento = 0;
int estado_boton_decremento = 0;

inline int estado_de_bit(int posicion, int secuencia);

void setup(){
    for (int PIN : SALIDAS){
        pinMode(PIN, OUTPUT);
    }

    pinMode(INCREMENTO, INPUT_PULLUP);
    pinMode(DECREMENTO, INPUT_PULLUP);
}

void loop(){

    estado_boton_incremento = digitalRead(INCREMENTO);
    estado_boton_decremento = digitalRead(DECREMENTO);

    if (!estado_boton_incremento){
        if(contador < MAX){
            ++contador;
        }

    }
    else if (!estado_boton_decremento){
        if(contador > MIN){
            --contador;
        }
    }

    for (int PIN : SALIDAS){
        digitalWrite(PIN, estado_de_bit(PIN-SALIDAS[0], contador));
    }

    delay(ESPERA);
}

inline int estado_de_bit(int posicion, int secuencia){
     return secuencia & (1 << posicion)? HIGH: LOW;
}
