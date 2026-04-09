#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdint.h>

#define PERCENT_ERROR  255

static  uint8_t container_depth = 90; // Profundidad del contendedor por defecto
static const uint8_t container_BLIND_SPOT = 20; // Valor minimo de la lectura a nivel fisico

static const uint8_t container_LEVEL_T = 90; // Umbral de nivel bajo/alto
static const uint8_t container_MAX_PERCENT = container_LEVEL_T; // Nivel maximo de llenado (ej. 80%)

typedef enum {
    container_LOW = 0,
    container_HIGH = 1
} Container_level;

inline uint8_t container_percent(uint16_t distance){
    
    if (distance == 0)
        return PERCENT_ERROR;

    float effective_depth = (float)container_depth - container_BLIND_SPOT;
    float measured_distance_from_blind_spot = (float)distance - container_BLIND_SPOT;


    if (measured_distance_from_blind_spot <= 0) {
        return 100; 
    }
    if (measured_distance_from_blind_spot >= effective_depth) {
        return 0; 
    }
    float percentage = 100.0f - (measured_distance_from_blind_spot * 100.0f / effective_depth);

    if (percentage < 0.0f) return 0;
    if (percentage > 100.0f) return 100;

    return (uint8_t)percentage;
}

inline uint8_t container_level(uint8_t percent){
    return (percent < container_LEVEL_T) ? container_LOW : container_HIGH;
}
#endif