# ESP32 + FreeRTOS Complete Learning Plan

**Recommended Background:** Arduino experience, C programming on PlatformIO  
**Duration:** 3-4 weeks (flexible, self-paced)  
**Goal:** Master ESP32 hardware capabilities and FreeRTOS real-time programming

---

## 🚀 How to Use This Tutorial

### **For Students:**
1. Copy this entire repository/folder to your machine
2. Open the workspace in VS Code with PlatformIO extension
3. Reference this document and share it with GitHub Copilot Chat:
   - Use `@workspace` to give Copilot context about your project
   - Say: "I'm following the ESP32 learning plan in `.learning/` folder"
   - Copilot will act as your instructor based on this guide
4. Progress through exercises in `src/main.cpp`

### **For Copilot/AI Instructors:**
This document defines your teaching methodology. Follow these principles:

**Teaching Philosophy: Minimal Hand-Holding**
- ❌ **Never write implementation code in TODO comments**
- ❌ **Never show complete function implementations as hints**
- ✅ **Only mention function names** (e.g., "Use `xTaskCreate()`")
- ✅ **Point to documentation** (e.g., "Check ESP-IDF docs for gpio_set_direction parameters")
- ✅ **Let students discover API signatures themselves**
- ✅ **Give conceptual hints, not code snippets**

**Example of GOOD vs BAD hints:**

**❌ BAD (Too much help):**
```cpp
// TODO: Create task
// xTaskCreate(&task_function, "task1", 2048, NULL, 5, NULL);
```

**✅ GOOD (Proper guidance):**
```cpp
// TODO: Create task using xTaskCreate()
// Hint: You need task function pointer, name string, stack size, parameters, priority, and handle
```

### **Learning Flow:**
1. **Concept Introduction** - Explain theory with minimal examples
2. **Challenge Assignment** - Describe what to build (requirements only)
3. **Student Implements** - Student writes code using documentation
4. **Code Review** - AI reviews and provides feedback
5. **Iteration** - Student fixes issues with minimal hints
6. **Concept Mastery** - Confirm understanding with questions

### **Role Division**

**AI Instructor Role:**
- ✅ Explain concepts with theory and minimal examples
- ✅ Provide clear requirements and success criteria
- ✅ Review code and identify issues
- ✅ Give function names and suggest documentation to read
- ✅ Ask probing questions to check understanding
- ❌ Write implementation code in hints or comments
- ❌ Show complete solutions before student attempts

**Student Role:**
- ✅ Read ESP-IDF and FreeRTOS documentation
- ✅ Write all implementation code independently
- ✅ Test and debug solutions
- ✅ Ask specific questions when stuck
- ✅ Document learnings in progress tracker

---

## 📁 Project Workflow

### **Single Workspace Approach**

You will work in **one PlatformIO project** (`esp32-boilerplate/`) throughout the entire learning journey.

**Directory Structure:**
```
esp32-boilerplate/
├── .exercises/
│   ├── README.md              # Workflow guide
│   ├── completed/             # Your finished exercise code
│   │   ├── day1-ex2-arduino-comparison.cpp
│   │   ├── day1-ex3-logging-levels.cpp
│   │   └── day2-ex1-two-tasks.cpp
│   └── templates/             # Exercise starting templates
│       └── day2-ex2-task-parameters.cpp
│
├── .learning/                 # This directory
│   ├── ESP32_FREERTOS_LEARNING_PLAN.md
│   └── PROGRESS_TRACKER.md
│
├── src/
│   └── main.cpp              # ← YOU ALWAYS EDIT THIS FILE
│
├── platformio.ini
└── README.md
```

### **Exercise Workflow**

**Before Each Exercise:**
1. AI backs up current `src/main.cpp` → `.exercises/completed/day#-ex#-name.cpp`
2. AI provides new minimal template with TODO markers → `src/main.cpp`
3. Student stays in same VS Code window (no context loss!)

