#include "protocol_setup.h"
#include "distortion.h"
#include "delay.h"
#include "filter.h"
#include "interface.h"
#include "effects.h"
#include "filter_coeffs.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

#define BUFFER_SIZE 128

volatile effect_state_t effect_state;
effect_state_t local_state;
portMUX_TYPE effect_state_mux = portMUX_INITIALIZER_UNLOCKED;

TaskHandle_t interface_handle;

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
    echo_init(0.0, 0.0);
    reverb_init(0.0, 0.0);
    distortion_set_gain(0.0);

    xTaskCreatePinnedToCore(interface_task, "Interface", 5000, NULL, 1, &interface_handle, 1);

    while(1){
        
        i2s_channel_read(input_handle, input_buffer, sizeof(input_buffer), &bytes_read, portMAX_DELAY);

        taskENTER_CRITICAL(&effect_state_mux);
        local_state = effect_state;
        taskEXIT_CRITICAL(&effect_state_mux);

        for (int i = 0; i < bytes_read/8; i++) {
                // In I2S protocol 24bits of data is 0 padded to 32bit
                int32_t left = input_buffer[i*2];
                int32_t right = input_buffer[i*2+1];

                if(local_state.enabled[ECHO]){
                    set_echo(local_state.delay[ECHO], local_state.gain[ECHO]);
                    left = echo_sample(left);
                }

                if(local_state.enabled[DISTORTION]){
                    left = distort_sample(left);
                }
                else if(local_state.enabled[OVERDRIVE]){   // Overdrive and distortion cant be applied at the same time
                    left = distort_sample(left);
                }

                if(local_state.enabled[LOW_PASS]){
                    left = shelvingLP(left, IIR_all_pass_1st_order_80Hz, local_state.gain[LOW_PASS]);
                }

                if(local_state.enabled[LOW_EQ]){
                    left = shelvingPeak(left, IIR_all_pass_2nd_order_350Hz, local_state.gain[LOW_EQ]);
                }

                if(local_state.enabled[MID_EQ]){
                    left = shelvingPeak(left, IIR_all_pass_2nd_order_1400Hz, local_state.gain[MID_EQ]);
                }

                if(local_state.enabled[HIGH_EQ]){
                    left = shelvingPeak(left, IIR_all_pass_2nd_order_6500Hz, local_state.gain[HIGH_EQ]);
                }

                if(local_state.enabled[REVERB]){
                    set_reverb(local_state.delay[REVERB], local_state.gain[REVERB]);
                    left = reverb_sample(left);
                }

                // In I2S protocol 24bits of data needs to be in 32bit format with 0 padding
                output_buffer[i*2] = left;
                output_buffer[i*2+1] = right;
        }

        i2s_channel_write(output_handle, output_buffer, sizeof(output_buffer), &bytes_written, portMAX_DELAY);
    }

    return;
}