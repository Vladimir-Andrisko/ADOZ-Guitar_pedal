#ifndef FILTER_H_
#define FILTER_H_

#include <stdint.h>

/**
 * @brief Implements first order IIR filter.
 * @param input Input sample to be filtered.
 * @param coeff Coefficients array, sizeof 4.
 * 
 * @return Returns filtered sample.
 */
int32_t first_order_IIR(int32_t input, int32_t *coeff);


/**
 * @brief Implements second order IIR filter.
 * @param input Input sample to be filtered.
 * @param coeff Coefficients array, sizeof 6, coeffs B1 and A1 are halfes.
 * 
 * @return Returns filtered sample.
 */
int32_t second_order_IIR(int32_t input, int32_t *coeff);


/**
 * @brief Implements any order IIR filter, cascade multiple second order IIR
 * @param input Input sample to be filtered.
 * @param coeff Coefficients matrix, row is order, col are coeff. coeffs B1 and A1 are halfes.
 * 
 * @return Returns filtered sample.
 */
int32_t Nth_order_IIR(int32_t input, int32_t *coeff, int8_t order);


/**
 * @brief Shelving low pass filter, first order IIR.
 * @param input Input sample to be filtered.
 * @param coeff First order all pass filter coefficients.
 * @param k Gain.
 * 
 * @return Returns filtered sample.
 */
int32_t shelvingLP(int32_t input, int32_t *coeff, float k);


/**
 * @brief Shelving high pass filter, first order IIR.
 * @param input Input sample to be filtered.
 * @param coeff First order all pass filter coefficients.
 * @param k Gain.
 * 
 * @return Returns filtered sample.
 */
int32_t shelvingHP(int32_t input, int32_t *coeff, float k);

/**
 * @brief Shelving band pass filter, second order IIR.
 * @param input Input sample to be filtered.
 * @param coeff Second order all pass filter coefficients.
 * @param k Gain.
 * 
 * @return Returns filtered sample.
 */
int32_t shelvingPeak(int32_t input, int32_t *coeff, float k);


#endif