#include "filter.h"

static int32_t x_history[10];
static int32_t y_history[10];

static inline int64_t signed_multiply_accumulate(int64_t sum, int32_t op1, int32_t op2){
    int64_t ret = (int64_t)sum + (((int64_t)op1 * (int64_t)op2) << 1);

    if(ret > INT64_MAX) return INT64_MAX;
    if(ret < INT64_MIN) return INT64_MIN;

    return (int64_t)ret;
}

static inline int64_t signed_multiply_subtract(int64_t sum, int32_t op1, int32_t op2){
    int64_t ret = (int64_t)sum - (((int64_t)op1 * (int64_t)op2) << 1);

    if(ret > INT64_MAX) return INT64_MAX;
    if(ret < INT64_MIN) return INT64_MIN;

    return (int64_t)ret;
}

int32_t first_order_IIR(int32_t input, int32_t *coeff){
    int64_t acc = 0;

    acc = signed_multiply_accumulate(acc, coeff[0], input);         // A0 * x(n)
    acc = signed_multiply_accumulate(acc, coeff[1], x_history[0]);  // A1 * x(n-1)
    acc = signed_multiply_subtract(acc, coeff[3], y_history[0]);    // B1 * y(n-1)

    acc >>= 32;
    int32_t output = (int32_t)acc;

    x_history[0] = input;
    y_history[0] = output;

    return output;
}

int32_t second_order_IIR(int32_t input, int32_t *coeff){
    int64_t acc = 0;

    acc = signed_multiply_accumulate(acc, coeff[0], input);         // A0 * x(n)
    acc = signed_multiply_accumulate(acc, coeff[1], x_history[0]);  // A1/2 * x(n-1)
    acc = signed_multiply_accumulate(acc, coeff[1], x_history[0]);  // A1/2 * x(n-1)
    acc = signed_multiply_accumulate(acc, coeff[2], x_history[1]);  // A2 * x(n-2)

    acc = signed_multiply_subtract(acc, coeff[4], y_history[0]);    // B1/2 * y(n-1)
    acc = signed_multiply_subtract(acc, coeff[4], y_history[0]);    // B1/2 * y(n-1)
    acc = signed_multiply_subtract(acc, coeff[5], y_history[1]);    // B2 * y(n-2)

    acc >>= 32;
    int32_t output = (int32_t)acc;

    x_history[1] = x_history[0];
    x_history[0] = input;
    y_history[1] = y_history[0];
    y_history[0] = output;

    return output;
}


int32_t shelvingLP(int32_t input, int32_t *coeff, float k){
    int64_t output = 0;

    int32_t filtered = first_order_IIR(input, coeff);

    output += (((int64_t)filtered + (int64_t)input) >> 1);
    output += (((int64_t)input - (int64_t)filtered) >> 1)*k;

    if(output > INT32_MAX) output = INT32_MAX;
    if(output < INT32_MIN) output = INT32_MIN;

    return (int32_t)output;
}

int32_t shelvingHP(int32_t input, int32_t *coeff, float k){
    int64_t output = 0;

    int32_t filtered = first_order_IIR(input, coeff);

    output += (((int64_t)filtered + (int64_t)input) >> 1)*k;
    output += (((int64_t)input - (int64_t)filtered) >> 1);

    if(output > INT32_MAX) output = INT32_MAX;
    if(output < INT32_MIN) output = INT32_MIN;

    return (int32_t)output;
}

int32_t shelvingPeak(int32_t input, int32_t *coeff, float k){
    int64_t output = 0;

    int32_t filtered = second_order_IIR(input, coeff);

    output += (((int64_t)filtered + (int64_t)input) >> 1);
    output += (((int64_t)input - (int64_t)filtered) >> 1)*k;

    if(output > INT32_MAX) output = INT32_MAX;
    if(output < INT32_MIN) output = INT32_MIN;

    return (int32_t)output;
}