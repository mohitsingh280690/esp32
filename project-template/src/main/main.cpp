/**
 * Day 2 - Exercise 3: Passing Multiple Parameters with Structs
 *
 * CHALLENGE: Pass BOTH pin number AND delay to a generic blink task
 * Since you have only one LED, we'll simulate multiple by logging different names
 * This teaches you struct usage - critical for passing complex data to tasks
 *
 * REQUIREMENTS:
 * ✅ Define a struct to hold pin and delay_ms
 * ✅ Use typedef for cleaner syntax
 * ✅ Create 3 task instances with different configurations
 * ✅ Properly manage struct memory lifetime (static or heap)
 * ✅ Access struct members using -> operator
 * ✅ Clean, reusable code
 *
 * FUNCTIONS YOU'LL NEED:
 * - gpio_reset_pin()
 * - gpio_set_direction()
 * - gpio_set_level()
 * - xTaskCreate() - pass struct pointer as parameter!
 *
 * C CONCEPTS IN THIS EXERCISE:
 * - struct: Grouping related data under one type
 * - typedef: Creating type aliases (blink_config_t)
 * - Arrow operator: config->pin vs config.pin (pointer vs value)
 * - Memory allocation: static vs stack vs heap
 * - Pointer to struct: Passing address of struct
 * - Member access: How to get data from struct pointer
 *
 * CRITICAL THINKING:
 * - Why pass struct POINTER instead of copying the whole struct?
 * - Where should you allocate the structs? (Stack of app_main? Static? Heap?)
 * - What happens if app_main's stack structs are destroyed before task reads them?
 * - How does the size of the struct affect your decision?
 * - When would you use malloc() for struct allocation?
 *
 * EXPECTED BEHAVIOR:
 * - LED blinks (you have GPIO 2)
 * - Three "virtual" LEDs via logging (LED1, LED2, LED3)
 * - Each logs at different intervals (200ms, 500ms, 1000ms)
 * - All run simultaneously
 *
 * STRUCT TEMPLATE (don't copy, understand!):
 * typedef struct {
 *     gpio_num_t pin;
 *     int delay_ms;
 *     const char* name;
 * } blink_config_t;
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
blinkConfig_t config3 = {1000, LED3, "SlowLED"};

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

// TODO: Create blink task that accepts struct pointer
// Cast pvParameter to your struct type
// Access members using -> operator
// Initialize GPIO using the pin from struct
// Use delay from struct
// Log using name from struct

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