**Template Format (Minimal Guidance Only):**
```cpp
/**
 * Day X - Exercise Y: Topic Name
 * 
 * CHALLENGE: Brief description
 * 
 * REQUIREMENTS:
 * ✅ Specific requirement 1
 * ✅ Specific requirement 2
 * 
 * FUNCTIONS TO USE:
 * - function_name_1() - Brief purpose only
 * - function_name_2() - Brief purpose only
 */

// Necessary includes only
#include "header.h"

// TODO: Your task description (no code examples!)
```

**During Exercise:**
1. Open `src/main.cpp` (has TODO comments)
2. Read ESP-IDF/FreeRTOS documentation for mentioned functions
3. Write your implementation
4. Build: `pio run`
5. Upload: `pio run -t upload`
6. Test and iterate

**After Exercise:**
1. Type "ready for review"
2. I review your code and give feedback
3. You fix issues if needed
4. Move to next exercise

**Benefits:**
- ✅ **No context loss** - Same VS Code window throughout
- ✅ **No reconfiguration** - One PlatformIO project
- ✅ **Full history** - All solutions saved in `.exercises/completed/`
- ✅ **Easy reference** - View previous exercises anytime
- ✅ **Simple workflow** - Just edit `main.cpp` every time

---

## 📊 Progress Tracking

### Week 1: Foundations ⬜
- [ ] Day 1: ESP-IDF vs Arduino, Build System
- [ ] Day 2: FreeRTOS Tasks Basics
- [ ] Day 3: Task Scheduling & Priorities
- [ ] Day 4: Inter-Task Communication (Queues)
- [ ] Day 5: Semaphores & Mutexes
- [ ] Day 6-7: Practice Project: Multi-Task LED Controller

### Week 2: Hardware Peripherals ⬜
- [ ] Day 8: GPIO Deep Dive (Input/Output/ISR)
- [ ] Day 9: Timers (Hardware & Software)
- [ ] Day 10: UART Communication
- [ ] Day 11: I2C Protocol
- [ ] Day 12: SPI Protocol
- [ ] Day 13: ADC & DAC
- [ ] Day 14: Practice Project: Sensor Dashboard

### Week 3: Advanced FreeRTOS ⬜
- [ ] Day 15: Event Groups
- [ ] Day 16: Task Notifications
- [ ] Day 17: Memory Management & Heap
- [ ] Day 18: Watchdogs & Error Handling
- [ ] Day 19: Power Management & Sleep Modes
- [ ] Day 20: Interrupt Handling Deep Dive
- [ ] Day 21: Practice Project: Power-Optimized Sensor Logger

### Week 4: Connectivity & Real-World ⬜
- [ ] Day 22: WiFi Station & AP Mode
- [ ] Day 23: HTTP Client/Server
- [ ] Day 24: MQTT Protocol
- [ ] Day 25: Bluetooth Classic
- [ ] Day 26: BLE (Bluetooth Low Energy)
- [ ] Day 27-28: Final Project: IoT Device (choice below)

---

## 📚 Detailed Curriculum

## WEEK 1: FreeRTOS Fundamentals

### Day 1: ESP-IDF vs Arduino Framework
**Concepts:**
- ESP-IDF architecture vs Arduino abstraction
- `app_main()` vs `setup()/loop()`
- Build system: PlatformIO + CMake
- ESP-IDF logging system
- `extern "C"` wrapper requirement
- GPIO driver vs Arduino pinMode/digitalWrite

**Exercise 1: Code Analysis (Guided)**
- Read and understand existing blink code in `src/main.cpp`
- Identify ESP-IDF patterns vs Arduino equivalents
- Understand each header file's purpose

**Exercise 2: Side-by-Side Comparison (Guided)**
- Add Arduino equivalent code as comments
- Understand why ESP-IDF is more verbose
- Learn GPIO driver initialization pattern

**Exercise 3: ESP Logging Levels (YOUR CODE)**
**Challenge:** Modify the LED blink task to use all 4 log levels:
- Use `ESP_LOGI()` when LED turns ON
- Use `ESP_LOGW()` when LED turns OFF  
- Use `ESP_LOGE()` every 5 blinks to report "5 blinks completed"
- Use `ESP_LOGD()` to show current blink counter

