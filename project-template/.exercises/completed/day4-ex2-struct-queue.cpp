/**
 * Day 4 - Exercise 2: Sending Structs via Queue
 *
 * CHALLENGE: Queue complex data structures instead of simple integers
 *
 * REQUIREMENTS:
 * ✅ Define a struct with multiple fields (timestamp, sensor_id, value)
 * ✅ Create a queue that holds these structs
 * ✅ Producer task: Creates sensor readings and sends them every 800ms
 * ✅ Consumer task: Receives structs and logs ALL fields
 * ✅ Both tasks run continuously
 *
 * FUNCTIONS YOU'LL NEED:
 * - xQueueCreate(length, sizeof(your_struct_t))
 * - xQueueSend(queue, &struct_variable, timeout)
 * - xQueueReceive(queue, &struct_variable, timeout)
 *
 * C CONCEPTS TO LEARN:
 *
 * Structs - Grouping Related Data
 * --------------------------------
 * Instead of separate variables, group them together!
 *
 * Why use structs?
 * - Organize related data (timestamp + sensor_id + value belong together)
 * - Pass multiple values in one queue item
 * - Represent real-world entities (sensor reading, GPS position, etc.)
 * - Type safety - fields have names, not just array indices
 *
 * typedef struct - Creating Type Aliases
 * ---------------------------------------
 * typedef struct {
 *     uint32_t timestamp;    // 4 bytes - milliseconds since boot
 *     uint8_t sensor_id;     // 1 byte - which sensor (0-255)
 *     float temperature;     // 4 bytes - degrees Celsius
 * } sensor_data_t;
 *          ^--- The new type name (convention: _t suffix)
 *
 * Why typedef?
 * - Cleaner syntax: sensor_data_t data; (not struct sensor_data data;)
 * - Common C convention in embedded systems
 * - Matches FreeRTOS style (TaskHandle_t, QueueHandle_t)
 *
 * Designated Initializers - Clear and Safe
 * -----------------------------------------
 * sensor_data_t reading = {
 *     .timestamp = 12345,
 *     .sensor_id = 1,
 *     .temperature = 23.5
 * };
 *
 * Why use designated initializers?
 * - Explicit: You see which value goes where
 * - Order-independent: Can initialize in any order
 * - Safe: Compiler catches typos in field names
 * - Self-documenting code
 *
 * Struct Memory Layout
 * --------------------
 * sizeof(sensor_data_t) might NOT be 4+1+4 = 9 bytes!
 * Could be 12 bytes due to PADDING for alignment.
 *
 * Why padding?
 * - CPU reads memory more efficiently on aligned boundaries
 * - uint32_t wants to start at address divisible by 4
 * - Compiler adds invisible padding bytes
 *
 * Example layout:
 * [timestamp: 4 bytes][sensor_id: 1 byte][padding: 3 bytes][temperature: 4 bytes]
 * Total = 12 bytes, not 9!
 *
 * Why this matters for queues:
 * - xQueueCreate(10, sizeof(sensor_data_t)) allocates 10 * 12 = 120 bytes
 * - Queue copies ALL bytes including padding
 * - ALWAYS use sizeof(), never hardcode sizes
 *
 * DESIGN PATTERN: Producer-Consumer (with Structs)
 * -------------------------------------------------
 * Same pattern as Exercise 1, but with richer data!
 *
 * Real-world applications:
 * - Sensor readings (temp, humidity, pressure) from I2C sensor
 * - GPS coordinates (latitude, longitude, altitude, timestamp)
 * - UART packets (command, payload, checksum)
 * - Button events (gpio_num, press_time, state)
 *
 * Why structs in embedded systems?
 * - Hardware often returns multiple related values
 * - Protocols have multi-field messages
 * - Debugging: Log complete state in one line
 * - Maintainable: Add/remove fields in one place
 *
 * CRITICAL THINKING QUESTIONS:
 * - What's the memory cost of a 10-item queue of structs vs integers?
 * - When would you queue pointers to structs instead of copying? (Advanced!)
 * - How would you handle variable-length data (strings, arrays)?
 * - Why not use a global struct instead of queuing? (Hint: thread safety)
 * - What fields would YOU add to make this more realistic?
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "StructQueue";

typedef struct
{
    uint32_t timeStamp;
    uint8_t sensorID;
    float sensorVal;
} sensor_data_t;

QueueHandle_t qHandle;

void producerTask(void *pvParameter)
{
    QueueHandle_t handle = (QueueHandle_t)pvParameter;
    const char *TAG = "Producer";
    uint32_t timeStamp = 0;
    sensor_data_t dataToSend;

    while (1)
    {
        dataToSend.timeStamp = timeStamp * 800;
        dataToSend.sensorID = 1;
        dataToSend.sensorVal = 0.2f + (timeStamp / 10.0f);
        xQueueSend(handle, &dataToSend, portMAX_DELAY);
        ESP_LOGI(TAG, "Sending Data - Timestamp: %lu ms, Sensor ID: %u, Sensor Value: %.2f", (unsigned long)dataToSend.timeStamp, dataToSend.sensorID, dataToSend.sensorVal);
        timeStamp++;
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

void consumerTask(void *pvParameter)
{
    QueueHandle_t handle = (QueueHandle_t)pvParameter;
    const char *TAG = "Consumer";
    sensor_data_t rxData;
    while (1)
    {
        xQueueReceive(handle, &rxData, portMAX_DELAY);
        ESP_LOGI(TAG, "Received Data - Timestamp: %lu ms, Sensor ID: %u, Sensor Value: %.2f", (unsigned long)rxData.timeStamp, rxData.sensorID, rxData.sensorVal);
    }
}

extern "C" void app_main(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 4 - Exercise 2: Sending Structs");
    ESP_LOGI(TAG, "=================================");
    qHandle = xQueueCreate(5, sizeof(sensor_data_t));
    xTaskCreate(producerTask,"prod",2048,(void*)qHandle,5,NULL);
    xTaskCreate(consumerTask,"cons",2048,(void*)qHandle,5,NULL);
}