#ifndef DISTORTION_H_
#define DISTORTION_H_

#include <stdint.h>
#include <math.h>

/**
 * @brief Takes one sample, and applies distortion effect to it.
 * @param input Sample to edit.
 * @param gain Distort gain.
 * @return Sample with applied effect.
 */
int32_t distort_sample(int32_t input, float gain);

/**
 * @brief Takes one sample, and applies overdrive effect to it.
 * @param input Sample to edit.
 * @param gain Overdrive gain.
 * @return Sample with applied effect.
 */
int32_t overdrive_sample(int32_t input, float gain);

#endif