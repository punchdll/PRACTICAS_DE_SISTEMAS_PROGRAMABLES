#include <stdint.h>

#define SEQ_SIZE 4
#define PINOUT_SIZE 4

#define LEFT_BUTTON  2
#define RIGTH_BUTTON  3
#define SPEED_UP_BUTTON 4
#define SPEED_DOWN_BUTTON 5

#define MIN_DELAY_TIME 10
#define MAX_DELAY_TIME 100
#define DEFAULT_DELAY_TIME 50
#define SPEED_STEP 1

// #define PROTEUS
#define DEBUG

enum directions {
  LEFT,
  RIGHT,
  STOPPED
};

const uint8_t pines[PINOUT_SIZE] = {11, 10, 9, 8};

const uint8_t sequences [SEQ_SIZE][PINOUT_SIZE] = {
  {1, 0, 0, 0}, 
  {0, 1, 0, 0}, 
  {0, 0, 1, 0}, 
  {0, 0, 0, 1}
};

uint8_t direction = STOPPED;

uint16_t delay_time = DEFAULT_DELAY_TIME;

inline void speed_up_motor(uint8_t step){
  delay_time -= step;
}

inline void speed_down_motor(uint8_t step){
  delay_time += step;
}

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGTH_BUTTON, INPUT_PULLUP);
  pinMode(SPEED_UP_BUTTON, INPUT_PULLUP);
  pinMode(SPEED_DOWN_BUTTON, INPUT_PULLUP);

  for (uint8_t pin : pines){
    pinMode(pin, OUTPUT);
  }
}

void loop() {

  bool left_button_state = digitalRead(LEFT_BUTTON);
  bool rigth_button_state = digitalRead(RIGTH_BUTTON);

  #ifndef PROTEUS
  left_button_state = !left_button_state;
  rigth_button_state = !rigth_button_state;
  #endif

  if (left_button_state){
    direction = LEFT;
  }
  else if (rigth_button_state){
    direction = RIGHT;
  }

  bool speed_up = digitalRead(SPEED_UP_BUTTON);
  bool speed_down = digitalRead(SPEED_DOWN_BUTTON);

  #ifndef PROTEUS
  speed_up = !speed_up;
  speed_down = !speed_down;
  #endif

  if (speed_up && delay_time > MIN_DELAY_TIME) {
    speed_up_motor(SPEED_STEP);
  }
  else if (speed_down && delay_time < MAX_DELAY_TIME) {
    speed_down_motor(SPEED_STEP);
  }

  if (direction == LEFT){
    for (int8_t sequence = SEQ_SIZE - 1; sequence >= 0; sequence--){
      for (uint8_t pin = 0; pin < PINOUT_SIZE; pin++){
        digitalWrite(pines[pin], sequences[sequence][pin]);
      }
      delay (delay_time);
    }
  }
  else if (direction == RIGHT){
      for (int8_t sequence = 0; sequence < SEQ_SIZE; sequence++){
      for (uint8_t pin = 0; pin < PINOUT_SIZE; pin++){
        digitalWrite(pines[pin], sequences[sequence][pin]);
      }
      delay (delay_time);
    }
  }




#ifdef DEBUG
const char* direccion_texto[] = {"Antihorario", "Horario", "Detenido"};
Serial.print("Direccion: ");
Serial.print(direccion_texto[direction]);
Serial.print(" | Delay/Velocidad: ");
Serial.print(delay_time);
Serial.print(" | ");
Serial.print(map(delay_time, MIN_DELAY_TIME, MAX_DELAY_TIME, 100, 0));
Serial.println("%");
#endif

}
