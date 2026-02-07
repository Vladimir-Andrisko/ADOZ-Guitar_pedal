#ifndef FILTER_H_
#define FILTER_H_

#include <stdint.h>

#define BLOCK_SIZE 128

int32_t first_order_IIR(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history);
int32_t second_order_IIR(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history);
int32_t Nth_order_IIR(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history, int8_t order);

int32_t shelvingLP(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history, float k);
int32_t shelvingHP(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history, float k);
int32_t shelvingPeak(int32_t input, int32_t *coeff, int32_t *x_history, int32_t *y_history, float k);


#endif