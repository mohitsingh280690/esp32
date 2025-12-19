/**
 * Day 1 - Exercise 3: ESP-IDF Logging Levels
 *
 * CHALLENGE: Modify the LED blink task to use all ESP-IDF log levels
 *
 * REQUIREMENTS:
 * ✅ Track number of blink cycles with a counter variable
 * ✅ Use ESP_LOGI() when LED turns ON
 * ✅ Use ESP_LOGW() when LED turns OFF
 * ✅ Use ESP_LOGE() every 5 complete blinks to report "X blinks completed"
 * ✅ Use ESP_LOGD() to show the current counter value each cycle
 * ✅ Counter starts at 0 and increments after each complete ON/OFF cycle
 *
 * FUNCTIONS TO USE:
 * - ESP_LOGI(TAG, "message") - Info level logging
 * - ESP_LOGW(TAG, "message") - Warning level logging
 * - ESP_LOGE(TAG, "message") - Error level logging
 * - ESP_LOGD(TAG, "message") - Debug level logging (may not show by default)
 *
 * C CONCEPTS YOU'LL USE:
 * - static variables inside functions (persistent state)
 * - Modulo operator (%) for detecting every Nth occurrence
 * - Printf-style format strings (%d for integers)
 *
 * CRITICAL THINKING:
 * - Why use 'static' for the counter variable?
 * - What happens to a normal (non-static) variable between function calls?
 * - When should you increment the counter?
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_PIN GPIO_NUM_2

static const char *TAG = "Day1-Ex3";
/*

I (1000) Day1-Ex3: LED ON
W (1000) Day1-Ex3: LED OFF
D (1001) Day1-Ex3: Counter: 1
I (2000) Day1-Ex3: LED ON
W (2000) Day1-Ex3: LED OFF
D (2001) Day1-Ex3: Counter: 2
...
E (5001) Day1-Ex3: 5 blinks completed
...

*/
void led_blink_task(void *pvParameter)
{
    // GPIO setup
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    ESP_LOGI(TAG, "LED blink task started - Exercise 3");

    uint32_t blinkCounter = 0;

    while (1)
    {
        // TODO: Turn LED ON
        // TODO: Log "LED ON" using appropriate log level (check requirements)
        ESP_LOGI(TAG, "LED ON");
        gpio_set_level(LED_PIN, 1);

        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // TODO: Turn LED OFF
        // TODO: Log "LED OFF" using appropriate log level (check requirements)
        ESP_LOGW(TAG, "LED OFF");
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // TODO: Increment counter after complete ON/OFF cycle
        blinkCounter++;
        // TODO: Log current counter value using ESP_LOGD()
        ESP_LOGD(TAG, "Counter : %d", blinkCounter);

        // TODO: Check if counter is divisible by 5
        // TODO: If yes, log "X blinks completed" using ESP_LOGE()
        if (blinkCounter % 5 == 0)
        {
            ESP_LOGE(TAG, "%d blinks completed", blinkCounter);
        }
    }
}

extern "C" void app_main(void)
{
        esp_log_level_set("*", ESP_LOG_DEBUG);

    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "Day 1 - Exercise 3: Logging Levels");
    ESP_LOGI(TAG, "=================================");

    xTaskCreate(&led_blink_task, "led_blink", 2048, NULL, 5, NULL);
}
