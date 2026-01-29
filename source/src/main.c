#include "setup.h"
#include "delay.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128

static i2s_chan_handle_t input_handle;
static i2s_chan_handle_t output_handle;

// Format (4 bytes): L R L R L R ... 
int32_t input_buffer[BUFFER_SIZE];
int32_t output_buffer[BUFFER_SIZE];
size_t bytes_read = 0, bytes_written = 0;

void app_main() {

    memset(input_buffer, 0, sizeof(input_buffer));
    memset(output_buffer, 0, sizeof(output_buffer));

    i2s_init(&input_handle, &output_handle);
    // Allow some time for init to finnish.
    vTaskDelay(pdMS_TO_TICKS(500));

    while(1){
        
        i2s_channel_read(input_handle, input_buffer, sizeof(input_buffer), &bytes_read, portMAX_DELAY);

        for (int i = 0; i < bytes_read/8; i++) {
                // In I2S protocol 24bits of data is 0 padded to 32bit
                int32_t left = input_buffer[i*2] >> 8;
                int32_t right = input_buffer[i*2+1] >> 8;

                // In I2S protocol 24bits of data needs to be in 32bit format with 0 padding
                output_buffer[i*2] = left << 8;
                output_buffer[i*2+1] = right << 8;
        }

        i2s_channel_write(output_handle, output_buffer, sizeof(output_buffer), &bytes_written, portMAX_DELAY);
    }

    return;
}