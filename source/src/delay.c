#include "delay.h"

int32_t reverb_buffer[DELAY_BUFFER_SIZE];
static uint16_t dbuff_read_index = 0;
static uint16_t dbuff_write_index = 0;
static uint16_t echo_delay = 0;
static float echo_gain = 0.0f;

int32_t delay_buffer[DELAY_BUFFER_SIZE];
static int16_t rbuff_read_index = 0;
static int16_t rbuff_write_index = 0;
static int16_t reverb_delay = 0;
static float reverb_gain = 0.0f;

static void clear_delay_buffer(){
    memset(delay_buffer, 0, sizeof(delay_buffer));
}

static void clear_reverb_buffer(){
    memset(reverb_buffer, 0, sizeof(reverb_buffer));
}


void echo_init(uint16_t N, float gain)
{
    if (N > MAX_DELAY) N = MAX_DELAY;

    if (gain < 0.0f) gain = 0.0f;
    if (gain >= 1.0f) gain = 0.999f;
    echo_gain = gain;

    clear_delay_buffer();
    echo_delay = N;
    dbuff_read_index = 0;
    dbuff_write_index = (dbuff_read_index + echo_delay) & MAX_DELAY;
}


void set_echo(uint16_t N, float gain){
    if(N > MAX_DELAY)
        N = MAX_DELAY;
    
    if (gain < 0.0f) gain = 0.0f;
    if (gain >= 1.0f) gain = 0.999f;
    echo_gain = gain;
    
    echo_delay = N;
    dbuff_read_index = (dbuff_write_index + DELAY_BUFFER_SIZE - echo_delay) & MAX_DELAY;
}


void reverb_init(uint16_t N, float gain){
    if (N > MAX_DELAY) N = MAX_DELAY;

    if (gain < 0.0f) gain = 0.0f;
    if (gain >= 1.0f) gain = 0.999f;
    reverb_gain = gain;

    clear_reverb_buffer();
    reverb_delay = N;
    rbuff_read_index = 0;
    rbuff_write_index = (rbuff_read_index + reverb_delay) & MAX_DELAY;
}


void set_reverb(uint16_t new_delay, float gain){
    if(new_delay > MAX_DELAY) 
        new_delay = MAX_DELAY;

    if (gain < 0.0f) gain = 0.0f;
    if (gain >= 1.0f) gain = 0.999f;
    reverb_gain = gain;

    reverb_delay = new_delay;
    rbuff_read_index = (rbuff_write_index + DELAY_BUFFER_SIZE - reverb_delay) & MAX_DELAY;
}

int32_t echo_sample(int32_t input){

    delay_buffer[dbuff_write_index++] = input;
    dbuff_write_index &= MAX_DELAY;

    int32_t delayed = delay_buffer[dbuff_read_index++];
    dbuff_read_index &= MAX_DELAY;
    
    int64_t acc = input;
    acc += (int64_t)llrintf(echo_gain * (float)delayed);
    if (acc > INT32_MAX) acc = INT32_MAX;
    if (acc < INT32_MIN) acc = INT32_MIN;

    return (int32_t)acc;
}


int32_t reverb_sample(int32_t input){
    int32_t delayed = reverb_buffer[rbuff_read_index++];
    rbuff_read_index &= MAX_DELAY;

    int64_t acc = input;
    acc += (int64_t)llrintf(reverb_gain * (float)delayed);
    if (acc > INT32_MAX) acc = INT32_MAX;
    if (acc < INT32_MIN) acc = INT32_MIN;

    reverb_buffer[rbuff_write_index++] = acc;
    rbuff_write_index &= MAX_DELAY;

    return (int32_t)acc;
}