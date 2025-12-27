/**
 * Day 5 - Exercise 2: Mutex for Shared UART (Real-World Example)
 *
 * CHALLENGE: See why UART/Serial printing needs mutex protection
 *
 * THE PROBLEM:
 * Multiple tasks printing to serial monitor simultaneously will produce
 * GARBLED, INTERLEAVED output that's impossible to read.
 *
 * Example WITHOUT mutex:
 * Task TaTasskkk A121 :c: ocuonuttne:r c=o u10n2t5e3r = 1024
 * 
 * Example WITH mutex:
 * Task A: counter = 1025
 * Task B: counter = 1026
 *
 * REQUIREMENTS:
 * ✅ Create multiple tasks printing multi-line messages
 * ✅ WITHOUT mutex: Observe garbled output
 * ✅ WITH mutex: Observe clean, readable output
 *
 * REAL-WORLD USE CASE:
 * This is EXACTLY why ESP_LOGI uses internal mutexes!
 * Any time multiple tasks share a resource (UART, SPI, I2C), you need mutex
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
        printf("====================================");
        printf("\n");
        printf("%s is printing...", taskName);
        printf("\n");
        printf("Counter value: %d", counter++);
        printf("\n");
        printf("====================================");
        printf("\n\n");
        
        // TODO: If use_mutex is true, unlock the mutex here
        if (use_mutex) {
            xSemaphoreGive(uartMutex);
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));  // Small delay between prints
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