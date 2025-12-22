/**
 * Day 3 - Exercise 2: Dynamic Priority Change
 * COMPLETED: December 22, 2025
 * 
 * Demonstrates:
 * - Two tasks with same initial priority (5)
 * - Runtime priority change using vTaskPrioritySet()
 * - TaskHandle_t and opaque pointers (using NULL for self-reference)
 * - Priority verification with uxTaskPriorityGet()
 * - Observable behavior change when priorities differ
 * 
 * Key Learning:
 * - Priority only matters when tasks are READY to run
 * - Tasks in BLOCKED state (vTaskDelay) don't compete
 * - Shortened delays (10ms) allow tasks to compete for CPU
 * - High-priority task preempts lower-priority when both ready
 * - NULL in FreeRTOS functions means "current task"
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "PriorityDemo";

static const char *task1Name = "t1";
static const char *task2Name = "t2";

void dynamicTask(void *pvParameter)
{

    char *tag = (char *)pvParameter;
    uint32_t counter = 0;
    
    UBaseType_t priority = uxTaskPriorityGet(NULL);
    ESP_LOGI(tag, "Started with priority: %d", priority);
    
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));  // Short delay so tasks compete
        counter++;
        
        // Log every 100 iterations (every ~1 second)
        if (counter % 100 == 0) {
            ESP_LOGI(tag, "Count: %d (priority: %d)", counter / 100, uxTaskPriorityGet(NULL));
        }
        
        // Task1 boosts its priority after 5 seconds
        if (counter == 500 && strcmp(tag, task1Name)==0)
        {
            ESP_LOGW(tag, "BEFORE: Priority = %d", uxTaskPriorityGet(NULL));
            vTaskPrioritySet(NULL, 10);
            ESP_LOGW(tag, "AFTER: Priority = %d", uxTaskPriorityGet(NULL));
            ESP_LOGW(tag, "Watch task1 dominate now!");
        }
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 3 - Exercise 2: Dynamic Priority");
    ESP_LOGI(TAG, "=================================");

    // Create two tasks with SAME initial priority (5)
    xTaskCreate(dynamicTask,"task1",2048,(void *)task1Name,5,NULL);
    xTaskCreate(dynamicTask,"task2",2048,(void *)task2Name,5,NULL);
}
