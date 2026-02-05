#include "distortion.h"

static float gain = 1.0;
static float max_output = 0;

void distortion_set_gain(float new_gain){
    if(new_gain < 1.0) new_gain = 1.0;
    if(new_gain > 100.0) new_gain = 100.0;

    gain = new_gain;
}

int32_t distort_sample(int32_t input) {
    float x = (float)input / 2147483648.0f;
    float abs_x = fabsf(x);
    if(abs_x > max_output) max_output = abs_x;

    x *= gain;
    if(x > 1.0f) x = 1.0f;
    if(x < -1.0f) x = -1.0f;

    x *= max_output;

    int32_t output = (int32_t)(x * 2147483647.0f);
    return output;
}

int32_t overdrive_sample(int32_t input){
    float x = (float)input / 2147483648.0f;
    float abs_x = fabsf(x);
    if(abs_x > max_output) max_output = abs_x;

    float y = tanhf(gain * x) * max_output;

    int32_t output = (int32_t)(y * 2147483647.0f);
    return output;
}

