/**
 * Day 2 - Exercise 1: Two Talking Tasks
 * COMPLETED: December 20, 2025
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

const char *TAG1 = "Task1";
const char *TAG2 = "Task2";

void task1(void *pvParameter)
{
    while (1)
    {
        ESP_LOGI(TAG1, "inside TASK1");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task2(void *pvParameter)
{
    while (1)
    {
        ESP_LOGI(TAG2, "inside TASK2");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI("Main", "=================================");
    ESP_LOGI("Main", "Day 2 - Exercise 1: Two Tasks");
    ESP_LOGI("Main", "=================================");

    xTaskCreate(&task1, "TASK1", 2048, NULL, 5, NULL);
    xTaskCreate(&task2, "TASK2", 2048, NULL, 5, NULL);

    ESP_LOGI("Main", "Both tasks created. Watch the interleaved output!");
}
