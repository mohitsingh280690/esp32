/**
 * Day 5 - Exercise 2: Mutex for Shared UART (Real-World Example)
 * COMPLETED: December 30, 2025
 *
 * This demonstrates mutex protection for shared UART output.
 * Multiple tasks print multi-line messages with and without mutex protection.
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "UARTMutex";

// Mutex to protect UART writes
SemaphoreHandle_t uartMutex = NULL;

// Flag to enable/disable mutex
bool use_mutex = false;  // Start FALSE to see garbled output!

// We'll use raw printf to bypass ESP_LOGI's built-in mutex
void printTask(void *pvParameter)
{
    const char *taskName = (const char *)pvParameter;
    int counter = 0;
    
    while (1)
    {
        // TODO: If use_mutex is true, lock the mutex here
        if (use_mutex) {
            xSemaphoreTake(uartMutex, portMAX_DELAY);
        }
        
        // Critical section - multi-line UART output
        // Without mutex, these lines will interleave with other tasks!
        printf("====================================\n");
        printf("%s is printing...\n", taskName);
        printf("Line 1 of message from %s\n", taskName);
        printf("Line 2 of message from %s\n", taskName);
        printf("Line 3 of message from %s\n", taskName);
        printf("Counter value: %d\n", counter++);
        printf("====================================\n\n");
        
        // TODO: If use_mutex is true, unlock the mutex here
        if (use_mutex) {
            xSemaphoreGive(uartMutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(10));  // Very short delay to force interleaving
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=====================================");
    ESP_LOGI(TAG, "Day 5 - Exercise 2: UART Mutex Demo");
    ESP_LOGI(TAG, "use_mutex = %s", use_mutex ? "TRUE" : "FALSE");
    ESP_LOGI(TAG, "=====================================");
    ESP_LOGI(TAG, "Watch the output below...");
    ESP_LOGI(TAG, "");

    // Create mutex
    uartMutex = xSemaphoreCreateMutex();
    
    // Create multiple tasks that print to UART
    // All pinned to same core to ensure interleaving
    xTaskCreatePinnedToCore(printTask, "TaskA", 2048, (void *)"[TASK-A]", 5, NULL, 0);
    xTaskCreatePinnedToCore(printTask, "TaskB", 2048, (void *)"[TASK-B]", 5, NULL, 0);
    xTaskCreatePinnedToCore(printTask, "TaskC", 2048, (void *)"[TASK-C]", 5, NULL, 0);
    
    // INSTRUCTIONS:
    // 1. First run with use_mutex = false
    //    → You'll see garbled, unreadable output
    // 2. Then change use_mutex = true and rebuild
    //    → Clean, separated output blocks
}
