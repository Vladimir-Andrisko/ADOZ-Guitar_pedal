#include "interface.h"
#include "effects.h"


static int8_t enState = 0, prevEnState = 0;
static int8_t selState = 0, prevSelState = 0;
static uint32_t time = 0;

gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << SELECT_BUTTON) | (1ULL << ENABLE_BUTTON),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
};

static adc_oneshot_unit_handle_t adc_handle;
static adc_oneshot_unit_init_cfg_t adc_config = {
    .unit_id = ADC_UNIT,
    .clk_src = ADC_RTC_CLK_SRC_DEFAULT
};
static adc_oneshot_chan_cfg_t chan_config = {
    .atten = ADC_ATTEN,
    .bitwidth = ADC_BITWIDTH
};

void print_effect(){
    for(int i = 0; i < EFFECT_NUM; i++){
        char *is_enabled = "\033[31mOFF,\033[37m";
        if(effect_state.enabled[i]) is_enabled = "\033[32mON,\033[37m";

        switch(i){
            case ECHO:
                printf("\033[40;37mECHO        %-15s    \033[34mgain: \033[35m%.2f,    \033[34mdelay: \033[35m%.2fs\033[37m", is_enabled, effect_state.gain[i], ((float)effect_state.delay[i]/(float)MAX_DELAY * 0.4f));
                break;

            case DISTORTION:
                printf("\033[40;37mDISTORTION  %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case OVERDRIVE:
                printf("\033[40;37mOVERDRIVE   %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case LOW_PASS:
                printf("\033[40;37mLOW_PASS    %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case LOW_EQ:
                printf("\033[40;37mLOW_EQ      %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case MID_EQ:
                printf("\033[40;37mMID_EQ      %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case HIGH_EQ:
                printf("\033[40;37mHIGH_EQ     %-15s    \033[34mgain: \033[35m%.2f", is_enabled, effect_state.gain[i]);
                break;

            case REVERB:
                printf("\033[40;37mREVERB      %-15s    \033[34mgain: \033[35m%.2f,    \033[34mdelay: \033[35m%.2fs\033[0m", is_enabled, effect_state.gain[i], ((float)effect_state.delay[i]/(float)MAX_DELAY * 0.4f));
                break;

            default:
                break;
        }

        if(effect_state.current_effect == i){
            printf("\033[1;33m  <---\n\033[0m");
        }else{
            printf("\n\033[0m");
        }
            
    }
    printf("\33c\33r\33[?25l\033[0m");
}

void readButton(int8_t *select, int8_t *enable){
    *select = gpio_get_level(SELECT_BUTTON);
    *enable = gpio_get_level(ENABLE_BUTTON);
}

void readPot(){
    int gain_read = 0, delay_read = 0;
    float gain_value = 0;
    int16_t delay_value = 0;

    adc_oneshot_read(adc_handle, POT_LOG_L, &gain_read);
    adc_oneshot_read(adc_handle, POT_LOG_R, &delay_read);

    if(effect_state.current_effect == DISTORTION || effect_state.current_effect == OVERDRIVE){
        gain_value = (float)gain_read * 9.0f/4096.0f + 1;
    }else if(effect_state.current_effect == ECHO || effect_state.current_effect == REVERB){
        gain_value = (float)gain_read/4096.0f;
        delay_value = (int16_t)((delay_read * MAX_DELAY) >> 12);
    }else{
        gain_value = (float)gain_read * 10.0f/4096.0f;
    }

    effect_state.gain[effect_state.current_effect] = gain_value;
    effect_state.delay[effect_state.current_effect] = delay_value;
}

void buttonDebounce(){
    readButton(&selState, &enState);

    if(selState != prevSelState){
        prevSelState = selState;
        if(!selState){
            effect_state.current_effect++;
            effect_state.current_effect = effect_state.current_effect % EFFECT_NUM;
        }
    }

    if(enState != prevEnState){
        prevEnState = enState;
        if(!enState){
            effect_state.enabled[effect_state.current_effect] = !effect_state.enabled[effect_state.current_effect];
        }
    }
}

void interface_task(void *param){
    gpio_config(&io_conf);
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc_config, &adc_handle));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, POT_LOG_L, &chan_config));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, POT_LOG_R, &chan_config));

    while(1){
        
        taskENTER_CRITICAL(&effect_state_mux);
        buttonDebounce();
        readPot();
        taskEXIT_CRITICAL(&effect_state_mux);

        if(time >= 500){
            time = 0;
            print_effect();
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
        time += 50;
    }
}