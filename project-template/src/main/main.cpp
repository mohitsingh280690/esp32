/**
 * Day 8: GPIO Deep Dive - Interrupts and Advanced Control
 * 
 * OBJECTIVES:
 * - Master GPIO interrupt configuration and handling
 * - Implement ISR Deferral pattern (interrupt → queue → task)
 * - Learn designated initializers for clean struct config
 * - Understand IRAM_ATTR and why ISRs need special handling
 * - Handle debouncing in embedded systems
 * 
 * CHALLENGE:
 * Build a button-controlled LED system with proper interrupt handling.
 * Button presses should be detected via GPIO interrupt, queued to a task,
 * and processed there (not in the ISR itself).
 * 
 * HARDWARE SETUP:
 * - Button on GPIO 15 (pull-down enabled, active HIGH)
 * - LED on GPIO 2 (or any available GPIO)
 * 
 * REQUIREMENTS:
 * ✅ Configure button GPIO as input with interrupt on rising edge
 * ✅ Register ISR handler with IRAM_ATTR attribute
 * ✅ ISR should send event to queue (use xQueueSendFromISR)
 * ✅ Task receives from queue and toggles LED
 * ✅ Implement debouncing (50ms delay after button press)
 * ✅ Log button press count
 * ✅ System should be responsive (<50ms from press to LED toggle)
 * 
 * DESIGN PATTERN: ISR Deferral / Interrupt Handler
 * This is one of the MOST CRITICAL patterns in embedded systems!
 * 
 * Why defer work from ISR to task?
 * - ISRs must be FAST (microseconds, not milliseconds)
 * - Limited stack space in ISR context
 * - Many FreeRTOS functions can't be called from ISR
 * - Logging, delays, complex logic belong in task context
 * - Other interrupts are blocked during ISR
 * 
 * Pattern structure:
 * 1. ISR does MINIMAL work: read hardware, send to queue, exit
 * 2. Queue signals waiting task
 * 3. Task does the HEAVY processing: logging, state updates, algorithms
 * 
 * FUNCTIONS YOU'LL NEED:
 * - gpio_config() - Configure GPIO with designated initializers
 * - gpio_install_isr_service() - Initialize interrupt service (call once)
 * - gpio_isr_handler_add() - Register your ISR for specific GPIO
 * - xQueueCreate() - Create queue for ISR→Task communication
 * - xQueueSendFromISR() - Send from interrupt context (NOT xQueueSend!)
 * - xQueueReceive() - Receive in task context
 * - gpio_set_level() - Toggle LED
 * - vTaskDelay() - Debounce delay
 * 
 * C CONCEPTS IN THIS EXERCISE:
 * 
 * 1. IRAM_ATTR - Forces function into internal RAM
 *    Why? Flash cache is disabled during ISR! Code must be in RAM.
 *    Usage: void IRAM_ATTR my_isr_handler(void* arg) { }
 * 
 * 2. Designated Initializers - Clean struct initialization
 *    Old way: gpio_config_t conf = {0x01, 2, 1, 0, 3}; // What's what?
 *    New way: gpio_config_t conf = {
 *                 .pin_bit_mask = (1ULL << GPIO_NUM_15),
 *                 .mode = GPIO_MODE_INPUT,
 *                 .pull_up_en = GPIO_PULLUP_DISABLE,
 *                 .pull_down_en = GPIO_PULLDOWN_ENABLE,
 *                 .intr_type = GPIO_INTR_POSEDGE
 *             };
 * 
 * 3. ULL Suffix - Unsigned Long Long (64-bit)
 *    Why? ESP32 has 40+ GPIOs, needs 64-bit bitmask
 *    (1ULL << 35) works correctly, (1 << 35) might overflow
 * 
 * 4. xQueueSendFromISR vs xQueueSend
 *    FromISR versions are ISR-safe, regular versions are NOT
 *    Never call regular FreeRTOS functions from ISR!
 * 
 * 5. void* ISR Arguments
 *    gpio_isr_handler_add(pin, handler, (void*)button_id);
 *    Inside ISR: uint32_t id = (uint32_t)arg;
 * 
 * CRITICAL THINKING QUESTIONS:
 * 
 * Q1: Why can't you use ESP_LOGI() inside the ISR?
 *     (Hint: logging allocates memory, not ISR-safe)
 * 
 * Q2: What happens if you forget IRAM_ATTR on your ISR?
 *     (Hint: think about flash cache during interrupts)
 * 
 * Q3: Why use a queue instead of a global flag variable?
 *     (Hint: what about multiple quick button presses?)
 * 
 * Q4: How would you handle 3 different buttons using one ISR?
 *     (Hint: pass button ID as ISR argument)
 * 
 * Q5: What's the tradeoff between interrupt-driven and polling?
 *     (Hint: responsiveness vs code complexity)
 * 
 * SUCCESS CRITERIA:
 * - Button press toggles LED within 50ms
 * - No double-triggers from bouncing (debouncing works)
 * - Button count increments correctly
 * - No system crashes or watchdog resets
 * - Clean serial output (no garbled messages)
 * 
 * HINTS (NOT CODE):
 * - Create queue first, then configure GPIO, then install ISR service
 * - Queue should hold uint32_t (button press count or timestamp)
 * - ISR: Increment counter, send to queue, that's it!
 * - Task: Receive from queue, toggle LED, log message, add delay for debounce
 * - Use portMAX_DELAY for queue receive (task should block waiting)
 * - Check gpio_install_isr_service() return value
 * - Check gpio_isr_handler_add() return value
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "GPIO_Deep_Dive";

// Hardware configuration
#define BUTTON_GPIO GPIO_NUM_15
#define LED_GPIO GPIO_NUM_2

// TODO: Declare global queue handle for ISR→Task communication
// Hint: QueueHandle_t button_queue = NULL;


// TODO: Create ISR handler function with IRAM_ATTR
// Function signature: void IRAM_ATTR button_isr_handler(void* arg)
// Inside ISR:
// - Create a static counter to track button presses
// - Increment the counter
// - Send counter value to queue using xQueueSendFromISR()
// - Remember: NO logging, NO delays, NO complex logic in ISR!


// TODO: Create button task function
// Function signature: void buttonTask(void* pvParameter)
// Inside task infinite loop:
// - Receive from queue (blocking with portMAX_DELAY)
// - Toggle LED state
// - Log button press count with mutex protection if needed
// - Add debounce delay (vTaskDelay 50ms)


extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "===========================================");
    ESP_LOGI(TAG, "Day 8: GPIO Interrupts - ISR Deferral Pattern");
    ESP_LOGI(TAG, "===========================================");

    // TODO: Create queue
    // Hint: xQueueCreate(queue_length, item_size)
    // Suggested: 10 items, sizeof(uint32_t)

    
    // TODO: Configure button GPIO
    // Use designated initializers for gpio_config_t:
    // - pin_bit_mask: (1ULL << BUTTON_GPIO)
    // - mode: GPIO_MODE_INPUT
    // - pull_up_en: GPIO_PULLUP_DISABLE
    // - pull_down_en: GPIO_PULLDOWN_ENABLE
    // - intr_type: GPIO_INTR_POSEDGE (rising edge, button press)
    // Call gpio_config() with pointer to your config struct

    
    // TODO: Configure LED GPIO
    // Simple output configuration:
    // - gpio_reset_pin()
    // - gpio_set_direction()

    
    // TODO: Install ISR service
    // Hint: gpio_install_isr_service(0)
    // Check return value with ESP_ERROR_CHECK()

    
    // TODO: Register ISR handler for button GPIO
    // Hint: gpio_isr_handler_add(gpio_num, handler_function, arg)
    // arg can be NULL for now, or pass button ID

    
    // TODO: Create button task
    // Hint: xTaskCreate(buttonTask, "buttonTask", 2048, NULL, 5, NULL)

    
    ESP_LOGI(TAG, "System initialized. Press button to toggle LED!");
    ESP_LOGI(TAG, "Watch for ISR Deferral pattern in action.");
}