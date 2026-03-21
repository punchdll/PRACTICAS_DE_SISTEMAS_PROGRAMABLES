#ifndef PINOUT_H
#define PINOUT_H

#include <stdint.h>

static const uint8_t TRIGGER = 2; // Pin trigger del hcsr
static const uint8_t ECHO = 3; // Pin echo del hcsr

static const uint8_t SELECTOR = 8; // Salida al selector de rele

static const uint8_t B_START = 9; // Boton de llenado manual
static const uint8_t B_AUTO = 10; // Parada de llenado manual
static const uint8_t B_STOP = 11; //Modo de llenado automatico

static const uint8_t HIGH_INDICATOR = 12; // Led indicador de nivel alto
static const uint8_t LOW_INDICATOR = 13; // Led indicador de nivel bajo


#endif