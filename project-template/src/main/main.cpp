/**
 * Day 4 - Exercise 1: Producer-Consumer Pattern
 *
 * CHALLENGE: Implement inter-task communication using queues
 *
 * REQUIREMENTS:
 * ✅ Create a queue that holds 5 integers
 * ✅ Producer task: Sends incrementing integers (0, 1, 2, ...) every 500ms
 * ✅ Consumer task: Receives integers and logs them
 * ✅ Both tasks run continuously
 *
 * FUNCTIONS YOU'LL NEED:
 * - xQueueCreate(length, item_size) - Create the queue
 * - xQueueSend(queue, &data, timeout) - Send data to queue
 * - xQueueReceive(queue, &buffer, timeout) - Receive data from queue
 *
 * C CONCEPTS TO LEARN:
 *
 * Queues and Data Copying
 * -----------------------
 * Queues COPY your data, they don't store pointers!
 *
 * Why use &data when sending?
 * - Queue needs the ADDRESS to read the data from
 * - It reads sizeof(int) bytes from that address
 * - It stores a COPY in the queue
 * - Your original variable is safe to reuse
 *
 * Example:
 * int data = 42;
 * xQueueSend(queue, &data, portMAX_DELAY);
 *                   ^--- Address of data
 * // Queue now has a copy of 42
 * // You can change data without affecting the queued value
 *
 * Receiving:
 * int received;
 * xQueueReceive(queue, &received, portMAX_DELAY);
 *                      ^--- Address where to store the data
 * // Queue copies its data INTO received variable
 *
 * DESIGN PATTERN: Producer-Consumer
 * ----------------------------------
 * One of the most fundamental patterns in embedded systems!
 *
 * Problem it solves:
 * - Decouple data generation from data processing
 * - Handle different rates (fast producer, slow consumer)
 * - Buffer data to prevent loss during processing
 *
 * Why use it:
 * - Sensor reads at fixed rate, processing time varies
 * - UART receives data asynchronously, parsing takes time
 * - Button events are instant, actions take longer
 *
 * Queue as the Buffer:
 * - Producer never waits for consumer (unless queue full)
 * - Consumer never misses data (unless queue empty)
 * - Both tasks are independent and loosely coupled
 *
 * CRITICAL THINKING QUESTIONS:
 * - Why does the queue COPY data instead of storing pointers?
 * - What happens if the producer is consistently faster than consumer?
 * - How would you size the queue? (Think: burst capacity, processing time)
 * - What's the difference between portMAX_DELAY and 0 for timeout?
 * - Why use sizeof(int) instead of just "4"?
 *
 * TIMEOUT VALUES:
 * - portMAX_DELAY = Block forever until space/data available
 * - 0 = Don't wait, return immediately if full/empty
 * - pdMS_TO_TICKS(1000) = Wait up to 1 second
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "QueueDemo";

// TODO: Declare a QueueHandle_t variable to store the queue handle
QueueHandle_t my_queue;

void producerTask(void *pvParameter)
{
    QueueHandle_t queue = (QueueHandle_t)pvParameter;
    const char *TAG = "producer";
    // TODO: Create producer task function
    // This task should:
    // - Have a counter that increments
    // - Send the counter value to the queue
    // - Delay 500ms between sends
    // - Log what it's sending

    int counter = 0;
    int delayms = 500;

    while (1)
    {
        xQueueSend(queue, &counter, portMAX_DELAY);
                ESP_LOGI(TAG, "Sent %d to Queue", counter++);

        vTaskDelay(pdMS_TO_TICKS(delayms));
    }
}

void consumerTask(void *pvParameter)
{
    QueueHandle_t queue = (QueueHandle_t)pvParameter;
    const char *TAG = "consumer";
    int receivedData = 0;

    while (1)
    {
        xQueueReceive(queue, &receivedData, portMAX_DELAY);
        ESP_LOGI(TAG, "Received %d from Queue", receivedData);
    }
    // TODO: Create consumer task function
    // This task should:
    // - Receive data from the queue (blocking)
    // - Log the received value
    // - Process immediately (no extra delay needed - blocked on receive)
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 4 - Exercise 1: Producer-Consumer");
    ESP_LOGI(TAG, "=================================");

    // TODO: Create the queue
    // Hint: my_queue = xQueueCreate(5, sizeof(int));
    my_queue = xQueueCreate(5, sizeof(int));
    // TODO: Create producer task
    xTaskCreate(&producerTask, "Producer", 2048, (void *)my_queue, 5, NULL);

    // TODO: Create consumer task
    xTaskCreate(&consumerTask, "Consumer", 2048, (void *)my_queue, 5, NULL);
}