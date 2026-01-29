#ifndef SETUP_H_
#define SETUP_H_

#include "driver/i2s_std.h"
#include <math.h>

#define SAMPLE_RATE 44100

#define PCM1808_I2S_SLOT_CONFIG(bits, mode) { \
    .data_bit_width = bits, \
    .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO, \
    .slot_mode = mode, \
    .slot_mask = (mode == I2S_SLOT_MODE_MONO) ? \
                 I2S_STD_SLOT_LEFT : I2S_STD_SLOT_BOTH, \
    .ws_width = I2S_SLOT_BIT_WIDTH_AUTO, \
    .ws_pol = false, \
    .bit_shift = true, \
    .msb_right = false \
}

#define PCM1808_I2S_CLOCK_CONFIG(rate) { \
    .sample_rate_hz = rate, \
    .clk_src = I2S_CLK_SRC_APLL, \
    .mclk_multiple = I2S_MCLK_MULTIPLE_256 \
}

#define PCM5102_I2S_SLOT_CONFIG(bits, mode) { \
    .data_bit_width = bits, \
    .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO, \
    .slot_mode = mode, \
    .slot_mask = (mode == I2S_SLOT_MODE_MONO) ? \
                 I2S_STD_SLOT_LEFT : I2S_STD_SLOT_BOTH, \
    .ws_width = I2S_SLOT_BIT_WIDTH_AUTO, \
    .ws_pol = false, \
    .bit_shift = true, \
    .msb_right = false \
}

#define PCM5102_I2S_CLOCK_CONFIG(rate) { \
    .sample_rate_hz = rate, \
    .clk_src = I2S_CLK_SRC_APLL, \
    .mclk_multiple = I2S_MCLK_MULTIPLE_256 \
}

/**
 * @brief Initialize I2S protocol.
 * 
 * @param chan1 I2S handle type, input.
 * @param chan2 I2S handle type, output.
 */
void i2s_init(i2s_chan_handle_t* chan1, i2s_chan_handle_t* chan2);

/**
 * @brief Used to debug output connection.
 * 
 * @param output Buffer to store generated sound.
 * @param buffer_size Size of output buffer.
 */
void test_output(int32_t* output, size_t buffer_size);


#endif