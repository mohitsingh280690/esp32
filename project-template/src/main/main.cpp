/**
 * Day 5 - Exercise 2: Mutex for Shared Resource Protection
 *
 * CHALLENGE: Demonstrate race conditions and fix them with mutex
 *
 * REQUIREMENTS:
 * ✅ Create a shared counter variable
 * ✅ Two tasks incrementing the counter 1000 times each
 * ✅ WITHOUT mutex: Observe race condition (final count < 2000)
 * ✅ WITH mutex: Observe correct behavior (final count = 2000)
 *
 * FUNCTIONS YOU'LL NEED:
 * - xSemaphoreCreateMutex() - Create mutex
 * - xSemaphoreTake(mutex, portMAX_DELAY) - Lock (acquire mutex)
 * - xSemaphoreGive(mutex) - Unlock (release mutex)
 *
 * C CONCEPTS TO LEARN:
 *
 * Race Conditions - The Hidden Bug
 * ---------------------------------
 * counter++;  // Looks atomic, but it's NOT!
 *
 * Actually 3 operations:
 * 1. Read counter from memory → register
 * 2. Add 1 to register
 * 3. Write register → memory
 *
 * What happens with 2 tasks:
 * Task A: Read counter=5 → Add 1 → (context switch)
 * Task B: Read counter=5 → Add 1 → Write 6
 * Task A: (resume) → Write 6  ← LOST Task B's increment!
 *
 * Result: Expected 2 increments (5→7), got 1 increment (5→6)
 *
 * Mutex - Mutual Exclusion Lock
 * ------------------------------
 * Ensures only ONE task in critical section at a time.
 *
 * Pattern:
 * xSemaphoreTake(mutex, portMAX_DELAY);  // Lock
 * counter++;  // Critical section - safe now!
 * xSemaphoreGive(mutex);  // Unlock
 *
 * DESIGN PATTERN: Guard / Mutex Protection
 * ------------------------------------------
 * Protect shared resources from concurrent access.
 *
 * Problem it solves:
 * - Multiple tasks reading/writing same variable
 * - Hardware peripherals (UART, SPI, I2C) shared between tasks
 * - Data structures modified by multiple tasks
 * - Non-atomic operations that must complete
 *
 * Classic use cases:
 * - Shared counter/statistics
 * - UART/Serial.print() from multiple tasks
 * - SPI bus with multiple devices
 * - Linked list or queue manipulation
 *
 * Without mutex (BAD):
 * - Race conditions
 * - Lost updates
 * - Corrupted data structures
 * - Unpredictable behavior
 *
 * With mutex (GOOD):
 * - One task at a time
 * - All operations complete
 * - Predictable, correct behavior
 *
 * Mutex = Special Type of Semaphore
 * -----------------------------------
 * Technically, mutex uses SemaphoreHandle_t type.
 * FreeRTOS mutexes have priority inheritance (prevents priority inversion).
 *
 * Example:
 * SemaphoreHandle_t myMutex;
 * myMutex = xSemaphoreCreateMutex();
 *           ^--- Returns handle or NULL on failure
 *
 * volatile Keyword - Does It Help?
 * --------------------------------
 * volatile int counter;  ← Still has race conditions!
 *
 * volatile means:
 * - Always read from memory (don't cache in register)
 * - Compiler won't optimize away reads
 *
 * volatile does NOT:
 * - Make operations atomic
 * - Prevent race conditions
 * - Replace mutex
 *
 * Use volatile for:
 * - Hardware registers (memory-mapped I/O)
 * - ISR-modified variables
 * - Variables modified by other cores/DMA
 *
 * Use mutex for:
 * - Protecting shared data between tasks
 *
 * CRITICAL THINKING QUESTIONS:
 * - Run WITHOUT mutex first - what final count do you get? Why not 2000?
 * - Does adding 'volatile' to counter fix the race condition? Why not?
 * - What if Task A holds mutex and gets suspended - what happens to Task B?
 * - Can you use the same mutex to protect multiple variables?
 * - What's the performance cost of using mutex?
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "MutexDemo";

// TODO: Declare shared counter variable (try without volatile first)
int shared_counter = 0;

// TODO: Declare mutex handle
SemaphoreHandle_t counterMutex = NULL;

// Flag to enable/disable mutex (for demonstration)
bool use_mutex = false;  // Start FALSE to see race condition!

void incrementTask(void *pvParameter)
{
    const char *taskName = (const char *)pvParameter;
    
    for (int i = 0; i < 1000; i++)
    {
        // TODO: If use_mutex is true, lock the mutex here
        if (use_mutex) {
            xSemaphoreTake(counterMutex, portMAX_DELAY);
        }
        
        // Critical section - reading and modifying shared variable
        shared_counter++;
        
        // TODO: If use_mutex is true, unlock the mutex here
        if (use_mutex) {
            xSemaphoreGive(counterMutex);
        }
        
        // Small delay to increase chance of context switch (makes race condition visible)
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    
    ESP_LOGI(taskName, "Finished 1000 increments");
    
    // Task deletes itself when done
    vTaskDelete(NULL);
}

void monitorTask(void *pvParameter)
{
    const char *TAG = "Monitor";
    vTaskDelay(pdMS_TO_TICKS(2000));  // Wait for tasks to start
    
    while (1)
    {
        ESP_LOGI(TAG, "Current counter value: %d", shared_counter);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        // Check if both increment tasks are done
        if (uxTaskGetNumberOfTasks() <= 2)  // Only monitor task and idle task left
        {
            ESP_LOGI(TAG, "=====================================");
            ESP_LOGI(TAG, "FINAL COUNTER: %d (expected: 2000)", shared_counter);
            if (shared_counter == 2000) {
                ESP_LOGI(TAG, "✅ SUCCESS - No race condition!");
            } else {
                ESP_LOGW(TAG, "❌ RACE CONDITION - Lost %d increments!", 2000 - shared_counter);
                ESP_LOGW(TAG, "Set use_mutex=true and rerun to fix.");
            }
            ESP_LOGI(TAG, "=====================================");
            vTaskDelete(NULL);  // Monitor done
        }
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=====================================");
    ESP_LOGI(TAG, "Day 5 - Exercise 2: Mutex Demo");
    ESP_LOGI(TAG, "use_mutex = %s", use_mutex ? "TRUE" : "FALSE");
    ESP_LOGI(TAG, "=====================================");

    // TODO: Create mutex (even if not using yet)
    counterMutex = xSemaphoreCreateMutex();
    
    // Create two tasks that will increment the counter
    xTaskCreate(incrementTask, "Task1", 2048, (void *)"Task1", 5, NULL);
    xTaskCreate(incrementTask, "Task2", 2048, (void *)"Task2", 5, NULL);
    
    // Create monitor task to observe the counter
    xTaskCreate(monitorTask, "Monitor", 2048, NULL, 3, NULL);
    
    // TODO: First run with use_mutex = false to see race condition
    // TODO: Then change use_mutex = true and observe correct behavior
}