**Requirements:**
- [ ] Add a counter variable to track blinks
- [ ] Log at 4 different levels with appropriate messages
- [ ] Counter increments correctly
- [ ] Every 5th blink triggers error log
- [ ] Code compiles and runs

**Hints:**
- Use `static int counter = 0;` in the task function
- `if (counter % 5 == 0)` detects every 5th blink
- Format: `ESP_LOGI(TAG, "Blink #%d", counter);`
- Increment counter after each ON/OFF cycle

**Key Takeaways:**
- `extern "C"` requirement for `app_main()`
- Header includes: `freertos/FreeRTOS.h`, `driver/gpio.h`
- ESP logging: LOGE (error), LOGW (warning), LOGI (info), LOGD (debug)
- Logging is thread-safe, Arduino Serial.print() is not

---

### Day 2: FreeRTOS Tasks - The Core Concept
**Concepts:**
- What is a task? (lightweight thread)
- Task states: Running, Ready, Blocked, Suspended
- `xTaskCreate()` parameters explained
- Task function signature: `void task(void *pvParameter)`
- Infinite loop requirement
- FreeRTOS naming conventions (v = void, x = BaseType_t)

**Exercise 1: Two Talking Tasks (YOUR CODE)**
**Challenge:** Create 2 tasks that print different messages at different intervals
- Task 1: Print "Hello from Task 1" every 1 second
- Task 2: Print "Hello from Task 2" every 2 seconds
- Both tasks should run simultaneously

**Requirements:**
- [ ] Create two separate task functions
- [ ] Both use proper `while(1)` loops
- [ ] Both use `vTaskDelay()` with different timings
- [ ] Both use ESP_LOGI with different tags
- [ ] Create both tasks in `app_main()`

**Hints:**
- Create functions: `void task1(void *pvParameter)` and `void task2(void *pvParameter)`
- Use different TAG names for each task
- Call `xTaskCreate()` twice in `app_main()`

**Exercise 2: Task with Parameters (YOUR CODE)**
**Challenge:** Pass a delay value to a generic blink task
- Create one task function that accepts delay as parameter
- Create 2 instances with different delays (500ms and 1500ms)
- Use different GPIOs for each (GPIO_NUM_2 and GPIO_NUM_4)

**Requirements:**
- [ ] Single task function accepts `void *pvParameter`
- [ ] Cast parameter to int for delay value
- [ ] Two task instances created with different parameters
- [ ] Both LEDs blink independently

**Hints:**
- Cast parameter: `int delay = (int)pvParameter;`
- Pass parameter: `xTaskCreate(&blink, "blink1", 2048, (void*)500, 5, NULL);`

**Exercise 3: Three LEDs at Different Rates (YOUR CODE)**
**Challenge:** Create 3 tasks controlling 3 LEDs
- LED 1 (GPIO_NUM_2): 200ms blink
- LED 2 (GPIO_NUM_4): 500ms blink  
- LED 3 (GPIO_NUM_5): 1000ms blink

**Requirements:**
- [ ] 3 separate GPIOs configured
- [ ] 3 tasks created
- [ ] All run simultaneously
- [ ] Clean, organized code

**Key Takeaways:**
- Stack size selection (2048, 4096 bytes)
- `vTaskDelay()` yields CPU to other tasks
- `portTICK_PERIOD_MS` vs `pdMS_TO_TICKS()`
- Tasks run truly concurrently on ESP32

---

### Day 3: Task Scheduling & Priorities
**Concepts:**
- Priority levels (0 = lowest, higher number = higher priority)
- Preemptive scheduling
- Time slicing for equal priority tasks
- `vTaskPrioritySet()`, `vTaskDelete()`, `vTaskSuspend()`

**Hands-On:**
```cpp
// Exercise 1: 3 tasks with priorities 1, 3, 5 - observe behavior
// Exercise 2: Change task priority dynamically
// Exercise 3: CPU-intensive vs I/O tasks - priority assignment
// Exercise 4: Implement task suspension/resumption with button
```

**Key Takeaways:**
- Higher priority tasks preempt lower ones
- Idle task (priority 0) runs when nothing else can
- Don't starve low-priority tasks

