/**
 * Day 2 - Exercise 2: Task with Parameters
 * COMPLETED: December 21, 2025
 * 
 * Key learnings:
 * - void* casting for passing values directly
 * - Memory lifetime considerations (local variables vs static vs direct values)
 * - Race conditions on shared hardware (single LED)
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_PIN GPIO_NUM_2

static const char *TAG = "BlinkTask";

void blinkTsk(void *pvParameter)
{   
    int delay = (int)pvParameter;  // Direct cast - safe approach
    
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    ESP_LOGI(TAG, "Entered Blink Task with delay %d ms", delay);

    while (1)
    {
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(delay));
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(delay));
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 2 - Exercise 2: Task Parameters");
    ESP_LOGI(TAG, "=================================");

    xTaskCreate(&blinkTsk, "FastBlink", 2048, (void*)500, 5, NULL);
    xTaskCreate(&blinkTsk, "SlowBlink", 2048, (void*)1500, 5, NULL);
    
    ESP_LOGI(TAG, "Both tasks created!");
}
