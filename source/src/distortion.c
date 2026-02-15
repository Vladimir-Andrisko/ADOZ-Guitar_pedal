#include "distortion.h"

static float max_output = 0;

int32_t distort_sample(int32_t input, float gain) {
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

int32_t overdrive_sample(int32_t input, float gain){
    float x = (float)input / 2147483648.0f;
    float abs_x = fabsf(x);
    if(abs_x > max_output) max_output = abs_x;

    float y = tanhf(gain * x) * max_output;

    int32_t output = (int32_t)(y * 2147483647.0f);
    return output;
}

