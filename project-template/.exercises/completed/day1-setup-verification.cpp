/**
 * ESP32 WROOM Boilerplate - Starting Template
 * 
 * This is a minimal LED blink example to verify your setup works.
 * Once you confirm this works, you'll start Challenge 1 (Day 1, Exercise 3).
 * 
 * Board: ESP32 WROOM
 * LED Pin: GPIO 2 (built-in LED on most ESP32 WROOM boards)
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_PIN GPIO_NUM_2

static const char *TAG = "Setup-Test";

void led_blink_task(void *pvParameter) {
    // GPIO setup
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    
    ESP_LOGI(TAG, "LED blink task started on GPIO %d", LED_PIN);
    ESP_LOGI(TAG, "If LED is blinking, your setup is complete!");
    
    while(1) {
        gpio_set_level(LED_PIN, 1);
        ESP_LOGI(TAG, "LED ON");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        gpio_set_level(LED_PIN, 0);
        ESP_LOGI(TAG, "LED OFF");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "ESP32 WROOM - Setup Verification");
    ESP_LOGI(TAG, "=================================");
    
    xTaskCreate(&led_blink_task, "led_blink", 2048, NULL, 5, NULL);
}
