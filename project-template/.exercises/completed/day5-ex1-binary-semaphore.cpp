/**
 * Day 5 - Exercise 1: Binary Semaphore for Signaling
 *
 * CHALLENGE: Use semaphores to coordinate tasks
 *
 * REQUIREMENTS:
 * ✅ Create a binary semaphore for task coordination
 * ✅ Producer task: Sends semaphore signal every 2 seconds
 * ✅ Consumer task: Waits for semaphore, then performs action
 * ✅ Log when signal is given and received
 *
 * FUNCTIONS YOU'LL NEED:
 * - xSemaphoreCreateBinary() - Create binary semaphore
 * - xSemaphoreGive(semaphore) - Signal the semaphore
 * - xSemaphoreTake(semaphore, timeout) - Wait for semaphore
 *
 * C CONCEPTS TO LEARN:
 *
 * Semaphores vs Queues - What's the Difference?
 * ----------------------------------------------
 * QUEUE: Passes DATA between tasks
 * - xQueueSend() copies your data into queue
 * - xQueueReceive() copies data out
 * - Use for: Sensor readings, commands, packets
 *
 * SEMAPHORE: Signals EVENTS, no data
 * - xSemaphoreGive() sets flag (count = 1)
 * - xSemaphoreTake() clears flag (count = 0)
 * - Use for: "Something happened!", "Resource available", "Go!"
 *
 * Binary Semaphore States:
 * - Count = 0: Not available (task will block on Take)
 * - Count = 1: Available (task can Take immediately)
 *
 * Think of it like a flag:
 * - Give() raises the flag
 * - Take() lowers the flag and proceeds
 * - If flag is down, Take() waits until someone raises it
 *
 * DESIGN PATTERN: Event Signaling
 * --------------------------------
 * One of the most common synchronization patterns!
 *
 * Problem it solves:
 * - Task B needs to wait for Task A to finish something
 * - Task needs to wait for external event (button, sensor, timer)
 * - Deferred interrupt handling (ISR → Task)
 *
 * Classic use cases:
 * - Button press → Action task
 * - Data ready → Processing task
 * - Timer expired → Periodic task
 * - Hardware interrupt → Handler task
 *
 * Without semaphore (BAD):
 * - Polling: while(!flag) { vTaskDelay(10); }  ← Wastes CPU!
 * - Global flag with race conditions
 * - Busy-wait loops
 *
 * With semaphore (GOOD):
 * - Task blocks efficiently (zero CPU usage)
 * - OS wakes task immediately when signaled
 * - Clean, race-free coordination
 *
 * SemaphoreHandle_t - Another Handle Type
 * ----------------------------------------
 * Like TaskHandle_t and QueueHandle_t:
 * - Opaque pointer to semaphore object
 * - Must be initialized before use
 * - Pass to Give/Take functions
 * - Can be shared between tasks
 *
 * Example:
 * SemaphoreHandle_t mySemaphore;
 * mySemaphore = xSemaphoreCreateBinary();
 *               ^--- Returns handle or NULL on failure
 *
 * CRITICAL THINKING QUESTIONS:
 * - Why use semaphore instead of a global flag variable?
 * - What happens if you Give() twice without Take()?
 * - Binary semaphore vs counting semaphore - what's the difference?
 * - Can multiple tasks wait on the same semaphore?
 * - What happens if you Take() but no one ever Give()s?
 *
 * TIMEOUT VALUES:
 * - portMAX_DELAY = Wait forever
 * - 0 = Check and return immediately (non-blocking)
 * - pdMS_TO_TICKS(5000) = Wait up to 5 seconds
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "SemaphoreDemo";

// TODO: Declare a SemaphoreHandle_t variable to store the semaphore handle
SemaphoreHandle_t mySemaphore = NULL;

void signalerTask(void *pvParameter)
{

    SemaphoreHandle_t smphr = (SemaphoreHandle_t)pvParameter;
    const char *TAG = "SignalerTask";
    while (1)
    {
        ESP_LOGI(TAG, "About to Send a Signal");
        xSemaphoreGive(smphr);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void waiterTask(void *pvParameter)
{
    SemaphoreHandle_t smphr = (SemaphoreHandle_t)pvParameter;
    const char *TAG = "WaiterTask";
    while (1)
    {
        xSemaphoreTake(smphr, portMAX_DELAY);
        ESP_LOGI(TAG, "Received Signal - Processing work...");
        
        // Simulate work being done
        vTaskDelay(pdMS_TO_TICKS(500));
        ESP_LOGI(TAG, "Work completed!");
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 5 - Exercise 1: Binary Semaphore");
    ESP_LOGI(TAG, "=================================");

    // Create the binary semaphore
    mySemaphore = xSemaphoreCreateBinary();

    // Create signaler task (sends signal every 2 seconds)
    xTaskCreate(signalerTask, "signaler", 2048, (void *)mySemaphore, 5, NULL);
    
    // Create waiter task (waits for signal)
    xTaskCreate(waiterTask, "waiter", 2048, (void *)mySemaphore, 5, NULL);
}