---

### Day 4: Queues - Inter-Task Communication
**Concepts:**
- Queue creation: `xQueueCreate(length, item_size)`
- Sending: `xQueueSend()`, `xQueueSendToBack()`, `xQueueSendToFront()`
- Receiving: `xQueueReceive()` (blocking)
- Queue full/empty handling

**Hands-On:**
```cpp
// Exercise 1: Producer-Consumer pattern (button → LED)
QueueHandle_t queue;

void producer_task(void *pvParameter) {
    int data = 0;
    while(1) {
        xQueueSend(queue, &data, portMAX_DELAY);
        data++;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void consumer_task(void *pvParameter) {
    int received;
    while(1) {
        if(xQueueReceive(queue, &received, portMAX_DELAY)) {
            ESP_LOGI("Consumer", "Got: %d", received);
        }
    }
}

// Exercise 2: Multi-producer, single consumer
// Exercise 3: Circular buffer with queue
// Exercise 4: Command processor (string commands via queue)
```

**Key Takeaways:**
- Queues are FIFO by default
- Blocking timeout: `portMAX_DELAY` vs `pdMS_TO_TICKS()`
- Check return value (`pdTRUE` / `pdFALSE`)

---

### Day 5: Semaphores & Mutexes
**Concepts:**
- Binary semaphore (0 or 1)
- Counting semaphore (resource counting)
- Mutex (mutual exclusion for shared resources)
- `xSemaphoreCreateBinary()`, `xSemaphoreCreateMutex()`
- `xSemaphoreTake()`, `xSemaphoreGive()`

**Hands-On:**
```cpp
// Exercise 1: Button ISR → Semaphore → Task (debouncing)
SemaphoreHandle_t buttonSemaphore;

void IRAM_ATTR button_isr_handler(void *arg) {
    xSemaphoreGiveFromISR(buttonSemaphore, NULL);
}

void button_task(void *pvParameter) {
    while(1) {
        if(xSemaphoreTake(buttonSemaphore, portMAX_DELAY)) {
            ESP_LOGI("BTN", "Button pressed!");
        }
    }
}

// Exercise 2: Mutex protecting shared counter (2 tasks incrementing)
// Exercise 3: Counting semaphore for resource pool (3 slots)
// Exercise 4: Priority inversion problem demonstration
```

**Key Takeaways:**
- ISR-safe versions: `FromISR()` suffix
- Mutex prevents race conditions
- Semaphores for synchronization, mutexes for protection

---

### Day 6-7: Practice Project - Multi-Task LED Controller
**Project Requirements:**
- 4 LEDs with independent control
- Task 1: LED pattern sequencer (reads from queue)
- Task 2: Button handler (sends patterns to queue)
- Task 3: Serial command parser (change speed, pattern)
- Task 4: Status reporter (prints state every 5s)
- Use: Queues, semaphores, proper priorities

**Patterns to Implement:**
1. Knight Rider (sweeping)
2. Blink all together
3. Alternating pairs
4. Random

**Success Criteria:**
- No race conditions
- Responsive button (<50ms)
- Clean serial output
- Proper resource cleanup

---

## WEEK 2: Hardware Peripherals Mastery

### Day 8: GPIO Deep Dive
**Concepts:**
- Pull-up/pull-down resistors
- Interrupt types: Rising, Falling, Both edges, Low/High level
- `gpio_config()` structure
- ISR registration and handling
- GPIO matrix and pin remapping

**Hands-On:**
```cpp
// Exercise 1: Button with internal pull-up
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_0),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE
};

// Exercise 2: Multi-button input with interrupts
// Exercise 3: Rotary encoder reading
// Exercise 4: Debouncing in software vs hardware
```

---

### Day 9: Timers (Hardware & Software)
**Concepts:**
- Hardware timers: 4 groups, 64-bit counters
- Timer ISR callbacks
- Software timers: `xTimerCreate()`
- One-shot vs auto-reload
- Timer precision vs power consumption

