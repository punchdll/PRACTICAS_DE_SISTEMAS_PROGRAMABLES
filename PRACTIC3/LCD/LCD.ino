#include <LiquidCrystal.h>

const int RS = 2;
const int ENABLE = 3;
const int SENSOR = 7;
const int RESET = 4;

const int CONTANDO = 0;
const int NO_CONTANDO = 1;

int contador =  0;
int estado =  0;

LiquidCrystal lcd(RS, ENABLE, 8, 9, 10, 11);

void setup() {
  pinMode(SENSOR, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  lcd.begin(16, 2);
}

void loop() {

  int objeto = !digitalRead(SENSOR);
  int reset = !digitalRead(RESET);

  if (reset){
    contador = 0;
  }

  if(objeto){
    if(estado == CONTANDO){
      contador++;
      estado = NO_CONTANDO;
    }
  }
  else{
    estado = CONTANDO;
  }

  lcd.setCursor(0,0);
  lcd.print("CONTEO: ");
  lcd.print(contador);
  lcd.print("            ");

  delay(100);
}
