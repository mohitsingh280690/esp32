/**
 * Day 3 - Exercise 1: Priority Demonstration
 * COMPLETED: December 22, 2025
 * 
 * Demonstrates:
 * - Three tasks with different priorities (5, 3, 1)
 * - Priority-based preemptive scheduling
 * - Counter logging to show execution frequency
 */

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void countingTask(void *pvParameter);


const char *  TAG1="TASK1";
const char *  TAG2="TASK2";
const char *  TAG3="TASK3";


extern "C" void app_main(void){
        esp_log_level_set("*", ESP_LOG_INFO);
        xTaskCreate(countingTask,"TASK 1",2048,(void *)TAG1,5,NULL);
        xTaskCreate(countingTask,"TASK 2",2048,(void *)TAG2,3,NULL);
        xTaskCreate(countingTask,"TASK 3",2048,(void *)TAG3,1,NULL);  // Fixed: TAG3
}

void countingTask(void *pvParameter){
    const char * TAG = (char *)pvParameter;
    int counter=0;

    while(1){
        counter++;
        if(counter % 1000 == 0) {  // Log every 100 iterations
            ESP_LOGI(TAG, "Counter value is %d", counter);
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // 5ms delay
    }
}
