#ifndef DISTORTION_H_
#define DISTORTION_H_

#include <stdint.h>
#include <math.h>


/**
 * @brief Sets the gain for distortion.
 * 
 * @param new_gain New gain value.
 * 
 */
void distortion_set_gain(float new_gain);


/**
 * @brief Takes one sample, and applies distortion effect to it.
 * @param input Sample to edit.
 * @return Sample with applied effect.
 */
int32_t distort_sample(int32_t input);

/**
 * @brief Takes one sample, and applies overdrive effect to it.
 * @param input Sample to edit.
 * @return Sample with applied effect.
 */
int32_t overdrive_sample(int32_t input);

#endif