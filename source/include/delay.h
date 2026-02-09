#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include <math.h>
#include <string.h>

#define DELAY_BUFFER_SIZE 16384
#define REVERB_BUFFER_SIZE 16384
#define MAX_DELAY (DELAY_BUFFER_SIZE - 1)


/**
 * @brief Initialize echo.
 * @param N Set delay in sample freq.
 * @param gain Echo gain, max 1.0.
 */
void echo_init(uint16_t N, float gain);


/**
 * @brief Change current delay for echo.
 * @param N Set delay in sample freq.
 * @param gain set gain, max 1.0.
 */
void set_echo(uint16_t N, float gain);


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
 * @param new_delay Set delay in sample freq.
 * @param gain set gain, max 1.0.
 */
void set_reverb(uint16_t new_delay, float gain);


/**
 * @brief Takes one audio sample and applies reverb effect.
 * @param input Input sample.
 * 
 * @return return sample with applied reverb effect.
 */
int32_t reverb_sample(int32_t input);

#endif