**Hands-On:**
```cpp
// Exercise 1: Precise 100ms hardware timer
// Exercise 2: Software timer for periodic sensor reading
// Exercise 3: PWM using timer (LED brightness)
// Exercise 4: Stopwatch with microsecond precision
```

---

### Day 10: UART Communication
**Concepts:**
- Multiple UART ports (0, 1, 2)
- Baud rates, parity, stop bits
- TX/RX buffers
- `uart_read_bytes()` vs `uart_get_buffered_data_len()`
- Pattern detection

**Hands-On:**
```cpp
// Exercise 1: Echo server (receive and send back)
// Exercise 2: AT command parser
// Exercise 3: GPS NMEA sentence parser (simulated)
// Exercise 4: Binary protocol with checksum
```

---

### Day 11: I2C Protocol
**Concepts:**
- Master/Slave configuration
- Clock speed: 100kHz (standard), 400kHz (fast)
- 7-bit vs 10-bit addressing
- ACK/NACK handling
- Common sensors: BME280, OLED displays

**Hands-On:**
```cpp
// Exercise 1: I2C scanner (find device addresses)
// Exercise 2: Read temperature from BMP280/BME280
// Exercise 3: Write to OLED display (SSD1306)
// Exercise 4: Multi-sensor I2C bus
```

---

### Day 12: SPI Protocol
**Concepts:**
- Master/Slave, full-duplex
- Clock polarity (CPOL) and phase (CPHA)
- CS (Chip Select) management
- DMA transfers
- Common devices: SD cards, TFT displays, NRF24L01

**Hands-On:**
```cpp
// Exercise 1: Read/Write to SPI flash memory
// Exercise 2: Interface with SD card (FATFS)
// Exercise 3: Control WS2812B-like LEDs via SPI
// Exercise 4: High-speed data acquisition
```

---

### Day 13: ADC & DAC
**Concepts:**
- 12-bit ADC (0-4095)
- Attenuation: 0dB (1V), 11dB (3.3V)
- Calibration for accuracy
- 8-bit DAC output
- Continuous vs single-shot mode

**Hands-On:**
```cpp
// Exercise 1: Read potentiometer value
// Exercise 2: Battery voltage monitor (with voltage divider)
// Exercise 3: DAC sine wave generator
// Exercise 4: Audio input level meter (VU meter)
```

---

### Day 14: Practice Project - Sensor Dashboard
**Project Requirements:**
- Read 3 sensors: Temperature (I2C), Light (ADC), Button state (GPIO)
- Display on OLED or Serial
- Update rates: Temp 1Hz, Light 5Hz, Button immediate
- Log data to SD card every 10s
- Buzzer alert if temperature > threshold

**Architecture:**
- Sensor reading tasks (3)
- Display update task
- SD card writer task
- Alert manager task
- Queues for data flow

---

## WEEK 3: Advanced FreeRTOS Concepts

### Day 15: Event Groups
**Concepts:**
- 24 event bits per group
- `xEventGroupSetBits()`, `xEventGroupWaitBits()`
- Wait for ANY bit vs ALL bits
- Synchronization points
- Difference from semaphores/queues

**Hands-On:**
```cpp
// Exercise 1: Wait for multiple conditions (WiFi + NTP ready)
// Exercise 2: State machine with event groups
// Exercise 3: Multi-button combinations (Ctrl+Alt+Del style)
```

---

### Day 16: Task Notifications
**Concepts:**
- Lightweight alternative to semaphores/queues
- Each task has 32-bit notification value
- Faster than queues (no memory allocation)
- `xTaskNotify()`, `ulTaskNotifyTake()`
- Use cases and limitations

**Hands-On:**
```cpp
// Exercise 1: ISR → Task notification (faster than semaphore)
// Exercise 2: Task notification as event flag
// Exercise 3: Notification value as counter
```

---

### Day 17: Memory Management
**Concepts:**
- Heap types: heap_caps, internal vs external RAM
- `malloc()` vs `heap_caps_malloc()`
- Memory fragmentation
- Stack overflow detection
- `heap_caps_get_free_size()`

