# Quick Reference Card

## 🔥 Common PlatformIO Commands

```bash
# Build project
pio run

# Upload to ESP32
pio run -t upload

# Serial monitor
pio device monitor

# Build + Upload + Monitor (all-in-one)
pio run -t upload && pio device monitor

# Clean build
pio run -t clean

# List connected devices
pio device list
```

## 📋 FreeRTOS Quick Reference

### Task Creation
```cpp
xTaskCreate(
    &task_function,    // Function pointer
    "task_name",       // Name (debugging)
    2048,              // Stack size (bytes)
    NULL,              // Parameters
    5,                 // Priority (0-24, higher=more priority)
    NULL               // Task handle (optional)
);
```

### Task Control
```cpp
vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay 1 second
vTaskDelete(NULL);                       // Delete current task
vTaskSuspend(task_handle);              // Suspend task
vTaskResume(task_handle);               // Resume task
```

### Queue Operations
```cpp
QueueHandle_t queue = xQueueCreate(10, sizeof(int));
xQueueSend(queue, &data, portMAX_DELAY);
xQueueReceive(queue, &buffer, portMAX_DELAY);
```

### Semaphores
```cpp
SemaphoreHandle_t sem = xSemaphoreCreateBinary();
xSemaphoreGive(sem);
xSemaphoreTake(sem, portMAX_DELAY);
```

### Mutexes
```cpp
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
xSemaphoreTake(mutex, portMAX_DELAY);
// Critical section
xSemaphoreGive(mutex);
```

## 🔌 GPIO Quick Reference

```cpp
#include "driver/gpio.h"

// Setup output
gpio_reset_pin(GPIO_NUM_2);
gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

// Control output
gpio_set_level(GPIO_NUM_2, 1);  // HIGH
gpio_set_level(GPIO_NUM_2, 0);  // LOW

// Setup input
gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
gpio_set_pull_mode(GPIO_NUM_4, GPIO_PULLUP_ONLY);

// Read input
int level = gpio_get_level(GPIO_NUM_4);
```

## 📝 Logging Quick Reference

```cpp
#include "esp_log.h"

static const char *TAG = "MyApp";

ESP_LOGE(TAG, "Error message");     // Red
ESP_LOGW(TAG, "Warning message");   // Yellow
ESP_LOGI(TAG, "Info message");      // Green
ESP_LOGD(TAG, "Debug message");     // Gray
ESP_LOGV(TAG, "Verbose message");   // Gray (rarely used)

// With variables
ESP_LOGI(TAG, "Value: %d", value);
ESP_LOGI(TAG, "String: %s", string);

// Set log level
esp_log_level_set("*", ESP_LOG_DEBUG);  // Global
esp_log_level_set(TAG, ESP_LOG_INFO);   // Per-tag
```

## ⏱️ Timer Quick Reference

```cpp
#include "esp_timer.h"

// Delay
vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1 second
esp_rom_delay_us(500);                  // 500 microseconds

// Get time
int64_t time_us = esp_timer_get_time();  // Microseconds since boot
```

## 🔗 Common Patterns

### Task Function Template
```cpp
void my_task(void *pvParameter) {
    // Initialization
    
    while(1) {
        // Task work
        
        vTaskDelay(pdMS_TO_TICKS(1000));  // Yield to scheduler
    }
}
```

### extern "C" for app_main
```cpp
extern "C" void app_main(void) {
    // ESP-IDF entry point
    // Can use C++ inside here
    
    xTaskCreate(&my_task, "my_task", 2048, NULL, 5, NULL);
}
```

### Producer-Consumer Pattern
```cpp
QueueHandle_t queue;

void producer(void *p) {
    while(1) {
        int data = get_data();
        xQueueSend(queue, &data, portMAX_DELAY);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void consumer(void *p) {
    int buffer;
    while(1) {
        if(xQueueReceive(queue, &buffer, portMAX_DELAY)) {
            process(buffer);
        }
    }
}
```

## 🐛 Debugging Tips

### Check Stack Usage
```cpp
UBaseType_t stack_left = uxTaskGetStackHighWaterMark(NULL);
ESP_LOGI(TAG, "Stack remaining: %d bytes", stack_left);
```

### Task Info
```cpp
char buffer[512];
vTaskList(buffer);
ESP_LOGI(TAG, "\n%s", buffer);
```

### Watchdog
```cpp
#include "esp_task_wdt.h"

esp_task_wdt_init(5, true);  // 5 second timeout
esp_task_wdt_add(NULL);       // Add current task
esp_task_wdt_reset();         // Reset watchdog (call periodically)
```

## 📊 Priority Guidelines

- **0:** Idle task (system reserved)
- **1-2:** Low priority (logging, background tasks)
- **3-5:** Normal priority (most application tasks)
- **6-9:** High priority (time-critical tasks)
- **10-24:** Very high (interrupt handlers, critical timing)

## 🔢 Stack Size Guidelines

- **2048 bytes:** Simple tasks (LED blink, basic logging)
- **4096 bytes:** Moderate tasks (string processing, simple calculations)
- **8192 bytes:** Complex tasks (JSON parsing, network operations)
- **16384+ bytes:** Very complex (image processing, large buffers)

**Tip:** Use `uxTaskGetStackHighWaterMark()` to check actual usage!

## 📚 Documentation Links

**ESP-IDF API:** https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/  
**FreeRTOS:** https://www.freertos.org/a00106.html  
**PlatformIO:** https://docs.platformio.org/en/latest/platforms/espressif32.html

---

**Print this for quick reference while coding!**
