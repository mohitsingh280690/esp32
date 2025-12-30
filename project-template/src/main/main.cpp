/**
 * Days 6-7: PRACTICE PROJECT - Multi-Task LED Controller
 *
 * 🎯 OBJECTIVE:
 * Build a complete embedded system that consolidates ALL Week 1 concepts:
 * - Tasks (Day 1-2)
 * - Priorities (Day 3)
 * - Queues (Day 4)
 * - Semaphores & Mutexes (Day 5)
 *
 * 🏗️ SYSTEM ARCHITECTURE:
 *
 * ┌─────────────┐     pattern     ┌──────────────┐
 * │   Button    │──── Queue ────→ │   Pattern    │
 * │   Handler   │                 │  Sequencer   │
 * └─────────────┘                 └──────┬───────┘
 *                                        │ controls
 *                                        ↓
 *                                   ┌─────────┐
 *                                   │ 4 LEDs  │
 *                                   └─────────┘
 *                                        ↑
 *                                        │ controls
 * ┌─────────────┐     pattern     ┌──────┴───────┐
 * │   Serial    │──── Queue ────→ │   Pattern    │
 * │   Command   │                 │  Sequencer   │
 * └─────────────┘                 └──────────────┘
 *       ↑
 *       │ protected by mutex
 *       │
 * ┌─────────────┐
 * │   Status    │
 * │  Reporter   │
 * └─────────────┘
 *
 * 📋 REQUIREMENTS:
 *
 * Task 1: Pattern Sequencer (Priority: 3)
 * ✅ Reads pattern commands from queue
 * ✅ Controls 4 LEDs based on current pattern
 * ✅ Patterns: Knight Rider, Blink All, Alternating, Random
 * ✅ Speed adjustable (delay between steps)
 *
 * Task 2: Button Handler (Priority: 5 - Highest)
 * ✅ Monitors button press (polling or interrupt-based)
 * ✅ Cycles through patterns on button press
 * ✅ Sends pattern change command to queue
 * ✅ Response time < 50ms
 *
 * Task 3: Serial Command Parser (Priority: 2)
 * ✅ Reads commands from UART (use scanf or ESP-IDF console)
 * ✅ Commands: "pattern <0-3>", "speed <50-1000>", "status"
 * ✅ Sends pattern/speed changes to appropriate queues
 * ✅ Uses mutex for serial output
 *
 * Task 4: Status Reporter (Priority: 1 - Lowest)
 * ✅ Prints system status every 5 seconds
 * ✅ Shows: Current pattern, speed, uptime, task states
 * ✅ Uses mutex to protect UART output
 *
 * 🎨 LED PATTERNS:
 *
 * Pattern 0 - Knight Rider (Sweeping):
 * ●○○○ → ○●○○ → ○○●○ → ○○○● → ○○●○ → ○●○○ → repeat
 *
 * Pattern 1 - Blink All Together:
 * ●●●● → ○○○○ → ●●●● → ○○○○ → repeat
 *
 * Pattern 2 - Alternating Pairs:
 * ●●○○ → ○○●● → ●●○○ → ○○●● → repeat
 *
 * Pattern 3 - Random:
 * Random LED on/off each step
 *
 * 🔧 HARDWARE SETUP:
 * - 4 LEDs on GPIOs (you choose which pins) d4 d16 d17 d5
 * - 1 Button on GPIO (you choose) d15
 * - Serial console (115200 baud)
 *
 * 💡 DESIGN CONSIDERATIONS:
 *
 * Queues:
 * - Pattern command queue (button & serial → sequencer)
 * - Speed command queue (serial → sequencer)
 *
 * Mutexes:
 * - UART output mutex (status reporter & serial parser share)
 *
 * Priorities (WHY these priorities?):
 * - Button (5): User interaction must feel instant
 * - Sequencer (3): LED timing is visible but not critical
 * - Serial (2): Can tolerate slight delay
 * - Status (1): Background task, runs when nothing else needs CPU
 *
 * C CONCEPTS TO APPLY:
 *
 * 1. Enums for Pattern Types:
 *    enum Pattern { KNIGHT_RIDER, BLINK_ALL, ALTERNATING, RANDOM };
 *
 * 2. Structs for Commands:
 *    typedef struct {
 *        enum Pattern pattern;
 *        uint32_t g_speed_ms;
 *    } command_t;
 *
 * 3. Arrays for LED Pins:
 *    const int led_pins[4] = {GPIO_NUM_X, GPIO_NUM_Y, ...};
 *
 * 4. Function Pointers for Patterns (Advanced):
 *    void (*pattern_functions[])(void) = {knight_rider, blink_all, ...};
 *
 * 📚 FUNCTIONS YOU'LL NEED:
 *
 * From FreeRTOS:
 * - xTaskCreate() / xTaskCreatePinnedToCore()
 * - xQueueCreate()
 * - xQueueSend() / xQueueReceive()
 * - xSemaphoreCreateMutex()
 * - xSemaphoreTake() / xSemaphoreGive()
 * - vTaskDelay()
 *
 * From ESP-IDF:
 * - gpio_set_direction()
 * - gpio_set_level()
 * - gpio_get_level()
 * - ESP_LOGI() for logging
 *
 * For Serial Input:
 * - scanf() (simple)
 * - Or ESP-IDF Console Component (advanced)
 *
 * 🚀 GETTING STARTED:
 *
 * Step 1: Define Your Data Structures
 * - Pattern enum
 * - Command struct
 * - LED pin array
 *
 * Step 2: Initialize Hardware
 * - Configure GPIOs for LEDs (output)
 * - Configure GPIO for button (input, pull-up)
 *
 * Step 3: Create Synchronization Objects
 * - Pattern queue
 * - Speed queue (or combine in one command struct)
 * - UART mutex
 *
 * Step 4: Implement Pattern Functions
 * - knight_rider()
 * - blink_all()
 * - alternating()
 * - random_pattern()
 *
 * Step 5: Implement Each Task
 * - Start simple: Get one pattern working
 * - Add button control
 * - Add serial commands
 * - Add status reporter last
 *
 * Step 6: Test & Debug
 * - Test each pattern individually
 * - Verify button responsiveness
 * - Check for race conditions in serial output
 * - Ensure clean system behavior
 *
 * ⚠️ COMMON PITFALLS TO AVOID:
 *
 * 1. Forgetting to initialize GPIOs
 * 2. Not protecting UART with mutex (garbled output!)
 * 3. Wrong priority (button feels sluggish)
 * 4. Not checking queue/mutex return values
 * 5. Holding mutex while calling vTaskDelay() (blocks everyone!)
 * 6. Button debouncing - need delay or state machine
 *
 * 🎯 SUCCESS CRITERIA:
 *
 * [ ] All 4 patterns work correctly
 * [ ] Button cycles through patterns smoothly (< 50ms response)
 * [ ] Serial commands parse correctly
 * [ ] Status reporter shows accurate information
 * [ ] NO garbled serial output (mutex working)
 * [ ] NO race conditions
 * [ ] Code is clean, documented, and organized
 *
 * 🤔 CRITICAL THINKING QUESTIONS (Answer in comments):
 *
 * Q1: Why is button priority highest? What happens if you make it lowest?
 * Q2: What happens if status reporter doesn't use mutex for UART?
 * Q3: Could you use one queue for both pattern AND speed commands?
 * Q4: How would you add a 5th LED without rewriting everything?
 * Q5: What's the maximum button press rate you can handle reliably?
 *
 * Remember: This is YOUR project. Implement it YOUR way!
 * I'll review and provide feedback, but the code is yours.
 *
 * When you're ready for review, say: "ready for review"
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_random.h"

gpio_num_t LED[4] = {(gpio_num_t)4, (gpio_num_t)16, (gpio_num_t)17, (gpio_num_t)5};
gpio_num_t BUTTON = (gpio_num_t)15;
static const char *TAG = "LEDController";
uint16_t g_speed_ms=400;
QueueHandle_t g_patternQueue=NULL;


void buttonTask(void * pvParameter){
QueueHandle_t qHandle = (QueueHandle_t)pvParameter;

    while(1){
        if(gpio_get_level(BUTTON) == 1){
            ESP_LOGI("BUTTON_TASK", "BUTTON PRESSED");
            
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// TODO: Define your data structures here
// Hint: enum for patterns, struct for commands, array for LED pins

// TODO: Declare your global synchronization objects here
// Hint: QueueHandle_t for queues, SemaphoreHandle_t for mutex

// TODO: Implement your pattern functions
// Each function should implement one LED pattern
//  * Pattern 0 - Knight Rider (Sweeping):
//  * ●○○○ → ○●○○ → ○○●○ → ○○○● → ○○●○ → ○●○○ → repeat
int knightRider(void)
{
    // Initialize LEDs as outputs


    static int pos = 0;       // Current LED position (0-3)
    static int direction = 1; // 1 = forward, -1 = backward

    // Turn all LEDs off, current position on
    for (int i = 0; i < 4; i++)
    {
        gpio_set_level(LED[i], (i == pos) ? 0 : 1);
    }

    // Move to next position
    pos += direction;

    // Reverse direction at the ends
    if (pos == 3 || pos == 0)
    {
        direction = -direction;
    }

    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

//  * Pattern 1 - Blink All Together:
//  * ●●●● → ○○○○ → ●●●● → ○○○○ → repeat
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
//  * Pattern 2 - Alternating Pairs:
//  * ●●○○ → ○○●● → ●●○○ → ○○●● → repeat


int alternatingPair(void){
    static bool pairNumber=0;


    if(pairNumber==0){
    gpio_set_level(LED[0], 0);
    gpio_set_level(LED[1], 0);
    gpio_set_level(LED[2], 1);
    gpio_set_level(LED[3], 1);
    } else {
    gpio_set_level(LED[0], 1);
    gpio_set_level(LED[1], 1);
    gpio_set_level(LED[2], 0);
    gpio_set_level(LED[3], 0);
    }

    pairNumber = !pairNumber;
    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
    return 0;
}

//  * Pattern 3 - Random:
//  * Random LED on/off each step
int randomPattern(void){
    for (int i = 0; i < 4; i++)
    {
 
        gpio_set_level(LED[i],rand()%2);
    }
    vTaskDelay(pdMS_TO_TICKS(g_speed_ms));
return 0;
}
// TODO: Task 1 - Pattern Sequencer
// Reads commands from queue, executes patterns
void patternSequencer(void *pvParameter)
{
    while (1)
    {
        knightRider();
        // blinkAll();
        // alternatingPair();
        // randomPattern();
    }
}
// TODO: Task 2 - Button Handler
// Monitors button, sends pattern changes

// TODO: Task 3 - Serial Command Parser
// Reads UART input, parses commands

// TODO: Task 4 - Status Reporter
// Prints system status periodically

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "===========================================");
    ESP_LOGI(TAG, "Multi-Task LED Controller - Practice Project");
    ESP_LOGI(TAG, "===========================================");
    g_patternQueue = xQueueCreate(10,sizeof(int));

    for (int i = 0; i < 4; i++)
    {
        gpio_reset_pin(LED[i]);
        gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
    }
    gpio_reset_pin(BUTTON);
    gpio_set_direction(BUTTON,GPIO_MODE_INPUT);
    gpio_pulldown_en(BUTTON);
    // TODO: Create synchronization objects (queues, mutex)

    // TODO: Create tasks with appropriate priorities

    ESP_LOGI(TAG, "System initialized. Tasks running...");
    ESP_LOGI(TAG, "Commands: pattern <0-3>, speed <50-1000>, status");

    xTaskCreate(patternSequencer, "pattern", 2048, g_patternQueue, 5, NULL);
    xTaskCreate(buttonTask, "buttonTask", 2048, g_patternQueue, 5, NULL);
}