**Hands-On:**
```cpp
// Exercise 1: Monitor heap usage over time
// Exercise 2: Intentional stack overflow (to understand errors)
// Exercise 3: Allocate DMA-capable memory
// Exercise 4: Memory leak detection
```

---

### Day 18: Watchdogs & Error Handling
**Concepts:**
- Task watchdog timer (TWDT)
- Interrupt watchdog timer (IWDT)
- `esp_task_wdt_add()`, `esp_task_wdt_reset()`
- Panic handler and core dumps
- `ESP_ERROR_CHECK()` macro

**Hands-On:**
```cpp
// Exercise 1: Trigger watchdog reset (intentional)
// Exercise 2: Graceful error recovery
// Exercise 3: Custom panic handler
```

---

### Day 19: Power Management & Sleep Modes
**Concepts:**
- Active mode, Modem sleep, Light sleep, Deep sleep
- Wake sources: Timer, GPIO, Touchpad, ULP
- RTC memory persistence
- Power consumption measurements
- `esp_sleep_enable_timer_wakeup()`

**Hands-On:**
```cpp
// Exercise 1: Deep sleep wake on timer
// Exercise 2: Wake on button press (ext0/ext1)
// Exercise 3: Battery-powered sensor (sleep between readings)
// Exercise 4: RTC memory usage across deep sleep
```

---

### Day 20: Interrupt Handling Deep Dive
**Concepts:**
- IRAM_ATTR requirement
- ISR stack limitations (no logging, no delays)
- Deferred interrupt processing
- Critical sections: `portENTER_CRITICAL()`, `portEXIT_CRITICAL()`
- Interrupt priority levels

**Hands-On:**
```cpp
// Exercise 1: High-frequency pulse counter in ISR
// Exercise 2: ISR → Queue → Processing task pattern
// Exercise 3: Critical section protecting shared variable
// Exercise 4: Measure ISR latency
```

---

### Day 21: Practice Project - Power-Optimized Sensor Logger
**Project Requirements:**
- Read sensor every 15 minutes
- Deep sleep between readings
- Store readings in RTC memory (last 10 readings)
- Wake on button to display all readings via serial
- Run on battery for days/weeks
- LED blink pattern shows battery level on wake

**Optimization Goals:**
- <1mA average current consumption
- Wake time <2 seconds
- No data loss on crashes

---

## WEEK 4: Connectivity & Real-World Applications

### Day 22: WiFi Station & AP Mode
**Concepts:**
- WiFi event handling (`WIFI_EVENT_STA_CONNECTED`)
- WPA2 authentication
- AP mode (ESP32 as access point)
- IP assignment (DHCP vs static)
- `esp_wifi_init()`, `esp_wifi_start()`

**Hands-On:**
```cpp
// Exercise 1: Connect to WiFi with credentials
// Exercise 2: WiFi event-driven state machine
// Exercise 3: Create WiFi AP with password
// Exercise 4: WiFi scan and strongest signal selection
```

---

### Day 23: HTTP Client/Server
**Concepts:**
- `esp_http_client` for requests
- `esp_http_server` for web server
- URI handlers
- GET/POST methods
- JSON parsing (cJSON library)

**Hands-On:**
```cpp
// Exercise 1: HTTP GET request to API
// Exercise 2: Web server serving HTML page
// Exercise 3: REST API (GET sensor data, POST settings)
// Exercise 4: OTA updates via HTTP
```

---

### Day 24: MQTT Protocol
**Concepts:**
- Publisher/Subscriber model
- Topics and QoS levels (0, 1, 2)
- Retained messages
- Last Will and Testament (LWT)
- `esp_mqtt_client`

**Hands-On:**
```cpp
// Exercise 1: Publish sensor data to broker
// Exercise 2: Subscribe to command topic
// Exercise 3: MQTT + JSON payload
// Exercise 4: Home Assistant integration
```

---

### Day 25: Bluetooth Classic
**Concepts:**
- SPP (Serial Port Profile)
- Pairing and bonding
- Bluetooth stack initialization
- Discovery and connection

**Hands-On:**
```cpp
// Exercise 1: Bluetooth serial terminal
// Exercise 2: Wireless sensor data over BT
// Exercise 3: Bluetooth audio (A2DP basics)
```

