/**
 * Day 2 - Exercise 1: Two Talking Tasks
 *
 * CHALLENGE: Create 2 concurrent tasks that print messages at different intervals
 *
 * REQUIREMENTS:
 * ✅ Task 1 prints "Hello from Task 1" every 1 second
 * ✅ Task 2 prints "Hello from Task 2" every 2 seconds
 * ✅ Both tasks run simultaneously (you'll see interleaved output)
 * ✅ Both tasks use proper infinite loops with vTaskDelay()
 * ✅ Each task has its own TAG for logging
 *
 * FUNCTIONS TO USE:
 * - xTaskCreate() - Create and start a task
 * - ESP_LOGI() - Log messages
 * - vTaskDelay() - Delay in milliseconds
 *
 * C CONCEPTS YOU'LL LEARN:
 * - Function pointers: Why &task_function?
 * - Multiple instances of task creation
 * - Task naming and identification
 * - Concurrent execution (tasks don't wait for each other)
 *
 * CRITICAL THINKING:
 * - What happens when Task 1 calls vTaskDelay()? Does Task 2 stop?
 * - Why do we pass &task1 instead of task1() to xTaskCreate()?
 * - What is pvParameter and when would you use it?
 *
 * EXPECTED OUTPUT:
 * I (1000) Task1: Hello from Task 1
 * I (2000) Task2: Hello from Task 2
 * I (2000) Task1: Hello from Task 1
 * I (3000) Task1: Hello from Task 1
 * I (4000) Task2: Hello from Task 2
 * I (4000) Task1: Hello from Task 1
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

const char *TAG1 = "Task1";
const char *TAG2 = "Task2";
// TODO: Create task1 function
// Signature: void task1(void *pvParameter)
// Inside: infinite loop that prints message and delays 1 second
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

    // TODO: Create task1 using xTaskCreate()
    // Parameters: function pointer, name string, stack size, parameters, priority, handle
    // Example structure: xTaskCreate(&your_function, "name", 2048, NULL, 5, NULL);
    xTaskCreate(&task1, "TASK1", 2048, NULL, 5, NULL);
    xTaskCreate(&task2, "TASK2", 2048, NULL, 5, NULL);

    ESP_LOGI("Main", "Both tasks created. Watch the interleaved output!");
}
