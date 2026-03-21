#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>

static const uint8_t DEPTH = 9; // Profundidad del contendedor
static const uint8_t LEVEL_T = 30; // Umbral de nivel bajo/alto
static const uint8_t CONTAINER_MAX_PERCENT = 70; // Nivel maximo de llenado 
static const uint8_t CONTAINER_LOW = 0;
static const uint8_t CONTAINER_HIGH = 1;

inline uint8_t container_percent(uint8_t distance){
    if (distance >= DEPTH) 
        return 0;
    
    if (distance == 0) 
        return 100;

  return 100 - (uint8_t)((uint16_t)distance * 100 / DEPTH);
}

inline uint8_t container_level(uint8_t percent){
    return (percent < LEVEL_T) ? CONTAINER_LOW : CONTAINER_HIGH;
}
#endif