---

### Day 26: BLE (Bluetooth Low Energy)
**Concepts:**
- GATT services and characteristics
- Advertising and scanning
- Central vs Peripheral roles
- Notifications and indications
- Power efficiency

**Hands-On:**
```cpp
// Exercise 1: BLE beacon advertiser
// Exercise 2: Custom GATT service (sensor readings)
// Exercise 3: BLE scanner (find nearby devices)
// Exercise 4: Phone app communication (nRF Connect)
```

---

### Day 27-28: Final Capstone Project (Choose One)

#### Option A: Smart Home Sensor Hub
- 5+ sensors (temp, humidity, motion, light, door)
- MQTT to Home Assistant
- Web interface for configuration
- Deep sleep when inactive
- Battery + solar powered
- OTA updates

#### Option B: Wireless Data Logger
- Multi-channel ADC sampling (1kHz)
- Store to SD card (CSV format)
- BLE for configuration
- Real-time streaming to PC
- Trigger modes (threshold, edge)
- Web dashboard

#### Option C: RC Car/Robot Controller
- WiFi control from phone
- Motor control (PWM)
- Ultrasonic obstacle avoidance
- Camera streaming (ESP32-CAM)
- FreeRTOS tasks: Control, Sensors, Camera, WiFi
- WebSocket for low-latency commands

#### Option D: Custom Project
Design your own combining:
- At least 3 peripherals
- WiFi or BLE
- Multiple FreeRTOS tasks
- Proper error handling
- Power management

---

## 📖 Learning Resources

### Official Documentation
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [FreeRTOS.org](https://www.freertos.org/Documentation/RTOS_book.html)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)

### Recommended Books
- "Mastering ESP32" by Luca Dentella
- "The FreeRTOS Reference Manual" (free PDF)
- "ESP32 Cookbook" by Marco Schwartz

### Video Tutorials
- Espressif YouTube channel
- Andreas Spiess (The guy with the Swiss accent)
- DroneBot Workshop

### Code Examples
- ESP-IDF examples folder: `$IDF_PATH/examples/`
- This boilerplate: Start from `src/main.cpp`

---

## 🎯 Success Metrics

### Week 1
✅ Can create and manage multiple tasks  
✅ Understand task priorities and scheduling  
✅ Use queues, semaphores, mutexes correctly  
✅ Debug task synchronization issues

### Week 2
✅ Configure any GPIO peripheral  
✅ Interface with I2C and SPI devices  
✅ Read ADC and generate DAC output  
✅ Handle UART communication

### Week 3
✅ Optimize power consumption  
✅ Handle errors gracefully  
✅ Understand memory management  
✅ Write ISR-safe code

### Week 4
✅ Connect ESP32 to internet  
✅ Build web server or API client  
✅ Implement MQTT or BLE  
✅ Complete full IoT project

---

## 🔧 Development Setup Checklist

- [x] PlatformIO installed
- [x] ESP32 board available
- [ ] Breadboard and jumper wires
- [ ] LEDs, resistors, buttons
- [ ] I2C sensor (BME280 recommended)
- [ ] Logic analyzer (optional but helpful)
- [ ] Multimeter for debugging

---

## 📝 Daily Learning Log

Use this section to track your progress:

### Week 1 Log
**Day 1:** _______________  
Notes:

**Day 2:** _______________  
Notes:

(Continue for each day...)

---

## 🚀 Next Steps After Completion

1. **ESP32 Advanced Topics:**
   - ULP coprocessor programming
   - Touch sensor APIs
   - ESP-NOW protocol
   - Ethernet connectivity

2. **Professional Development:**
   - RTOS design patterns
   - Unit testing (Unity framework)
   - CI/CD for embedded
   - Production deployment

3. **Hardware Expansion:**
   - ESP32-S3 (AI acceleration)
   - ESP32-C3 (RISC-V)
   - ESP32-CAM
   - Custom PCB design

---

**Ready to start? Begin with Week 1, Day 1! 🎓**

**Questions? Create issues in this project or ask as we go along.**
