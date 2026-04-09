#include "pinout.h"
#include "HC-SR04/hcsr04.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "container.h"
#include "pump.h"
#include <stdint.h>

static LiquidCrystal_I2C lcd(0x27,16,2);

static const uint16_t DELAY = 60;
static const uint8_t HYSTERESIS = 1;
static const uint8_t DEPTH_SAMPLES = 50;
static float smoothed_distance = -1.0;    // -1.0 indica que no esta inicializado
static PumpMode mode = MANUAL;
static bool filling = false;

static uint32_t previous_time = 0;

void setup() {
  Wire.begin();

  // Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(ECHO, INPUT);
  
  pinMode(B_START, INPUT_PULLUP);
  pinMode(B_STOP, INPUT_PULLUP);
  pinMode(B_AUTO, INPUT_PULLUP);
  pinMode(B_CALIBRATION, INPUT_PULLUP);


  pinMode(SELECTOR, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(LOW_INDICATOR, OUTPUT);
  pinMode(HIGH_INDICATOR, OUTPUT);

}

void loop() {


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
  else if (!digitalRead(B_CALIBRATION)){
    mode = MANUAL;
    filling = false;
    lcd.clear();
    uint32_t sum_depth = 0;
    uint8_t valid_samples = 0;
    for (uint16_t i = 0; i < DEPTH_SAMPLES; i++){
      uint16_t current_reading = hcsr04_millimeter(ECHO, TRIGGER);
      if (current_reading != 0) {
        sum_depth += current_reading;
        valid_samples++;
      }
      lcd.setCursor(0, 0);
      lcd.print(F("Calibrando..."));
      lcd.setCursor(0, 1);
      lcd.print(F("Lec. ("));
      lcd.print(i+1);
      lcd.print(F("): "));
      lcd.print(current_reading);
      lcd.print(F("mm"));
      delay(20);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    if (valid_samples > 0) {
      container_depth = (sum_depth / valid_samples);
      lcd.print(F("Profundidad:"));
    } else {
      lcd.print(F("Calib. Fallida"));
    }
    lcd.setCursor(0, 1);
    lcd.print(container_depth);
    lcd.print(F("mm  "));
    delay(1000);
    smoothed_distance = -1.0;
  }

  uint32_t current_time = millis();

  if(current_time - previous_time >= DELAY){
    previous_time = current_time;

    uint16_t current_distance = hcsr04_millimeter(ECHO, TRIGGER);    

    if (current_distance != 0) {
        if (smoothed_distance < 0) { // Si es la primera lectura válida, inicializar.
            smoothed_distance = current_distance;
        } else {
            float alpha;
            float max_deviation;

            if (filling) {
                alpha = 0.3;
                max_deviation = 30.0;
            } else {
                alpha = 0.2;
                max_deviation = 25.0;
            }

            // Aplicar el filtro EMA solo si la lectura es plausible.
            if (abs(current_distance - smoothed_distance) < max_deviation) {
                smoothed_distance = (alpha * current_distance) + ((1.0 - alpha) * smoothed_distance);
            }
        }
    }

    // Solo procesar si ya tenemos al menos una lectura válida
    uint8_t porcentaje = (smoothed_distance >= 0) ? container_percent((uint16_t)smoothed_distance) : PERCENT_ERROR;
    uint8_t nivel = container_level(porcentaje);


    // Serial.print(distancia);

  if (mode == AUTO){
    if (porcentaje != PERCENT_ERROR && porcentaje < (container_MAX_PERCENT - HYSTERESIS)){
      digitalWrite(SELECTOR, HIGH);
      filling = true;
    }
    else if (porcentaje == PERCENT_ERROR || porcentaje >= container_MAX_PERCENT){
      digitalWrite(SELECTOR, LOW);
      filling = false;
    }
  }

    if(nivel == container_HIGH){
      digitalWrite(HIGH_INDICATOR, HIGH);
      digitalWrite(LOW_INDICATOR, LOW);
    }
    else{
      digitalWrite(LOW_INDICATOR, HIGH);
      digitalWrite(HIGH_INDICATOR, LOW);    
    }
    
    lcd.setCursor(0, 0);
    if (porcentaje == PERCENT_ERROR) {
      lcd.print("ERR    ");
    } else {
      lcd.print(porcentaje);
      lcd.print(F("% ["));
      lcd.print(smoothed_distance != -1.0 ? (int)(container_depth - smoothed_distance): 0);
      lcd.print(F("mm/")); 
      lcd.print(container_depth - container_BLIND_SPOT); 
      lcd.print(F("mm]"));
    }

    lcd.setCursor(0, 1);
    lcd.print(F("Nivel: "));
    lcd.print(nivel == container_LOW ? "bajo   " : "alto   ");

    lcd.setCursor(12, 1);
    lcd.print(F("M~"));
    lcd.print(mode == AUTO ? F("A") : F("M"));
    
    lcd.setCursor(15, 1);
    lcd.print(filling ? F("^") : F("-"));
  }

}
