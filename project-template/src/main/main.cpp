#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_random.h"

static const char *TAG = "LEDController";

typedef struct
{
    QueueHandle_t patternQHandle;
    QueueHandle_t speedQHandle;
} g_serialHandle;

gpio_num_t LED[4] = {(gpio_num_t)4, (gpio_num_t)16, (gpio_num_t)17, (gpio_num_t)5};
gpio_num_t BUTTON = (gpio_num_t)15;

uint16_t g_speed_ms = 400;

QueueHandle_t g_patternQueue = NULL;
QueueHandle_t g_speedQueue = NULL;
g_serialHandle sHandle;

char g_commandBuffer[32] = {0};

int knightRider(void)
{
    static int pos = 0;
    static int direction = 1;

    for (int i = 0; i < 4; i++)
    {
        gpio_set_level(LED[i], (i == pos) ? 0 : 1);
    }

    pos += direction;

    if (pos == 3 || pos == 0)
    {
        direction = -direction;
    }

    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

int blinkAll(void)
{
    static bool ON_OFF = 0;

    for (int i = 0; i < 4; i++)
    {
        gpio_set_level(LED[i], (ON_OFF) ? 0 : 1);
    }

    ON_OFF = !ON_OFF;
    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

int alternatingPair(void)
{
    static bool pairNumber = 0;

    if (pairNumber == 0)
    {
        gpio_set_level(LED[0], 0);
        gpio_set_level(LED[1], 0);
        gpio_set_level(LED[2], 1);
        gpio_set_level(LED[3], 1);
    }
    else
    {
        gpio_set_level(LED[0], 1);
        gpio_set_level(LED[1], 1);
        gpio_set_level(LED[2], 0);
        gpio_set_level(LED[3], 0);
    }

    pairNumber = !pairNumber;
    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

int randomPattern(void)
{
    for (int i = 0; i < 4; i++)
    {
        gpio_set_level(LED[i], rand() % 2);
    }
    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

void patternSequencer(void *pvParameter)
{
    g_serialHandle *g_Handle = (g_serialHandle *)pvParameter;
    uint16_t selectedPattern = 0;
    uint16_t newPattern = 0;
    uint16_t newSpeed = 0;
    while (1)
    {
        if (xQueueReceive(g_Handle->speedQHandle, &newSpeed, 0) == pdTRUE)
        {
            g_speed_ms = newSpeed;
            ESP_LOGI("PATTERN_SEQUENCER", "SELECTED SPEED: %d", newSpeed);
        }

        if (xQueueReceive(g_Handle->patternQHandle, &newPattern, 0) == pdTRUE)

        {
            selectedPattern = newPattern;
            ESP_LOGI("PATTERN_SEQUENCER", "SELECTED PATTERN: %d", newPattern);
        }
        if (selectedPattern == 0)
            knightRider();
        else if (selectedPattern == 1)
            blinkAll();
        else if (selectedPattern == 2)
            alternatingPair();
        else if (selectedPattern == 3)
            randomPattern();
    }
}

void buttonTask(void *pvParameter)
{
    QueueHandle_t qHandle = (QueueHandle_t)pvParameter;
    uint16_t buttonCounter = 0;
    while (1)
    {
        if (gpio_get_level(BUTTON) == 1)
        {
            ESP_LOGI("BUTTON_TASK", "BUTTON PRESSED");
            buttonCounter = buttonCounter + 1;
            if (buttonCounter == 4)
                buttonCounter = 0;
            xQueueSend(qHandle, &buttonCounter, portMAX_DELAY);
            ESP_LOGI("BUTTON_TASK", "BUTTON COUNTER VALUE: %d", buttonCounter);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void serialTask(void *pvParameter)
{
    g_serialHandle *handles = (g_serialHandle *)pvParameter;
    char rxtext[50] = {0};
    uint16_t rxdPattern = 0;
    uint16_t rxdSpeed = 0;

    ESP_LOGI("SERIALTASK", "Entered Serial Task");

    while (1)
    {
        if (fgets(rxtext, sizeof(rxtext), stdin) != NULL)
        {
            ESP_LOGI("SERIALTASK", "Received: %s", rxtext);

            char cmd[20] = {0};
            int value = 0;

            if (sscanf(rxtext, "%s %d", cmd, &value) >= 1)
            {
                if (strcmp(cmd, "pattern") == 0 && value >= 0 && value <= 3)
                {
                    rxdPattern = (uint16_t)value;
                    xQueueSend(handles->patternQHandle, &rxdPattern, 0);
                    ESP_LOGI("SERIALTASK", "Pattern changed to: %d", rxdPattern);
                }
                else if (strcmp(cmd, "speed") == 0 && value >= 50 && value <= 1000)
                {
                    rxdSpeed = (uint16_t)value;
                    xQueueSend(handles->speedQHandle, &rxdSpeed, 0);
                    ESP_LOGI("SERIALTASK", "Speed changed to: %d", rxdSpeed);
                }
                else if (strcmp(cmd, "status") == 0)
                {
                    ESP_LOGI("SERIALTASK", "Status requested");
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "===========================================");
    ESP_LOGI(TAG, "Multi-Task LED Controller - Practice Project");
    ESP_LOGI(TAG, "===========================================");

    g_patternQueue = xQueueCreate(10, sizeof(int));
    g_speedQueue = xQueueCreate(10, sizeof(int));
    sHandle.patternQHandle = g_patternQueue;
    sHandle.speedQHandle = g_speedQueue;

    for (int i = 0; i < 4; i++)
    {
        gpio_reset_pin(LED[i]);
        gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
    }

    gpio_reset_pin(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON);

    ESP_LOGI(TAG, "System initialized. Tasks running...");
    ESP_LOGI(TAG, "Commands: pattern <0-3>, speed <50-1000>, status");

    xTaskCreate(patternSequencer, "pattern", 2048, &sHandle, 3, NULL);
    xTaskCreate(buttonTask, "buttonTask", 2048, g_patternQueue, 5, NULL);
    xTaskCreate(serialTask, "SerialTask", 4096, &sHandle, 2, NULL);
}