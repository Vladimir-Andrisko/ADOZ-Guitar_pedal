#include "protocol_setup.h"

i2s_chan_config_t input_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
i2s_chan_config_t output_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_1, I2S_ROLE_MASTER);

i2s_std_config_t input_i2s_cfg = {
    .clk_cfg = PCM1808_I2S_CLOCK_CONFIG(SAMPLE_RATE),
    .slot_cfg = PCM1808_I2S_SLOT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_STEREO),
    .gpio_cfg = {
        .mclk = GPIO_NUM_0,
        .bclk = GPIO_NUM_16,
        .ws = GPIO_NUM_18,
        .dout = I2S_GPIO_UNUSED,
        .din = GPIO_NUM_17,
        .invert_flags = {
            .mclk_inv = false,
            .bclk_inv = false,
            .ws_inv = false,
        },
    },
};

i2s_std_config_t output_i2s_cfg = {
    .clk_cfg = PCM5102_I2S_CLOCK_CONFIG(SAMPLE_RATE),
    .slot_cfg = PCM5102_I2S_SLOT_CONFIG(I2S_DATA_BIT_WIDTH_32BIT, I2S_SLOT_MODE_STEREO),
    .gpio_cfg = {
        .mclk = I2S_GPIO_UNUSED,
        .bclk = GPIO_NUM_21,
        .ws   = GPIO_NUM_22,
        .dout  = GPIO_NUM_23,
        .din  = I2S_GPIO_UNUSED,
        .invert_flags = {
            .mclk_inv = false,
            .bclk_inv = false,
            .ws_inv   = false,
        },
    },
};

void i2s_init(i2s_chan_handle_t* chan1, i2s_chan_handle_t* chan2){

    // Create new channels
    i2s_new_channel(&input_chan_cfg, NULL, chan1);
    i2s_new_channel(&output_chan_cfg, chan2, NULL);

    // Initialize both channels in standard mode
    i2s_channel_init_std_mode(*chan1, &input_i2s_cfg);
    i2s_channel_init_std_mode(*chan2, &output_i2s_cfg);

    // Create channels
    i2s_channel_enable(*chan1);
    i2s_channel_enable(*chan2);

}

void test_output(int32_t *output, size_t buffer_size){
  for(int i = 0; i < buffer_size; i++){
        float t = (float)i / (float)SAMPLE_RATE;  // vreme u sekundama
        float val = 0.1*sinf(2.0f * 3.14159f * 120.0f * t);
        int32_t sample = (int32_t)(val * 0x7FFFFFFF);   // 32-bit MSB aligned
        output[i*2]   = sample; // L
        output[i*2+1] = sample; // R
  }
}