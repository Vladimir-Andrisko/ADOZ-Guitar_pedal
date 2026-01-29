#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include <math.h>

#define DELAY_BUFFER_SIZE 32768
#define REVERB_BUFFER_SIZE 32768
#define MAX_DELAY (DELAY_BUFFER_SIZE - 1)

/**
 * @brief Initialize delay.
 * @param N Set delay in sample freq.
 */
void delay_init(uint16_t N);


/**
 * @brief Initialize echo.
 * @param N Set delay in sample freq.
 * @param gain Echo gain, max 1.0.
 */
void echo_init(uint16_t N, float gain);


/**
 * @brief Change current delay for echo.
 * @param N Set delay in sample freq.
 */
void set_echo_delay(uint16_t N);


/**
 * @brief Takes one audio sample and applies echo effect.
 * @param input Input sample.
 * 
 * @return return sample with applied echo effect.
 */
int32_t echo_sample(int32_t input);


/**
 * @brief Initialize reverb.
 * @param N Set delay in sample freq.
 * @param gain Reverb gain, max 1.0.
 */
void reverb_init(uint16_t N, float gain);


/**
 * @brief Change current delay for reverb.
 * @param N Set delay in sample freq.
 */
void set_reverb_delay(uint16_t new_delay);


/**
 * @brief Takes one audio sample and applies reverb effect.
 * @param input Input sample.
 * 
 * @return return sample with applied reverb effect.
 */
int32_t reverb_sample(int32_t input);

#endif