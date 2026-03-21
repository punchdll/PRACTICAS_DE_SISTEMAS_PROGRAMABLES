#include "pinout.h"
#include "HC-SR04/hcsr04.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "container.h"
#include "pump.h"
#include <stdint.h>

static LiquidCrystal_I2C lcd(0x27,16,2);

static uint8_t mode = AUTO;
static uint8_t filling = false;

void setup() {
  Wire.begin();

  // Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(ECHO, INPUT);
  
  pinMode(B_START, INPUT_PULLUP);
  pinMode(B_STOP, INPUT_PULLUP);
  pinMode(B_AUTO, INPUT_PULLUP);

  pinMode(SELECTOR, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(LOW_INDICATOR, OUTPUT);
  pinMode(HIGH_INDICATOR, OUTPUT);

}

void loop() {

  uint8_t distancia = hcsr04_centimeter(ECHO, TRIGGER);
  uint8_t porcentaje = container_percent(distancia);
  uint8_t nivel = container_level(porcentaje);

  // Serial.print(distancia);

  if (!digitalRead(B_START)){
    mode = MANUAL;
    filling = true;
    digitalWrite(SELECTOR, HIGH); 
  }
  else if (!digitalRead(B_STOP)){
    mode = MANUAL;
    filling = false;
    digitalWrite(SELECTOR, LOW); 
  }
  else if (!digitalRead(B_AUTO)){
    mode = AUTO;
  }

  if (mode == AUTO){
    if (porcentaje >= CONTAINER_MAX_PERCENT){
      digitalWrite(SELECTOR, LOW);
      filling = false;
    }
    else{
      digitalWrite(SELECTOR, HIGH);
      filling = true;
    }
  }

  if(nivel == CONTAINER_HIGH){
    digitalWrite(HIGH_INDICATOR, HIGH);
    digitalWrite(LOW_INDICATOR, LOW);
  }
  else{
    digitalWrite(LOW_INDICATOR, HIGH);
    digitalWrite(HIGH_INDICATOR, LOW);    
  }
  
  lcd.setCursor(0, 0);
  lcd.print(F("Porcentaje: "));
  lcd.print(porcentaje);
  lcd.print(F("%    "));

  lcd.setCursor(0, 1);
  lcd.print(F("Nivel: "));
  lcd.print(nivel == CONTAINER_LOW ? "bajo   " : "alto   ");

  lcd.setCursor(12, 1);
  lcd.print(F("M~"));
  lcd.print(mode == AUTO ? F("A") : F("M"));
  
  lcd.setCursor(15, 1);
  lcd.print(filling ? F("^") : F("-"));
  delay(1000);
}
