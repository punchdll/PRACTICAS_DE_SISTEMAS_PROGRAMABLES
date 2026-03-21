#ifndef HCSR04_H
#define HCSR04_H

#include <stdint.h>

//const float SOS = 0.034; // Velocidad del sonido en cm/us

static const uint8_t PULSE_T_US = 10; // Duración del pulso de trigger en us
static const uint8_t FIXED_SOS = 58; // Velocidad del sonido inversa entera
static const uint16_t TIMEOUT = 6000; // Cantidad maxima de tiempo en la lectura (~102cm)

inline uint16_t hcsr04_read(const uint8_t echo, const uint8_t trigger){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(PULSE_T_US);
  digitalWrite(trigger, LOW);
  return pulseIn(echo, HIGH, TIMEOUT);
}

inline uint8_t hcsr04_centimeter(const uint8_t echo, const uint8_t trigger){
  return hcsr04_read(echo, trigger) / FIXED_SOS;
}


#endif
