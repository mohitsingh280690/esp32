/**
 * Day 2 - Exercise 3: Passing Multiple Parameters with Structs
 * COMPLETED: December 21, 2025
 * 
 * Key learnings:
 * - Struct definition with typedef
 * - Passing struct pointers to tasks
 * - Arrow operator (->) for pointer member access
 * - Race conditions on shared hardware (3 tasks, 1 LED)
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "BlinkTask";
#define LED1 GPIO_NUM_2
#define LED2 GPIO_NUM_2
#define LED3 GPIO_NUM_2

typedef struct
{
    int delay_ms;
    gpio_num_t pinNumber;
    const char *name;
} blinkConfig_t;

blinkConfig_t config1 = {200, LED1, "FastLED"};
blinkConfig_t config2 = {500, LED2, "MediumLED"};
blinkConfig_t config3 = {1000, LED3, "SlowLED*************************"};

void blinkTask(void *pvParameter)
{
    blinkConfig_t *blinkConfig = (blinkConfig_t *)pvParameter;

    int delay = blinkConfig->delay_ms;
    gpio_num_t pinNumber = blinkConfig->pinNumber;
    const char *TAG = blinkConfig->name;
    gpio_reset_pin(pinNumber);
    gpio_set_direction(pinNumber, GPIO_MODE_OUTPUT);

    ESP_LOGI(TAG, "Entering task with delay %d", delay);

    while (1)
    {
        gpio_set_level(pinNumber, 1);
        vTaskDelay(pdMS_TO_TICKS(delay));
        gpio_set_level(pinNumber, 0);
        vTaskDelay(pdMS_TO_TICKS(delay));
        ESP_LOGI(TAG, "Task with delay %d", delay);
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 2 - Exercise 3: Struct Parameters");
    ESP_LOGI(TAG, "=================================");

    xTaskCreate(&blinkTask, "Blink1", 2048, (void *)&config1, 5, NULL);
    xTaskCreate(&blinkTask, "Blink2", 2048, (void *)&config2, 5, NULL);
    xTaskCreate(&blinkTask, "Blink3", 2048, (void *)&config3, 5, NULL);
    ESP_LOGI(TAG, "All tasks created. Watch the different blink rates!");
}
