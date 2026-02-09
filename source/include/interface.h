#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "delay.h"
#include <string.h>
#include <stdio.h>

#define SELECT_BUTTON (GPIO_NUM_14)
#define ENABLE_BUTTON (GPIO_NUM_27)

#define POT_LOG_L    (ADC_CHANNEL_7)   // pin 35
#define POT_LOG_R    (ADC_CHANNEL_4)   // pin 32
#define POT_LIN      (ADC_CHANNEL_5)   // pin 33
#define ADC_UNIT     (ADC_UNIT_1)
#define ADC_BITWIDTH (ADC_BITWIDTH_12)
#define ADC_ATTEN    (ADC_ATTEN_DB_12)


/**
 * @brief freeRTOS task, reads all input.
 * 
 */
void interface_task(void* param);


/**
 * @brief Reads values of select and enable buttons.
 * @param select Memory for read value.
 * @param enable Memory for read value.
 * 
 */
void readButton(int8_t *select, int8_t *enable);


/**
 * @brief Handles all button options.
 * 
 */
void buttonDebounce();

#endif