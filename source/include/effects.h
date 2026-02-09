#ifndef EFFECTS_H_
#define EFFECTS_H_

#include <stdint.h>

typedef enum{
    ECHO = 0, 
    DISTORTION, 
    OVERDRIVE, 
    LOW_PASS,
    LOW_EQ, 
    MID_EQ, 
    HIGH_EQ, 
    REVERB, 
    EFFECT_NUM
} Effect_sel;

typedef struct {
    volatile Effect_sel current_effect;
    volatile int8_t enabled[EFFECT_NUM];
    volatile int16_t delay[EFFECT_NUM];
    volatile float gain[EFFECT_NUM];
} effect_state_t;

extern volatile effect_state_t effect_state;
extern portMUX_TYPE effect_state_mux;

#endif